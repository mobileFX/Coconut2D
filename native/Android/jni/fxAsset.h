#ifndef fxCore_fxAsset_h
#define fxCore_fxAsset_h

#include "Defines.h"
#include <cstring>
#include "png.h"
#include "jpeglib.h"
#include "ivorbisfile.h"
#include "ft2build.h"
#include FT_FREETYPE_H

class fxFile
{
private:
	static char* filesPath;
    static char* assetPath;
    static AAssetManager* manager;

protected:
    union {
    	FILE* fd;
    	AAsset* ad;
    } ptr;
    void* fd;
    char* file;
    char* data;
    bool isAsset;
	size_t length;

public:
	static void init(AAssetManager* i_manager, const char* str)
	{
		assetPath = strdup("file:///android_asset/");
		filesPath = strdup(str);
		manager = i_manager;
	}
    static void quit()
    {
    	manager = nullptr;
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
            AAsset* a = AAssetManager_open(manager, temps.c_str(), AASSET_MODE_UNKNOWN);
            if(a) AAsset_close(a);
            else return false;
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
        return createWithData(str, nullptr);
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
        	ptr.ad = AAssetManager_open(manager, str + 2, AASSET_MODE_BUFFER);
			if (ptr.ad)
			{
				length = AAsset_getLength(ptr.ad);
				LOGI("ASSET OPEN(\"%s\")!\n", str);
			}
			else LOGI("ASSET ERROR OPEN: %s\n", str);
        }
        else if(!isAsset && filesPath && str)
        {
            std::string temps(filesPath);
            temps += str + 2;
            file = strdup(temps.c_str());
            ptr.fd = fopen(file, "rb+");
            if(ptr.fd)
			{
                fseek(ptr.fd, 0, SEEK_END);
                length = ftell(ptr.fd);
                rewind(ptr.fd);
				LOGI("FILE OPEN(\"%s\")!\n", str);
			}
			else LOGI("FILE ERROR OPEN: %s\n", file);
        }
	}
	~fxFile()
	{
        if(isAsset && ptr.ad) AAsset_close(ptr.ad);
        else if(!isAsset && ptr.fd) fclose(ptr.fd);
        delete[] file;
        delete[] data;
	}
    char* getData()
    {
        if(!data)
        {
            data = new char[length + 1];
            data[length] = 0;
            seek(0, SEEK_SET);
            read(data, length);
        }
        return data;
    }
	inline const size_t& getLength() const { return length; }
    inline const char* getFullPath() const { return file; }

    // standard io functions pass-through
    // they update only the file, not the data!
    int seek(long int offset, int origin)
    {
    	if(isAsset && ptr.ad)
    		return AAsset_seek(ptr.ad, offset, origin);
    	else if(!isAsset && ptr.fd)
    		return fseek(ptr.fd, offset, origin);
    	LOGW("Error fxFile::seek(%ld, %d)\n", offset, origin);
    	return -1;
    }
    long int tell()
    {
    	if(isAsset && ptr.ad)
    		return length - AAsset_getRemainingLength(ptr.ad);
    	else if(!isAsset && ptr.fd)
    		return ftell(ptr.fd);
    	LOGW("Error fxFile::tell()\n");
    	return -1;
    }
    size_t read(void* dest, size_t size)
    {
    	if(isAsset && ptr.ad)
    		return AAsset_read(ptr.ad, dest, size);
    	else if(!isAsset && ptr.fd)
    		return fread(dest, 1, size, ptr.fd);
    	LOGW("Error fxFile::read(0x%08x, %llu)\n", dest, size);
    	return 0;
    }
    size_t write(const void* src, size_t size)
    {
    	if(!isAsset && ptr.fd)
    		return fwrite(src, 1, size, ptr.fd);
    	LOGW("Error fxFile::write(%s, %llu)\n", src, size);
    	return 0;
    }
    int flush()
    {
    	if(!isAsset && ptr.fd)
    		return fflush(ptr.fd);
    	return -1;
    }
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

/*class fxAsset
{
private:
	constexpr static const char* path = "assets:///";
	static AAssetManager* manager;
	static fxAsset* jsArgs;

protected:
	size_t length;
	size_t offset;
	char* data;
	char* file;
public:
	static int argc;
	static char** argv;

	static void init(AAssetManager* i_manager, const char* str)
	{
		manager = i_manager;

		jsArgs = new fxAsset(str);
		char* data = jsArgs->getData();
		char* pos;
		argc = 1;
		argv = (char**)malloc(sizeof(char*));
		argv[0] = nullptr;
		while((pos = strchr(data, '\n')))
		{
			*pos = 0;
			argv = (char**)realloc(argv, sizeof(char*) * (argc + 1));
			argv[argc] = data;
			LOGI("argv[%d] = \"%s\"", argc, argv[argc]);
			argc++;
			data = pos + 1;
		}
	}
	static void quit()
	{
		free(argv);
		argv = nullptr;
		delete jsArgs;
		jsArgs = nullptr;
		manager = nullptr;
	}
    fxAsset(fxAsset&& old)
    {
        data = old.data;
        old.data = nullptr;
        file = old.file;
        old.file = nullptr;
        length = old.length;
        offset = old.offset;
    }
	fxAsset(const char* str) : length(0), offset(0), data(nullptr), file(nullptr)
	{
		if(manager && str)
		{
			size_t len = strlen(str) + strlen(path);
			file = new char[len - 1];
			strcpy(file, path);
			strcat(file, str + 2);
			LOGI("loading file: %s\n", str);
			AAsset* asset = AAssetManager_open(manager, str + 2, AASSET_MODE_BUFFER);
			if (asset)
			{
				length = AAsset_getLength(asset);
				data = new char[length + 1];
				data[length] = 0;
				if(AAsset_read(asset, data, length) > 0)
					LOGI("ASSET READ!\n");
				else LOGI("ASSET ERROR READ!\n");
				AAsset_close(asset);
			}
			else LOGI("ASSET ERROR OPEN!\n");
		}
	}
	~fxAsset()
	{
		delete[] data;
		delete[] file;
	}
	inline char* getData() { return data; }
	inline const size_t& getLength() { return length; }
	inline const char* getFullPath() const { return file; }
	inline const size_t& getOffset() { return offset; }
	inline int setOffset(const size_t& i_offset)
	{
		if(i_offset > length) return -1;
		offset = i_offset;
		return 0;
	}
	size_t read(void* dest, const size_t& size) {
		size_t ret = std::min(length - offset, size);
		memcpy(dest, data + offset, ret);
		offset += ret;
		return ret;
	}
};*/

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
