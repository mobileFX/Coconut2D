#include "StdAfx.h"
#include "fxAudioStream.h"

extern ov_callbacks fxAudioStream::ovc;
extern ALCdevice* fxAudioStream::alcDevice;
extern ALCcontext* fxAudioStream::alcContext;
extern std::map<fxObjectUID, fxAudioStream*>* fxAudioStream::audios;

//////////////////////////////////////////////////////////////////////////////////////////////
void fxAudioStream::init()
{
    ovc.read_func = ogg_from_memory_read;
    ovc.seek_func = ogg_from_memory_seek;
    ovc.close_func = ogg_from_memory_close;
    ovc.tell_func = ogg_from_memory_tell;

    alcDevice = alcOpenDevice(nullptr);

    if(!alcDevice) LOGW("Could not get default ALC Device!\n");
    alcContext = alcCreateContext(alcDevice, nullptr);
    if(!alcContext) LOGW("Could not create ALC Context!\n");
    alcMakeContextCurrent(alcContext);

    audios = new std::map<fxObjectUID, fxAudioStream*>();
}

//////////////////////////////////////////////////////////////////////////////////////////////
void fxAudioStream::quit()
{
    delete audios;
    audios = nullptr;
    alcMakeContextCurrent(nullptr);
    alcDestroyContext(alcContext);
    alcCloseDevice(alcDevice);
}

//////////////////////////////////////////////////////////////////////////////////////////////
void fxAudioStream::add(fxObjectUID uid, const char* str)
{
    if(!audios) return;
    audios->insert(std::pair<fxObjectUID, fxAudioStream*>(uid, new fxAudioStream(str)));
    LOGI("audio file allocated!\n");
}

//////////////////////////////////////////////////////////////////////////////////////////////
void fxAudioStream::remove(fxObjectUID uid)
{
    if(!audios) return;
    std::map<fxObjectUID, fxAudioStream*>::iterator it = audios->find(uid);
    if(it != audios->end())
    {
        delete it->second;
        audios->erase(it);
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////
fxAudioStream* fxAudioStream::get(fxObjectUID uid)
{
    if(audios)
    {
        std::map<fxObjectUID, fxAudioStream*>::iterator it = audios->find(uid);
        if(it != audios->end()) return it->second;
    }
    return nullptr;
}

//////////////////////////////////////////////////////////////////////////////////////////////
void fxAudioStream::tick()
{
    if(!audios) return;
    for(std::map<fxObjectUID, fxAudioStream*>::iterator it = audios->begin(); it != audios->end(); it++)
        it->second->_tick();
}

//////////////////////////////////////////////////////////////////////////////////////////////
fxAudioStream::fxAudioStream(const char* str, bool isAsset) : fxFile(str, isAsset), loop(false), playCount(1), state(State::STOPPED)
{
    OggVorbis_File ovf;
    ov_open_callbacks(this, &ovf, nullptr, 0, ovc);
    vorbis_info* ovi = ov_info(&ovf, -1);

    ALsizei alFrequency = ovi->rate;
    ALenum alFormat;
    switch(ovi->channels)
    {
        case 1: alFormat = AUDIO_FORMAT_MONO; break;
        case 2: alFormat = AUDIO_FORMAT_STEREO; break;
        default: { LOGW("Wrong number of channels in OGG file!\n"); }
    }

    int ovSection = 0;
    ogg_int64_t size = ov_pcm_total(&ovf, -1) * AUDIO_SAMPLE_SIZE * ovi->channels;
    unsigned char* buffer = new unsigned char[size];
    long i;
    long total = 0;
    ov_pcm_seek(&ovf, 0);
    while((i = ov_read(&ovf, (char*)buffer + total, 4096, &ovSection)))
        total += i;
    ov_clear(&ovf);

    alGenBuffers(1, &alBuffer);
    alBufferData(alBuffer, alFormat, buffer, size, alFrequency);

    alGenSources(1, &alSource);
    alSourcef(alSource, AL_GAIN, 1.0f);
    alSourcef(alSource, AL_PITCH, 1.0f);
    alSourcei(alSource, AL_BUFFER, alBuffer);

    delete[] buffer;
}

//////////////////////////////////////////////////////////////////////////////////////////////
fxAudioStream::~fxAudioStream()
{
    alSourceStop(alSource);
    alDeleteSources(1, &alSource);
    alDeleteBuffers(1, &alBuffer);
}

//////////////////////////////////////////////////////////////////////////////////////////////
void fxAudioStream::play(size_t i_playCount)
{
    playCount = i_playCount;

    if(loop) alSourcei(alSource, AL_LOOPING, AL_TRUE);
    else
    {
        alSourcei(alSource, AL_LOOPING, AL_FALSE);
        for(size_t i = playCount; i--;)
            alSourceQueueBuffers(alSource, 1, &alBuffer);
    }
    alSourcePlay(alSource);
}

//////////////////////////////////////////////////////////////////////////////////////////////
void fxAudioStream::setloop(bool i_loop)
{
    loop = i_loop;
}

//////////////////////////////////////////////////////////////////////////////////////////////
void fxAudioStream::stop()
{
    alSourceStop(alSource);
}

//////////////////////////////////////////////////////////////////////////////////////////////
void fxAudioStream::_tick()
{
    return;
    /*if(state != State::PLAYING) return;

    ALuint buff;
    ALint val;
    long size;
    bool repeat = false;

    alGetSourcei(alSource, AL_SOURCE_STATE, &val);
    if(val == AL_STOPPED) state = State::STOPPED;

    alGetSourcei(alSource, AL_BUFFERS_PROCESSED, &val);
    while(val--)
    {
        alSourceUnqueueBuffers(alSource, 1, &buff);
        size = ov_read(&ovf, (char*)Buffer, AUDIO_BUFFER_SIZE, &ovSection);
        if(size < 0) { LOGW("Error reading OGG file!\n"); }
        else if(!size)
        {
            ov_pcm_seek(&ovf, 0);
            if(!loop && !(--playCount)) { alSourceStop(alSource); }
            size = ov_read(&ovf, (char*)Buffer, AUDIO_BUFFER_SIZE, &ovSection);
            if(size <= 0) { LOGW("Error on OGG file!\n"); }
        }
        if(size > 0)
        {
            repeat = true;
            alBufferData(buff, alFormat, Buffer, size, alFrequency);
            alSourceQueueBuffers(alSource, 1, &buff);
        }
    }
    if(repeat && state != State::PLAYING) alSourcePlay(alSource);*/
}

//////////////////////////////////////////////////////////////////////////////////////////////
// OGG
//////////////////////////////////////////////////////////////////////////////////////////////

size_t fxAudioStream::ogg_from_memory_read(void* ptr, size_t size, size_t nmemb, void* datasource)
{
    if(datasource && ptr) return ((fxFile*)datasource)->read(ptr, size * nmemb);
    return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////
int fxAudioStream::ogg_from_memory_seek(void* datasource, ogg_int64_t offset, int whence)
{
    if(!datasource) return -1;
    fxFile* file = (fxFile*)datasource;
    return file->seek(offset, whence);
}

//////////////////////////////////////////////////////////////////////////////////////////////
int fxAudioStream::ogg_from_memory_close(void* datasource)
{
    return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////
long fxAudioStream::ogg_from_memory_tell(void* datasource)
{
    if(!datasource) return -1;
    return ((fxFile*)datasource)->tell();
}


