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

#ifndef _fxAudioStream_h
#define _fxAudioStream_h

#include "AssetFile.h" // <- Device Specific

class fxAudioStream
{
    #ifdef ENABLE_OGG_SUPPORT
    private:
        static ov_callbacks ovc;
    public:
        static size_t ogg_from_memory_read(void* ptr, size_t size, size_t nmemb, void* datasource);
        static int ogg_from_memory_seek(void* datasource, ogg_int64_t offset, int whence);
        static int ogg_from_memory_close(void* datasource);
        static long ogg_from_memory_tell(void* datasource);
    #endif /* ENABLE_OGG_SUPPORT */

    #ifdef ENABLE_OPENAL_SUPPORT
    private:
        static ALCdevice* alcDevice;
        static ALCcontext* alcContext;
    protected:
        ALuint alBuffer;
        ALuint alSource;
		static std::map<std::string, ALuint>* buffers;
    #endif /* ENABLE_OPENAL_SUPPORT */
private:
    static std::map<fxObjectUID, fxAudioStream*>* audios;

protected:
    bool loop;
    size_t playCount;

    enum class Type : uint8_t
    {
        NONE = 0,
        OGG
    } type;

    enum class State : uint8_t
    {
        NONE = 0,
        STOPPED,
		PAUSED,
        PLAYING
    } state;

public:
    fxAudioStream(const char* str);
    ~fxAudioStream();

    static void add(fxObjectUID uid, const char* str);
    static void remove(fxObjectUID uid);
    static fxAudioStream* get(fxObjectUID uid);
    static void init();
    static void quit();
    static void tick();

    void play(size_t i_playCount = 1);
    void setloop(bool i_loop);
    void stop();
	void set_position(float pos);
	float get_position();
	bool isStopped();
	bool isPaused();
    void _tick();
};

#endif


