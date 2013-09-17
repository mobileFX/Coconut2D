#ifndef fxCore_fxAsset_h
#define fxCore_fxAsset_h

#include "Defines.h"
#include "png.h"
#include "jpeglib.h"
#include "ft2build.h"
#include FT_FREETYPE_H

class fxFile
{
private:
	static char* filesPath;
    static char* assetPath;
    
protected:
    void* fd;
    char* file;
    char* data;
    bool isAsset;
	size_t length;
    
public:
	static void init(const char* i_filesPath, const char* i_assetPath)
	{
        filesPath = strdup(i_filesPath);
        assetPath = strdup(i_assetPath);
	}
    static void quit()
    {
        free(filesPath); filesPath = nullptr;
        free(assetPath); assetPath = nullptr;
    }
    /*fxFile(fxFile&& old)
    {
        fd = old.fd; old.fd = nullptr;
        file = old.file; old.file = nullptr;
        data = old.data; old.data = nullptr;
        length = old.length;
        isAsset = old.isAsset;
    }*/
    static bool exists(const char* str, bool isAsset)
    {
        if(isAsset && assetPath && str)
        {
            std::string temps(assetPath);
            temps += str + 2;
            FILE* f = fopen(temps.c_str(), "rb");
            if(f) fclose(f);
            return false;
        }
        else if(!isAsset && filesPath && str)
        {
            std::string temps(filesPath);
            temps += str + 2;
            FILE* f = fopen(temps.c_str(), "rb");
            if(f) fclose(f);
            else return false;
        }
        else return false;
        return true;
    }
    static bool create(const char* str)
    {
        return createWithData(str, nullptr, 0);
    }
    static bool createWithData(const char* str, const char* data, size_t size = 0)
    {
        if(filesPath && str)
        {
            std::string temps(filesPath);
            temps += str + 2;
            FILE* f = fopen(temps.c_str(), "wb");
            if(f)
            {
                if(data)
                {
                    if(!size) size = strlen(data);
                    fwrite(data, 1, size, f);
                }
                fclose(f);
            }
            else return false;
        }
        else return false;
        return true;
    }
	fxFile(const char* str, bool i_isAsset) : fd(nullptr), file(nullptr), data(nullptr), isAsset(i_isAsset), length(0)
	{
        if(isAsset && assetPath && str)
        {
            std::string temps(assetPath);
            temps += str + 2;
            file = strdup(temps.c_str());
            fd = fopen(file, "rb");
            if(fd)
			{
                fseek((FILE*)fd, 0, SEEK_END);
                length = ftell((FILE*)fd);
                rewind((FILE*)fd);
				LOGI("ASSET OPEN(\"%s\")!\n", str);
			}
			else LOGI("ASSET ERROR OPEN: %s\n", file);
        }
        else if(!isAsset && filesPath && str)
        {
            std::string temps(filesPath);
            temps += str + 2;
            file = strdup(temps.c_str());
            fd = fopen(file, "rb+");
            if(fd)
			{
                fseek((FILE*)fd, 0, SEEK_END);
                length = ftell((FILE*)fd);
                rewind((FILE*)fd);
				LOGI("FILE OPEN(\"%s\")!\n", str);
			}
			else LOGI("FILE ERROR OPEN: %s\n", file);
        }
	}
	~fxFile()
	{
        if(fd)
        {
            fclose((FILE*)fd);
            fd = nullptr;
        }
        delete[] file;
        delete[] data;
	}
    char* getData()
    {
        if(!fd) return nullptr;
        if(!data)
        {
            rewind((FILE*)fd);
            data = new char[length + 1];
            data[length] = 0;
            fread(data, 1, length, (FILE*)fd);
        }
        return data;
    }
	inline const size_t& getLength() const { return length; }
    inline const char* getFullPath() const { return file; }
    
    // standard io functions pass-through
    // they update only the file, not the data!
    inline int seek(long int offset, int origin) { return fseek((FILE*)fd, offset, origin); }
    inline long int tell() { return ftell((FILE*)fd); }
    inline size_t read(void* dest, size_t size) { return fread(dest, 1, size, (FILE*)fd); }
    inline size_t write(const void* src, size_t size) { return fwrite(src, 1, size, (FILE*)fd); }
    inline int flush() { return fflush((FILE*)fd); }
};

class fxArgs : public fxFile
{
protected:
    int argc;
    char** argv;
    
public:
    static fxArgs* Args;
    static void init(const char* str, bool isAsset = true)
    {
        Args = new fxArgs(str, isAsset);
    }
    static void quit()
    {
        delete Args;
    }
    fxArgs(const char* str, bool isAsset = true) : fxFile(str, isAsset), argc(1), argv(nullptr)
    {
        argv = (char**)malloc(sizeof(char*));
        argv[0] = nullptr;
        
        char* data = getData();
        char* pos;
        while((pos = strchr(data, '\n')))
        {
            *pos = 0;
            argv = (char**)realloc(argv, sizeof(char*) * (argc + 1));
            argv[argc] = data;
            argc++;
            data = pos + 1;
        }
    }
    ~fxArgs()
    {
        free(argv);
    }
    inline int getArgc() { return argc; }
    inline char** getArgv() { return argv; }
};

class fxFontFace : public fxFile
{
private:
    static FT_Library ftLibrary;
    static std::map<std::string, fxFontFace*> fonts;
protected:
    FT_Face ftFace;
    bool ftKerning;
public:
    static void add(const char* str, bool isAsset = true)
    {
        std::string name(str);
        name = name.substr(name.find_last_of("/\\") + 1);
        name = name.substr(0, name.find_last_of("."));
        fonts.insert(std::pair<std::string, fxFontFace*>(name, new fxFontFace(str, isAsset)));
        LOGI("@font-face %s loaded\n", name.c_str());
    }
    static const fxFontFace* get(const char* str)
    {
        std::map<std::string, fxFontFace*>::iterator it = fonts.find(std::string(str));
        if(it != fonts.end()) return it->second;
        return nullptr;
    }
    static void init()
    {
        if(FT_Init_FreeType(&ftLibrary)) { LOGW("Could not initialize FreeType library!\n"); }
        else { LOGI("FreeType OK!\n"); }
    }
    static void quit()
    {
        std::map<std::string, fxFontFace*>::iterator it = fonts.begin();
        while(it != fonts.end()) delete (it++)->second;
        fonts.clear();
        FT_Done_FreeType(ftLibrary);
    }
    
    /*fxFontFace(fxFontFace&& old) : fxFile(std::move(old))
    {
        ftFace = old.ftFace;
        old.ftFace = nullptr;
    }*/
    fxFontFace(const char* str, bool isAsset) : fxFile(str, isAsset), ftFace(nullptr)
    {
        int er = 0;
        if((er = FT_New_Memory_Face(ftLibrary, (const FT_Byte*)getData(), length, 0, &ftFace)))
        {
            LOGW("Could not load FreeType Face(%d)!\n", er);
        }
        /*else if(FT_Select_Charmap(ftFace, FT_ENCODING_UNICODE))
         {
         LOGW("Could not select UNICODE encoding!\n");
         }*/
        ftKerning = FT_HAS_KERNING(ftFace);
    }
    ~fxFontFace()
    {
        if(!ftFace) return;
        FT_Done_Face(ftFace);
        ftFace = nullptr;
    }
    inline FT_Face getFace() const { return ftFace; }
    inline bool hasKerning() const { return ftKerning; }
};

#endif /* fxCore_fxAsset_h */
