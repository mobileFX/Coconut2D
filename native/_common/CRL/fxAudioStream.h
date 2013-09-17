#ifndef FXAUDIO_H
#define FXAUDIO_H

#include "Defines.h"
#include "fxAsset.h"

class fxAudioStream : public fxFile
{
private:
    // OGG
    static ov_callbacks ovc;

    // OpenAL Soft
    static ALCdevice* alcDevice;
    static ALCcontext* alcContext;

    // Custom
    static std::map<fxObjectUID, fxAudioStream*>* audios;

protected:

    // OpenAL Soft
    ALuint alBuffer;
    ALuint alSource;

    // Custom
    bool loop;
    size_t playCount;

    enum class State : uint8_t
    {
        NONE = 0,
        STOPPED,
        PLAYING
    } state;

public:
    fxAudioStream(fxAudioStream&& old);
    fxAudioStream(const char* str, bool isAsset = true);
    ~fxAudioStream();

    // OGG
    static size_t ogg_from_memory_read(void* ptr, size_t size, size_t nmemb, void* datasource);
    static int ogg_from_memory_seek(void* datasource, ogg_int64_t offset, int whence);
    static int ogg_from_memory_close(void* datasource);
    static long ogg_from_memory_tell(void* datasource);

    static void add(fxObjectUID uid, const char* str);
    static void remove(fxObjectUID uid);
    static fxAudioStream* get(fxObjectUID uid);
    static void init();
    static void quit();
    static void tick();

    void play(size_t i_playCount = 1);
    void setloop(bool i_loop);
    void stop();
    void _tick();
};

#endif // FXAUDIO_H
