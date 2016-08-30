/* ***** BEGIN LICENSE BLOCK *****
*
* Copyright (C) 2016 www.mobilefx.com
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

#include "CocoAudioSystem.h"

// ==================================================================================================================================
//	   ______                 ___             ___      _____            __
//	  / ____/___  _________  /   | __  ______/ (_)___ / ___/__  _______/ /____  ____ ___
//	 / /   / __ \/ ___/ __ \/ /| |/ / / / __  / / __ \\__ \/ / / / ___/ __/ _ \/ __ `__ \
//	/ /___/ /_/ / /__/ /_/ / ___ / /_/ / /_/ / / /_/ /__/ / /_/ (__  ) /_/  __/ / / / / /
//	\____/\____/\___/\____/_/  |_\__,_/\__,_/_/\____/____/\__, /____/\__/\___/_/ /_/ /_/
//	                                                     /____/
// ==================================================================================================================================

ALCdevice* CocoAudioSystem::AudioDevice;
ALCcontext* CocoAudioSystem::AudioDeviceContext;
ov_callbacks CocoAudioSystem::vorbis_callbacks;

// This cache holds OpenAL Audio Buffer per asset file so
// that we don't reload audio files if used by multiple Clips
std::map<String, ALuint>* CocoAudioSystem::OpenALBuffersCache;

// This list holds CocoAudioSource objects and is used for tick()
Array<CocoAudioSource*>* CocoAudioSystem::AudioSources;

//////////////////////////////////////////////////////////////////////////////////////////////
// Vorbis Buffer Readers
//////////////////////////////////////////////////////////////////////////////////////////////

size_t CocoAudioSystem::ogg_from_memory_read(void* ptr, size_t size, size_t nmemb, void* datasource)
{
	return !datasource ? 0 : ((CocoAssetFile*) datasource)->read(ptr, size * nmemb);
}

int CocoAudioSystem::ogg_from_memory_seek(void* datasource, ogg_int64_t offset, int whence)
{
	return !datasource ? -1 : ((CocoAssetFile*) datasource)->seek((size_t) offset, (size_t) whence);
}

int CocoAudioSystem::ogg_from_memory_close(void* datasource)
{
	return 0;
}

long CocoAudioSystem::ogg_from_memory_tell(void* datasource)
{
	return !datasource ? -1 : ((CocoAssetFile*) datasource)->tell();
}

//////////////////////////////////////////////////////////////////////////////////////////////
// Audio System Initialize
//////////////////////////////////////////////////////////////////////////////////////////////

void CocoAudioSystem::init()
{
	// Setup Audio File Read Callbacks
	vorbis_callbacks.read_func = ogg_from_memory_read;
	vorbis_callbacks.seek_func = ogg_from_memory_seek;
	vorbis_callbacks.close_func = ogg_from_memory_close;
	vorbis_callbacks.tell_func = ogg_from_memory_tell;

	// Open default Audio Device
	AudioDevice = alcOpenDevice(nullptr);

	// Get Audio Device Context
	AudioDeviceContext = alcCreateContext(AudioDevice, nullptr);

	// Make Context Current
	alcMakeContextCurrent(AudioDeviceContext);

	// Allocate caches
	OpenALBuffersCache = new std::map<String, ALuint>();
	AudioSources = new Array<CocoAudioSource*>;
}

//////////////////////////////////////////////////////////////////////////////////////////////
// Audio System Terminate
//////////////////////////////////////////////////////////////////////////////////////////////

void CocoAudioSystem::quit()
{
	// Dispose Audio Cache
	while (AudioSources->begin() != AudioSources->end())
	{
		CocoAudioSource* audio = *(AudioSources->begin());
		delete audio;
	}
	delete AudioSources;
	AudioSources = nullptr;

	// Dispose Audio Buffers
	while (OpenALBuffersCache->begin() != OpenALBuffersCache->end())
	{
		alDeleteBuffers(1, &OpenALBuffersCache->begin()->second);
		OpenALBuffersCache->erase(OpenALBuffersCache->begin());
	}
	delete OpenALBuffersCache;
	OpenALBuffersCache = nullptr;

	// Release Audio Device
	alcMakeContextCurrent(nullptr);
	alcDestroyContext(AudioDeviceContext);
	alcCloseDevice(AudioDevice);
}

//////////////////////////////////////////////////////////////////////////////////////////////
CocoAudioSource* CocoAudioSystem::NewSource(String src)
{
	// Audio System initialized?
	if (!AudioSources) return nullptr;

	// Create an audio source
	CocoAudioSource* audio = new CocoAudioSource;
	AudioSources->push(audio);

	// Check if audio file is already loaded into an OpenAL buffer
	auto buffer = OpenALBuffersCache->find(src);

	if (buffer != OpenALBuffersCache->end())
	{
		// Get OpenAL Buffer ID for this Audio Asset
		audio->alBuffer = buffer->second;
	}
	else
	{
		// Open Asset File
		CocoAssetFile* asset_file_stream = CocoAssetFile::open(src);
		if (asset_file_stream)
		{
			// Pass asset file to Vorbis OGG Format Reader
			OggVorbis_File vorbis_file;
			if (ov_open_callbacks(asset_file_stream, &vorbis_file, nullptr, 0, CocoAudioSystem::vorbis_callbacks) == 0)
			{
				// Get Audio stream info
				vorbis_info* vorbis_audio_info = ov_info(&vorbis_file, -1);
				ALsizei alFrequency = (ALsizei) vorbis_audio_info->rate;
				ALenum alFormat = vorbis_audio_info->channels == 1 ? AUDIO_FORMAT_MONO : AUDIO_FORMAT_STEREO;

				// Get duration in seconds
				audio->duration = ov_time_total(&vorbis_file, -1);

				// Get total pcm samples of the physical bitstream
				ogg_int64_t total_pcm_samples = ov_pcm_total(&vorbis_file, -1);

				// Allocate memory for all samples
				ogg_int64_t total_pcm_samples_bytes = total_pcm_samples * AUDIO_SAMPLE_SIZE * vorbis_audio_info->channels;
				unsigned char* pcm_samples_bytes_buffer = new unsigned char[(size_t) total_pcm_samples_bytes];

				// Read Audio Samples
				int ovSection = 0;
				long samples_bytes_read = 0;
				ov_pcm_seek(&vorbis_file, 0);
				while (samples_bytes_read < total_pcm_samples_bytes)
				{
					#ifdef WIN32_APPLICATION
						samples_bytes_read += ov_read(&vorbis_file, (char*) pcm_samples_bytes_buffer + samples_bytes_read, 4096, 0, 2, 1, &ovSection);
					#else
						samples_bytes_read += ov_read(&vorbis_file, (char*)(pcm_samples_bytes_buffer + samples_bytes_read), 4096, &ovSection);
					#endif
				}

				// Clear the decoder's buffers.
				ov_clear(&vorbis_file);

				if (samples_bytes_read > 0)
				{
					// Generate a OpenAL Buffer and fill it with PCM data
					alGenBuffers(1, &(audio->alBuffer));
					alBufferData(audio->alBuffer, alFormat, pcm_samples_bytes_buffer, (ALsizei) total_pcm_samples_bytes, alFrequency);

					// Cache OpenAL Buffer
					(*OpenALBuffersCache)[src] = audio->alBuffer;
				}

				// Release pcm buffer
				delete[] pcm_samples_bytes_buffer;
			}
		}

		// Release asset file
		delete asset_file_stream;
	}

	// If Audio Buffer exists, we create a new OpenAL Source and bind them together
	if (audio->alBuffer)
	{
		ALint sizeInBytes;
		ALint channels;
		ALint bits;
		ALint frequency;
		ALint lengthInSamples;
		ALdouble durationInSeconds;

		// Create OpenAL Source
		alGenSources(1, &(audio->alSource));

		// Setup Source
		alSourcef(audio->alSource, AL_GAIN, 1.0f);
		alSourcef(audio->alSource, AL_PITCH, 1.0f);

		// Bind Audio Buffer to Source
		alSourcei(audio->alSource, AL_BUFFER, (ALint) audio->alBuffer);

		// Query Buffer to get its size
		alGetBufferi(audio->alBuffer, AL_SIZE, &sizeInBytes);
		alGetBufferi(audio->alBuffer, AL_CHANNELS, &channels);
		alGetBufferi(audio->alBuffer, AL_BITS, &bits);
		alGetBufferi(audio->alBuffer, AL_FREQUENCY, &frequency);

		// Calculate duration
		lengthInSamples = sizeInBytes * 8 / (channels * bits);
		durationInSeconds = (float) lengthInSamples / (float) frequency;

		// Keep duration in audio object
		audio->duration = durationInSeconds;

		// Set src
		audio->src = src;
	}

	return audio;
}

//////////////////////////////////////////////////////////////////////////////////////////////
void CocoAudioSystem::DisposeSource(CocoAudioSource* source)
{
	if (!AudioSources || !source) return;

	// Remove current source
	int32_t index = AudioSources->indexOf(source);
	if (index != -1)
	{
		AudioSources->splice(index, 1);
	}

	// Find how many sources use the same audio buffer.
	uint32_t count = 0;
	for (auto src = AudioSources->begin(); src != AudioSources->end(); src++)
	{
		if ((*src)->alBuffer == source->alBuffer)
			count++;
	}

	// If the audio buffer is not used any more, dispose it
	if (!count)
	{
		alDeleteBuffers(1, &(source->alBuffer));
		OpenALBuffersCache->erase(OpenALBuffersCache->find(source->src));
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////
void CocoAudioSystem::tick()
{
	if (!AudioSources) return;
	for (auto it = AudioSources->begin(); it != AudioSources->end(); it++)
		(*it)->tick();
}
