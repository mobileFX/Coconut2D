#ifndef _fxFile_h
#define _fxFile_h

#include "cstdio"
#include "Coconut2D.hpp"

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
    char* file;
    char* data;
    bool isAsset;
	size_t length;

public:
	static void init(AAssetManager* i_manager, const char* str)
	{
		assetPath = strdup("web/");
		filesPath = strdup(str);
		manager = i_manager;
	}
    static void quit()
    {
    	manager = nullptr;
        free(filesPath); filesPath = nullptr;
        free(assetPath); assetPath = nullptr;
    }
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
    static fxFile* open(const char* str)
    {
        fxFile* ret = nullptr;
        if(str && strlen(str) > 2 && str[0] == '.' && str[1] == '/')
        {
            if(exists(str, false)) ret = new fxFile(str, false);
            else if(exists(str, true)) ret = new fxFile(str, true);
            else LOGW("Could not open file: %s\n", str);
        }
        return ret;
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
	fxFile(const char* str, bool i_isAsset) : file(nullptr), data(nullptr), isAsset(i_isAsset), length(0)
	{
        if(isAsset && assetPath && str)
        {
            std::string temps(assetPath);
            temps += str + 2;
            file = strdup(temps.c_str());
        	ptr.ad = AAssetManager_open(manager, file, AASSET_MODE_BUFFER);
			if (ptr.ad)
			{
				length = AAsset_getLength(ptr.ad);
				LOGI("ASSET OPEN(\"%s\")!\n", str);
			}
			else LOGI("ASSET ERROR OPEN: %s\n", file);
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
    	LOGW("Error fxFile::read(0x%08x, %zu)\n", (size_t)dest, size);
    	return 0;
    }
    size_t write(const void* src, size_t size)
    {
    	if(!isAsset && ptr.fd)
    		return fwrite(src, 1, size, ptr.fd);
    	LOGW("Error fxFile::write(%s, %zu)\n", (const char*)src, size);
    	return 0;
    }
    int flush()
    {
    	if(!isAsset && ptr.fd)
    		return fflush(ptr.fd);
    	return -1;
    }
};

#endif
