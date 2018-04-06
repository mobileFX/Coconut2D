/* ***** BEGIN LICENSE BLOCK *****
*
* Copyright (C) 2013-2017 www.mobilefx.com
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

#ifndef __NATIVE_AUDIO_HPP__
#define __NATIVE_AUDIO_HPP__

#ifdef COCONUT_SCRIPT_CONTROL
	#include "Common.h"
	#include "AssetFile.h"
	typedef AssetFile CocoAssetFile;
#else
	#include "Coconut2D.hpp"
#endif

#define AUDIO_SAMPLE_SIZE 2
#define AUDIO_FORMAT_MONO AL_FORMAT_MONO16
#define AUDIO_FORMAT_STEREO AL_FORMAT_STEREO16

// ==================================================================================================================================
//	    _   __      __  _            ___             ___      _____            __
//	   / | / /___ _/ /_(_)   _____  /   | __  ______/ (_)___ / ___/__  _______/ /____  ____ ___
//	  /  |/ / __ `/ __/ / | / / _ \/ /| |/ / / / __  / / __ \\__ \/ / / / ___/ __/ _ \/ __ `__ \
//	 / /|  / /_/ / /_/ /| |/ /  __/ ___ / /_/ / /_/ / / /_/ /__/ / /_/ (__  ) /_/  __/ / / / / /
//	/_/ |_/\__,_/\__/_/ |___/\___/_/  |_\__,_/\__,_/_/\____/____/\__, /____/\__/\___/_/ /_/ /_/
//	                                                            /____/
// ==================================================================================================================================

class CocoAudioSystemSource;

class CocoAudioSystem
{
public:

	static ov_callbacks vorbis_callbacks;
	static ALCdevice* AudioDevice;
	static ALCcontext* AudioDeviceContext;

	static Array<CocoAudioSystemSource*>* AudioSources;
	static std::map<String, ALuint>* OpenALBuffersCache;

	// Audio System	API
	static void init();
	static void quit();
	static void tick();
	static CocoAudioSystemSource* NewSource(String url);
	static void DisposeSource(CocoAudioSystemSource* stream);

	// Vorbis OGG File Format Helpers
	static size_t ogg_from_memory_read(void* ptr, size_t size, size_t nmemb, void* datasource);
	static int ogg_from_memory_seek(void* datasource, ogg_int64_t offset, int whence);
	static int ogg_from_memory_close(void* datasource);
	static long ogg_from_memory_tell(void* datasource);
};

// ==================================================================================================================================
//	    _   __      __  _            ___             ___      _____
//	   / | / /___ _/ /_(_)   _____  /   | __  ______/ (_)___ / ___/____  __  _______________
//	  /  |/ / __ `/ __/ / | / / _ \/ /| |/ / / / __  / / __ \\__ \/ __ \/ / / / ___/ ___/ _ \
//	 / /|  / /_/ / /_/ /| |/ /  __/ ___ / /_/ / /_/ / / /_/ /__/ / /_/ / /_/ / /  / /__/  __/
//	/_/ |_/\__,_/\__/_/ |___/\___/_/  |_\__,_/\__,_/_/\____/____/\____/\__,_/_/   \___/\___/
//
// ==================================================================================================================================

enum NATIVE_AUDIO_STATE_ENUM
{
	AUDIO_STATE_NONE = 0,
	AUDIO_STATE_INITIALIZED,
	AUDIO_STATE_STOPPED,
	AUDIO_STATE_PAUSED,
	AUDIO_STATE_PLAYING
};

class CocoAudioSystemSource
{
public:

	String id;
	float volume;
	String src;
	ALuint alBuffer;
	ALuint alSource;
	bool loop;
	bool autoplay;
	bool ended;
	double duration;
	NATIVE_AUDIO_STATE_ENUM state;

	//////////////////////////////////////////////////////////////////////////////////////////////
	CocoAudioSystemSource()
	{
		id = "";
		src = "";
		volume = 1.0;
		alBuffer = 0;
		alSource = 0;
		loop = false;
		autoplay = false;
		ended = false;
		state = NATIVE_AUDIO_STATE_ENUM::AUDIO_STATE_NONE;
	}

	//////////////////////////////////////////////////////////////////////////////////////////////
	~CocoAudioSystemSource()
	{
		// Stop OpenAL Source
		if (alSource)
		{
			alSourceStop(alSource);
			alDeleteSources(1, &alSource);
		}

		// Remove Audio Stream
		CocoAudioSystem::DisposeSource(this);
	}

	//////////////////////////////////////////////////////////////////////////////////////////////
	String get_src()				{ return src; }
	void set_autoplay(bool value)	{ autoplay = value;	}
	bool get_autoplay()				{ return autoplay; }
	void set_loop(bool value)		{ loop = value;	}
	bool get_loop()					{ return loop; }
	bool isStopped()				{ return state == NATIVE_AUDIO_STATE_ENUM::AUDIO_STATE_STOPPED;	}
	bool isPaused()					{ return state == NATIVE_AUDIO_STATE_ENUM::AUDIO_STATE_PAUSED; }
	bool hasEnded()					{ return ended;	}
	double get_duration()			{ return duration; }

	//////////////////////////////////////////////////////////////////////////////////////////////
	void play()
	{
		/*

		alSourcePlay applied to an AL_INITIAL source will promote the source to
		AL_PLAYING, thus the data found in the buffer will be fed into the processing,
		starting at the beginning.

		alSourcePlay applied to a AL_PLAYING source will restart the source from the beginning.
		It will not affect the configuration, and will leave the source in AL_PLAYING state,
		but reset the sampling offset to the beginning.

		alSourcePlay applied to a AL_PAUSED source will resume processing using the source state as
		preserved at the alSourcePause operation.

		alSourcePlay applied to a AL_STOPPED source will propagate it to AL_INITIAL then
		to AL_PLAYING immediately.

		*/

		if (!alSource || !alBuffer)
			return;

		if (loop)
		{
			alSourcei(alSource, AL_LOOPING, AL_TRUE);
		}
		else
		{
			alSourcei(alSource, AL_LOOPING, AL_FALSE);
			alSourceQueueBuffers(alSource, 1, &alBuffer);
		}

		ended = false;
		alSourcePlay(alSource);
	}

	//////////////////////////////////////////////////////////////////////////////////////////////
	void pause()
	{
		/*

		alSourcePause applied to an AL_INITIAL source is a legal NOP.

		alSourcePause applied to a AL_PLAYING source will change its state to AL_PAUSED.
		The source is exempt from processing, its current state is preserved.

		alSourcePause applied to a AL_PAUSED source is a legal NOP.

		alSourcePause applied to a AL_STOPPED source is a legal NOP.

		*/

		if (!alSource || !alBuffer)
			return;

		alSourcePause(alSource);
	}

	//////////////////////////////////////////////////////////////////////////////////////////////
	void stop()
	{
		/*

		alSourceStop applied to an AL_INITIAL source is a legal NOP.

		alSourceStop applied to a AL_PLAYING source will change its state to AL_STOPPED.
		The source is exempt from processing, its current state is preserved.

		alSourceStop applied to a AL_PAUSED source will change its state to AL_STOPPED,
		with the same consequences as on a AL_PLAYING source.

		alSourceStop applied to a AL_STOPPED source is a legal NOP.

		*/

		if (!alSource || !alBuffer)
			return;

		alSourceStop(alSource);
	}

	//////////////////////////////////////////////////////////////////////////////////////////////
	void set_position(float pos)
	{
		if (!alSource || !alBuffer)
			return;

		alSourceStop(alSource);
		alSourcef(alSource, AL_SEC_OFFSET, pos);
	}

	//////////////////////////////////////////////////////////////////////////////////////////////
	float get_position()
	{
		if (!alSource || !alBuffer)
			return 0;

		float ret = 0.0f;
		alGetSourcef(alSource, AL_SEC_OFFSET, &ret);
		return ret;
	}

	//////////////////////////////////////////////////////////////////////////////////////////////
	void tick()
	{
		// Get OpenAL Source state
		ALint al_state;
		alGetSourcei(alSource, AL_SOURCE_STATE, &al_state);

		switch (al_state)
		{
		case AL_INITIAL:
			state = NATIVE_AUDIO_STATE_ENUM::AUDIO_STATE_INITIALIZED;
			break;

		case AL_STOPPED:

			// if previous state was playing and now is stopped, then audio completed
			if (state == NATIVE_AUDIO_STATE_ENUM::AUDIO_STATE_PLAYING)
				ended = true;

			state = NATIVE_AUDIO_STATE_ENUM::AUDIO_STATE_STOPPED;
			break;

		case AL_PAUSED:
			state = NATIVE_AUDIO_STATE_ENUM::AUDIO_STATE_PAUSED;
			break;

		case AL_PLAYING:
			state = NATIVE_AUDIO_STATE_ENUM::AUDIO_STATE_PLAYING;
			break;
		}
	}
};

#endif // __NATIVE_AUDIO_HPP__


