#ifndef _fxAudioStream_h
#define _fxAudioStream_h

#include "Common.h"
#include "fxFile.h"

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
    #endif /* ENABLE_OPENAL_SUPPORT */
private:
    static std::map<fxObjectUID, fxAudioStream*>* audios;
    
protected:
    bool loop;
    size_t playCount;
    
    union
    {
        fxFile* file;
    } data;
    
    enum class Type : uint8_t
    {
        NONE = 0,
        OGG
    } type;
    
    enum class State : uint8_t
    {
        NONE = 0,
        STOPPED,
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
    void _tick();
};

#endif
