/* ***** BEGIN LICENSE BLOCK *****
 *
 * Copyright (C) 2013-2014 www.coconut2D.org
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

#ifndef _AssetFile_h
#define _AssetFile_h

#include "Coconut2D.hpp"

//////////////////////////////////////////////////////////////////////////////////////////////
class AssetFile//	: public AutoGC<AssetFile>
{
protected:

	// Set the global folders for loading resources.
	// Especially for Android we also need to define an assets path.
	static char* filesPath;
	static char* assetPath;
    static AAssetManager* manager;

protected:
    union {
    	FILE* fd;
    	AAsset* ad;
    } ptr;
    char* file;
	unsigned char* data;
	size_t cursor;
    bool isAsset;
	size_t length;

public:

	enum Type {
		TYPE_FILE,
		TYPE_ASSET,
		TYPE_DATA
	} type;

	enum MIME {
		IMAGE_PNG,
		IMAGE_JPG,
		AUDIO_OGG,
		FONT_TTF,
		MIME_OTHER
	} mime;
	// ==================================================================================================================================
	//	   _____ __        __  _
	//	  / ___// /_____ _/ /_(_)____
	//	  \__ \/ __/ __ `/ __/ / ___/
	//	 ___/ / /_/ /_/ / /_/ / /__
	//	/____/\__/\__,_/\__/_/\___/
	//
	// ==================================================================================================================================

	//////////////////////////////////////////////////////////////////////////////////////////////
	static void init(AAssetManager* i_manager, const char* str)
	{
		assetPath = strdup("");
		filesPath = strdup(str);
		manager = i_manager;
	}

	//////////////////////////////////////////////////////////////////////////////////////////////
	static void quit()
    {
    	manager = nullptr;
        free(filesPath); filesPath = nullptr;
        free(assetPath); assetPath = nullptr;
    }

	//////////////////////////////////////////////////////////////////////////////////////////////
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

	//////////////////////////////////////////////////////////////////////////////////////////////
	static AssetFile* open(const char* str)
    {
		if(!strncmp(str, "data:", 5))
		{
			if(!strncmp(str + 5, "image/png;base64,", 17))
				return createFromBase64(str + 22, IMAGE_PNG);
			else if(!strncmp(str + 5, "image/jpg;base64,", 17))
				return createFromBase64(str + 22, IMAGE_JPG);
			else if(!strncmp(str + 5, "audio/ogg;base64,", 17))
				return createFromBase64(str + 22, AUDIO_OGG);
			else if(!strncmp(str + 5, "font/ttf;base64,", 16))
				return createFromBase64(str + 21, FONT_TTF);
			else
			{
				trace("ERROR(AssetFile.h): Unsupported data");
				return nullptr;
			}
		}
        if(str && strlen(str) > 2 && str[0] == '.' && str[1] == '/')
        {
            if(exists(str, false))
				return new AssetFile(str, false);
            else if(exists(str, true))
				return new AssetFile(str, true);
        }
		trace("ERROR(AssetFile.h): File does not exist %s", str);
		return NULL;
    }

	//////////////////////////////////////////////////////////////////////////////////////////////
    static bool create(const char* str)
    {
		return createWithData(str, nullptr);
    }

	//////////////////////////////////////////////////////////////////////////////////////////////
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

	//////////////////////////////////////////////////////////////////////////////////////////////
	static AssetFile* createFromBase64(const char* str, MIME mime)
	{
		static const unsigned char unb64[] = { 62, 0, 0, 0, 63, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 0, 0, 0, 0, 0, 0, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51 };
		size_t len = strlen(str);
		if(len < 2) return nullptr;
		int pad = 0;
		if(str[len - 1] == '=') pad++;
		if(str[len - 2] == '=') pad++;
		AssetFile* ret = new AssetFile(3 * len / 4 - pad);
		ret->mime = mime;
		size_t i, c = 0;
		unsigned char A, B, C, D;
		for(i = 0; i < len - 4 - pad; i += 4)
		{
			A = unb64[str[i] - 43];
			B = unb64[str[i + 1] - 43];
			C = unb64[str[i + 2] - 43];
			D = unb64[str[i + 3] - 43];

			ret->data[c++] = (A << 2) | (B >> 4);
			ret->data[c++] = (B << 4) | (C >> 2);
			ret->data[c++] = (C << 6) | (D);
		}
		if(pad == 1)
		{
			A = unb64[str[i] - 43];
			B = unb64[str[i + 1] - 43];
			C = unb64[str[i + 2] - 43];

			ret->data[c++] = (A << 2) | (B >> 4);
			ret->data[c++] = (B << 4) | (C >> 2);
		}
		else if(pad == 2)
		{
			A = unb64[str[i] - 43];
			B = unb64[str[i + 1] - 43];

			ret->data[c++] = (A << 2) | (B >> 4);
		}
		return ret;
	}

	// ==================================================================================================================================
	//	    ____           __
	//	   /  _/___  _____/ /_____ _____  ________
	//	   / // __ \/ ___/ __/ __ `/ __ \/ ___/ _ \
	//	 _/ // / / (__  ) /_/ /_/ / / / / /__/  __/
	//	/___/_/ /_/____/\__/\__,_/_/ /_/\___/\___/
	//
	// ==================================================================================================================================

	AssetFile(size_t i_length) : file(nullptr), data(nullptr), cursor(0), length(i_length), type(TYPE_DATA), mime(MIME_OTHER)
	{
		data = new unsigned char[length];
	}

	AssetFile(const char* str, bool i_isAsset) : file(nullptr), data(nullptr), isAsset(i_isAsset), length(0), mime(MIME_OTHER)
	{
		char* ld = (char*) strrchr(str, '.');
        if(!ld)
        {
            trace("ERROR(AssetFile.h): Invalid file %s", str);
            return;
        }
        else
        {
            ld++;
            if(!strncmp(ld, "jpg", 3)) mime = IMAGE_JPG;
            else if(!strncmp(ld, "png", 3)) mime = IMAGE_PNG;
			else if(!strncmp(ld, "ogg", 3)) mime = AUDIO_OGG;
			else if(!strncmp(ld, "ttf", 3)) mime = FONT_TTF;
		}
        if(isAsset && assetPath && str)
        {
			type = TYPE_ASSET;
            std::string temps(assetPath);
            temps += str + 2;
            file = strdup(temps.c_str());
        	ptr.ad = AAssetManager_open(manager, file, AASSET_MODE_BUFFER);
			if (ptr.ad)
			{
				length = AAsset_getLength(ptr.ad);
			}
			else
			{
				trace("ERROR(AssetFile.h): open asset failed %s", file);
			}
        }
        else if(!isAsset && filesPath && str)
        {
			type = TYPE_FILE;
            std::string temps(filesPath);
            temps += str + 2;
            file = strdup(temps.c_str());
            ptr.fd = fopen(file, "rb+");
            if(ptr.fd)
			{
                fseek(ptr.fd, 0, SEEK_END);
                length = ftell(ptr.fd);
                rewind(ptr.fd);
			}
			else
			{
				trace("ERROR(AssetFile.h): open file failed %s", file);
			}
        }
	}

	//////////////////////////////////////////////////////////////////////////////////////////////
	~AssetFile()
	{
		if(isAsset && ptr.ad) AAsset_close(ptr.ad);
		else if(!isAsset && ptr.fd) fclose(ptr.fd);
        if(file) delete[] file;
        if(data) delete[] data;
	}
    unsigned char* getData()
    {
        if(!data)
        {
        	data = new unsigned char[length + 1];
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
	inline int seek(long int offset, int origin)
	{
		switch(type)
		{
			case TYPE_FILE:
				return fseek(ptr.fd, offset, origin);
			case TYPE_ASSET:
				return AAsset_seek(ptr.ad, offset, origin);
			case TYPE_DATA:
				switch(origin)
				{
					case SEEK_SET: cursor = offset; break;
					case SEEK_CUR: cursor += offset; break;
					case SEEK_END: cursor = length - offset; break;
				}
				return 0;
		}
		return -1;
    }
	inline long int tell()
    {
		switch(type)
		{
			case TYPE_FILE:
				return ftell(ptr.fd);
			case TYPE_ASSET:
    			return length - AAsset_getRemainingLength(ptr.ad);
			case TYPE_DATA:
				return cursor;
		}
    	return -1;
    }
	inline size_t read(void* dest, size_t size)
    {
		switch(type)
		{
			case TYPE_FILE:
				return fread(dest, 1, size, ptr.fd);
			case TYPE_ASSET:
    			return AAsset_read(ptr.ad, dest, size);
			case TYPE_DATA:
				size_t ret = size;
				if(ret + cursor > length) ret = length - cursor;
				memcpy(dest, data + cursor, ret);
				cursor += ret;
				return ret;
		}
		return 0;
    }
    size_t write(const void* src, size_t size)
    {
    	if(!isAsset && ptr.fd)
    		return fwrite(src, 1, size, ptr.fd);
    	trace("ERROR(AssetFile.h): write file failed %s", file);
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
