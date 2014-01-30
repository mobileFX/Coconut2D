/* ***** BEGIN LICENSE BLOCK *****
 *
 * Copyright (C) 2013 www.coconut2D.org
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.   
 *
 * ***** END LICENSE BLOCK ***** */

// ==================================================================================================================================
//	    ___             ___      _____ __                          
//	   /   | __  ______/ (_)___ / ___// /_________  ____ _____ ___ 
//	  / /| |/ / / / __  / / __ \\__ \/ __/ ___/ _ \/ __ `/ __ `__ \
//	 / ___ / /_/ / /_/ / / /_/ /__/ / /_/ /  /  __/ /_/ / / / / / /
//	/_/  |_\__,_/\__,_/_/\____/____/\__/_/   \___/\__,_/_/ /_/ /_/ 
//	                                                               
// ==================================================================================================================================

#include "fxAudioStream.h"

#ifdef ENABLE_OGG_SUPPORT
extern ov_callbacks fxAudioStream::ovc;

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
#endif /* ENABLE_OGG_SUPPORT */

#ifdef ENABLE_OPENAL_SUPPORT
extern ALCdevice* fxAudioStream::alcDevice;
extern ALCcontext* fxAudioStream::alcContext;
#endif /* ENABLE_OPENAL_SUPPORT */

extern std::map<fxObjectUID, fxAudioStream*>* fxAudioStream::audios;

//////////////////////////////////////////////////////////////////////////////////////////////
void fxAudioStream::init()
{
    #ifdef ENABLE_OGG_SUPPORT
    ovc.read_func = ogg_from_memory_read;
    ovc.seek_func = ogg_from_memory_seek;
    ovc.close_func = ogg_from_memory_close;
    ovc.tell_func = ogg_from_memory_tell;
    #endif /* ENABLE_OGG_SUPPORT */
    
    #ifdef ENABLE_OPENAL_SUPPORT
    alcDevice = alcOpenDevice(nullptr);
    if(!alcDevice) LOGW("Could not get default ALC Device!\n");
    alcContext = alcCreateContext(alcDevice, nullptr);
    if(!alcContext) LOGW("Could not create ALC Context!\n");
    alcMakeContextCurrent(alcContext);
    #endif /* ENABLE_OPENAL_SUPPORT */
    
    audios = new std::map<fxObjectUID, fxAudioStream*>();
}

//////////////////////////////////////////////////////////////////////////////////////////////
void fxAudioStream::quit()
{
    delete audios;
    audios = nullptr;
    
    #ifdef ENABLE_OPENAL_SUPPORT
    alcMakeContextCurrent(nullptr);
    alcDestroyContext(alcContext);
    if(alcCloseDevice(alcDevice) != ALC_TRUE)
    {
    	LOGW("alcCloseDevice Error!\n");
    } else {
    	LOGI("alcCloseDevice ok!");
    }
    #endif /* ENABLE_OPENAL_SUPPORT */
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

#ifdef ENABLE_OPENAL_SUPPORT
//////////////////////////////////////////////////////////////////////////////////////////////
fxAudioStream::fxAudioStream(const char* str) : loop(false), playCount(1), data({nullptr}), type(Type::NONE), state(State::NONE)
{
    char* ld = (char*) strrchr(str, '.');
    if(!ld) { LOGW("Invalid file!\n"); }
    else
    {
        ld++;
        #ifdef ENABLE_OGG_SUPPORT
        if(!strncmp(ld, "ogg", 3)) type = Type::OGG;
        else
        #endif /* ENABLE_OGG_SUPPORT */
            
        {
            LOGW("Extension \".%s\" not supported!\n", ld);
            return;
        }
    }

    switch(type) {
        case Type::OGG:
        #ifdef ENABLE_OGG_SUPPORT
        {
            data.file = fxFile::open(str);
            if(!data.file) return;
            
            OggVorbis_File ovf;
            ov_open_callbacks(data.file, &ovf, nullptr, 0, ovc);
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
            state = State::STOPPED;
        } break;
        #endif /* ENABLE_OGG_SUPPORT */
		default: LOGW("Audio file not supported!\n"); break;
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////
fxAudioStream::~fxAudioStream()
{
    if(data.file) delete data.file;
    if(state != State::NONE)
    {
        alSourceStop(alSource);
        alDeleteSources(1, &alSource);
        alDeleteBuffers(1, &alBuffer);
    }
}
#else
fxAudioStream::fxAudioStream(const char* str) : state(State::NONE) { LOGW("Audio playback not supported!\n"); }
fxAudioStream::~fxAudioStream() {}
#endif /* ENALE_OPENAL_SUPPORT */


//////////////////////////////////////////////////////////////////////////////////////////////
void fxAudioStream::play(size_t i_playCount)
{
    if(state == State::NONE) return;
    playCount = i_playCount;
    
    #ifdef ENABLE_OPENAL_SUPPORT
    if(loop) alSourcei(alSource, AL_LOOPING, AL_TRUE);
    else
    {
        alSourcei(alSource, AL_LOOPING, AL_FALSE);
        for(size_t i = playCount; i--;)
            alSourceQueueBuffers(alSource, 1, &alBuffer);
    }
    alSourcePlay(alSource);
    #endif /* ENABLE_OPENAL_SUPPORT */
}

//////////////////////////////////////////////////////////////////////////////////////////////
void fxAudioStream::setloop(bool i_loop)
{
    loop = i_loop;
}

//////////////////////////////////////////////////////////////////////////////////////////////
void fxAudioStream::stop()
{
    #ifdef ENABLE_OPENAL_SUPPORT
    alSourceStop(alSource);
    #endif /* ENABLE_OPENAL_SUPPORT */
}

//////////////////////////////////////////////////////////////////////////////////////////////
void fxAudioStream::set_position(float pos)
{
	#ifdef ENABLE_OPENAL_SUPPORT
    alSourceStop(alSource);
	alSourcef(alSource, AL_SEC_OFFSET, pos);
	#endif /* ENABLE_OPENAL_SUPPORT */
}

//////////////////////////////////////////////////////////////////////////////////////////////
float fxAudioStream::get_position()
{
	float ret = 0.0f;
	#ifdef ENABLE_OPENAL_SUPPORT
    alGetSourcef(alSource, AL_SEC_OFFSET, &ret);
	#endif /* ENABLE_OPENAL_SUPPORT */
	return ret;
}

bool fxAudioStream::isStopped()
{
	return state == State::STOPPED;
}

bool fxAudioStream::isPaused()
{
	return state == State::PAUSED;
}

//////////////////////////////////////////////////////////////////////////////////////////////
void fxAudioStream::_tick()
{
	#ifdef ENABLE_OPENAL_SUPPORT
	ALint val;
	alGetSourcei(alSource, AL_SOURCE_STATE, &val);
	switch(val)
	{
		case AL_STOPPED:
			state = State::STOPPED;
			break;
			
		case AL_PAUSED:
			state = State::PAUSED;
			break;
		case AL_PLAYING:
			state = State::PLAYING;
			break;
		default:
			state = State::STOPPED;
	}
	#endif
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


