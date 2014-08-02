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
//	   ______                 ___             ___      _____ __
//	  / ____/___  _________  /   | __  ______/ (_)___ / ___// /_________  ____ _____ ___
//	 / /   / __ \/ ___/ __ \/ /| |/ / / / __  / / __ \\__ \/ __/ ___/ _ \/ __ `/ __ `__ \
//	/ /___/ /_/ / /__/ /_/ / ___ / /_/ / /_/ / / /_/ /__/ / /_/ /  /  __/ /_/ / / / / / /
//	\____/\____/\___/\____/_/  |_\__,_/\__,_/_/\____/____/\__/_/   \___/\__,_/_/ /_/ /_/
//
// ==================================================================================================================================

#include "CocoAudioStream.h"

#ifdef ENABLE_OGG_SUPPORT
ov_callbacks CocoAudioStream::ovc;

//////////////////////////////////////////////////////////////////////////////////////////////
size_t CocoAudioStream::ogg_from_memory_read(void* ptr, size_t size, size_t nmemb, void* datasource)
{
    if(datasource && ptr) return ((CocoAssetFile*)datasource)->read(ptr, size * nmemb);
    return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////
int CocoAudioStream::ogg_from_memory_seek(void* datasource, ogg_int64_t offset, int whence)
{
    if(!datasource) return -1;
    CocoAssetFile* file = (CocoAssetFile*)datasource;
    return file->seek(offset, whence);
}

//////////////////////////////////////////////////////////////////////////////////////////////
int CocoAudioStream::ogg_from_memory_close(void* datasource)
{
    return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////
long CocoAudioStream::ogg_from_memory_tell(void* datasource)
{
    if(!datasource) return -1;
    return ((CocoAssetFile*)datasource)->tell();
}
#endif /* ENABLE_OGG_SUPPORT */

#ifdef ENABLE_OPENAL_SUPPORT
	ALCdevice* CocoAudioStream::alcDevice;
	ALCcontext* CocoAudioStream::alcContext;
	std::map<std::string, ALuint>* CocoAudioStream::buffers;
#endif /* ENABLE_OPENAL_SUPPORT */

std::map<fxObjectUID, CocoAudioStream*>* CocoAudioStream::audios;

//////////////////////////////////////////////////////////////////////////////////////////////
void CocoAudioStream::init()
{
    #ifdef ENABLE_OGG_SUPPORT
    ovc.read_func = ogg_from_memory_read;
    ovc.seek_func = ogg_from_memory_seek;
    ovc.close_func = ogg_from_memory_close;
    ovc.tell_func = ogg_from_memory_tell;
    #endif /* ENABLE_OGG_SUPPORT */

    #ifdef ENABLE_OPENAL_SUPPORT
    alcDevice = alcOpenDevice(nullptr);
    if(!alcDevice) trace("ERROR(CocoAudioStream.cpp): Could not get default ALC Device");
    alcContext = alcCreateContext(alcDevice, nullptr);
    if(!alcContext) trace("ERROR(CocoAudioStream.cpp): Could not create ALC Context");
	buffers = new std::map<std::string, ALuint>();
    alcMakeContextCurrent(alcContext);
    #endif /* ENABLE_OPENAL_SUPPORT */

    audios = new std::map<fxObjectUID, CocoAudioStream*>();
}

//////////////////////////////////////////////////////////////////////////////////////////////
void CocoAudioStream::quit()
{
	while(audios->begin() != audios->end())
	{
		delete audios->begin()->second;
		audios->erase(audios->begin());
	}
    delete audios;
    audios = nullptr;

    #ifdef ENABLE_OPENAL_SUPPORT
	while(buffers->begin() != buffers->end())
	{
		alDeleteBuffers(1, &buffers->begin()->second);
		buffers->erase(buffers->begin());
	}
	delete buffers;
	buffers = nullptr;
    alcMakeContextCurrent(nullptr);
    alcDestroyContext(alcContext);
    if(alcCloseDevice(alcDevice) != ALC_TRUE)
    {
    	trace("ERROR(CocoAudioStream.cpp): alcCloseDevice Error");
    }
    #endif /* ENABLE_OPENAL_SUPPORT */
}

//////////////////////////////////////////////////////////////////////////////////////////////
void CocoAudioStream::add(fxObjectUID uid, const char* str)
{
    if(!audios) return;
    audios->insert(std::pair<fxObjectUID, CocoAudioStream*>(uid, new CocoAudioStream(str)));
}

//////////////////////////////////////////////////////////////////////////////////////////////
void CocoAudioStream::remove(fxObjectUID uid)
{
    if(!audios) return;
    std::map<fxObjectUID, CocoAudioStream*>::iterator it = audios->find(uid);
    if(it != audios->end())
    {
        delete it->second;
        audios->erase(it);
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////
CocoAudioStream* CocoAudioStream::get(fxObjectUID uid)
{
    if(audios)
    {
        std::map<fxObjectUID, CocoAudioStream*>::iterator it = audios->find(uid);
        if(it != audios->end()) return it->second;
    }
    return nullptr;
}

//////////////////////////////////////////////////////////////////////////////////////////////
void CocoAudioStream::tick()
{
    if(!audios) return;
    for(std::map<fxObjectUID, CocoAudioStream*>::iterator it = audios->begin(); it != audios->end(); it++)
        it->second->_tick();
}

#ifdef ENABLE_OPENAL_SUPPORT
//////////////////////////////////////////////////////////////////////////////////////////////
CocoAudioStream::CocoAudioStream(const char* str) : loop(false), playCount(1), type(Type::NONE), state(State::NONE)
{
	std::string stdStr = str;
	std::map<std::string, ALuint>::iterator it = buffers->find(stdStr);
	if(it != buffers->end())
	{
		alBuffer = it->second;
	}
	else
	{
		CocoAssetFile* file = CocoAssetFile::open(str);
		if(!file)
		{
			trace("ERROR(CocoAudioStream.cpp): Could not load audio from: %s", str);
			return;
		}
		switch(file->mime)
		{
			#ifdef ENABLE_OGG_SUPPORT
			case CocoAssetFile::MIME::AUDIO_OGG:
			{
				OggVorbis_File ovf;
				ov_open_callbacks(file, &ovf, nullptr, 0, ovc);
				vorbis_info* ovi = ov_info(&ovf, -1);

				ALsizei alFrequency = ovi->rate;
				ALenum alFormat;
				switch(ovi->channels)
				{
					case 1: alFormat = AUDIO_FORMAT_MONO; break;
					case 2: alFormat = AUDIO_FORMAT_STEREO; break;
					default:
						trace("ERROR(CocoAudioStream.cpp): Wrong number of channels in OGG file %s", str);
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
				buffers->insert(std::pair<std::string, ALuint>(stdStr, alBuffer));

				delete[] buffer;
				break;
			}
			#endif /* ENABLE_OGG_SUPPORT */
			default:
				trace("ERROR(CocoAudioStream.cpp): Unsupported audio format %s", str);
				return;
		}
		delete file;
	}
	alGenSources(1, &alSource);
	alSourcef(alSource, AL_GAIN, 1.0f);
	alSourcef(alSource, AL_PITCH, 1.0f);
	alSourcei(alSource, AL_BUFFER, alBuffer);
	state = State::STOPPED;
}

//////////////////////////////////////////////////////////////////////////////////////////////
CocoAudioStream::~CocoAudioStream()
{
    if(state != State::NONE)
    {
        alSourceStop(alSource);
        alDeleteSources(1, &alSource);
    }
}

#else
CocoAudioStream::CocoAudioStream(const char* str) : state(State::NONE) { trace("ERROR(CocoAudioStream.cpp): Audio playback not supported"); }
CocoAudioStream::~CocoAudioStream() {}
#endif /* ENALE_OPENAL_SUPPORT */


//////////////////////////////////////////////////////////////////////////////////////////////
void CocoAudioStream::play(size_t i_playCount)
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
void CocoAudioStream::setloop(bool i_loop)
{
    loop = i_loop;
}

//////////////////////////////////////////////////////////////////////////////////////////////
void CocoAudioStream::stop()
{
    #ifdef ENABLE_OPENAL_SUPPORT
    alSourceStop(alSource);
    #endif /* ENABLE_OPENAL_SUPPORT */
}

//////////////////////////////////////////////////////////////////////////////////////////////
void CocoAudioStream::set_position(float pos)
{
	#ifdef ENABLE_OPENAL_SUPPORT
    alSourceStop(alSource);
	alSourcef(alSource, AL_SEC_OFFSET, pos);
	#endif /* ENABLE_OPENAL_SUPPORT */
}

//////////////////////////////////////////////////////////////////////////////////////////////
float CocoAudioStream::get_position()
{
	float ret = 0.0f;
	#ifdef ENABLE_OPENAL_SUPPORT
    alGetSourcef(alSource, AL_SEC_OFFSET, &ret);
	#endif /* ENABLE_OPENAL_SUPPORT */
	return ret;
}

bool CocoAudioStream::isStopped()
{
	return state == State::STOPPED;
}

bool CocoAudioStream::isPaused()
{
	return state == State::PAUSED;
}

//////////////////////////////////////////////////////////////////////////////////////////////
void CocoAudioStream::_tick()
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
     if(size < 0) { trace("Error reading OGG file!\n"); }
     else if(!size)
     {
     ov_pcm_seek(&ovf, 0);
     if(!loop && !(--playCount)) { alSourceStop(alSource); }
     size = ov_read(&ovf, (char*)Buffer, AUDIO_BUFFER_SIZE, &ovSection);
     if(size <= 0) { trace("Error on OGG file!\n"); }
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


