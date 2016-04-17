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
class CocoAssetFile//	: public AutoGC<CocoAssetFile>
{
protected:

	static char* filesPath;
	static char* assetPath;

	void* fd;
	char* file;
	uint8_t* data;
	size_t cursor;
	bool isAsset;
	size_t length;

public:

	enum Type
	{
		TYPE_FILE,
		TYPE_ASSET,
		TYPE_DATA
	} type;

	enum MIME
	{
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
	static void init(const char* FilesPath, const char* AssetPath)
	{
		filesPath = strdup(FilesPath);
		assetPath = strdup(AssetPath);
	}

	//////////////////////////////////////////////////////////////////////////////////////////////
	static void quit()
	{
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
            FILE* f = fopen(temps.c_str(), "rb");
			if(f)
				fclose(f);
            else
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

	//////////////////////////////////////////////////////////////////////////////////////////////
	static CocoAssetFile* open(const char* str)
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
				trace("Unsupported data");
				return nullptr;
			}
		}
		#ifdef __XMLHTTPREQUEST_HPP__
		if(!strncmp(str, "http://", 7) || !strncmp(str, "https://", 8))
		{
			XMLHttpRequest* req = new XMLHttpRequest();
			CocoAssetFile* ret = req->data;
			req->freeData = false;
			req->open("get", str, false);
			req->send();
			delete req;
			return ret;
		}
		#endif
        if(str && strlen(str) > 2 && str[0] == '.' && str[1] == '/')
        {
            if(exists(str, false))
				return new CocoAssetFile(str, false);
            else if(exists(str, true))
				return new CocoAssetFile(str, true);
        }
		trace("File does not exist");
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
	static CocoAssetFile* createFromBase64(const char* str, MIME mime)
	{
		static const unsigned char unb64[] = { 62, 0, 0, 0, 63, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 0, 0, 0, 0, 0, 0, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51 };
		size_t len = strlen(str);
		if(len < 2) return nullptr;
		size_t pad = 0;
		if(str[len - 1] == '=') pad++;
		if(str[len - 2] == '=') pad++;
		CocoAssetFile* ret = new CocoAssetFile(3 * len / 4 - pad);
		ret->mime = mime;
		size_t i, c = 0;
		unsigned char A, B, C, D;
		for(i = 0; i < len - 4 - pad; i += 4)
		{
			A = unb64[str[i] - 43];
			B = unb64[str[i + 1] - 43];
			C = unb64[str[i + 2] - 43];
			D = unb64[str[i + 3] - 43];

			ret->data[c++] = (uint8_t) (((A << 2) | (B >> 4)) & 0xFF);
			ret->data[c++] = (uint8_t) (((B << 4) | (C >> 2)) & 0xFF);
			ret->data[c++] = (uint8_t) (((C << 6) | (D))  & 0xFF);
		}
		if(pad == 1)
		{
			A = unb64[str[i] - 43];
			B = unb64[str[i + 1] - 43];
			C = unb64[str[i + 2] - 43];

			ret->data[c++] = (uint8_t) (((A << 2) | (B >> 4)) & 0xFF);
			ret->data[c++] = (uint8_t) (((B << 4) | (C >> 2)) & 0xFF);
		}
		else if(pad == 2)
		{
			A = unb64[str[i] - 43];
			B = unb64[str[i + 1] - 43];

			ret->data[c++] = (uint8_t) (((A << 2) | (B >> 4)) & 0xFF);
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

	CocoAssetFile(size_t i_length) : fd(nullptr), file(nullptr), data(nullptr), cursor(0), length(i_length), type(TYPE_DATA), mime(MIME_OTHER)
	{
		data = (uint8_t*)malloc(length);
	}

	//////////////////////////////////////////////////////////////////////////////////////////////
	CocoAssetFile(const char* str, bool i_isAsset) : fd(nullptr), file(nullptr), data(nullptr), isAsset(i_isAsset), length(0), mime(MIME_OTHER)
	{
		char* ld = (char*) strrchr(str, '.');
        if(!ld)
        {
            trace("Invalid file");
            return;
        }
        else
        {
            ld++;
            if(!strncmp(ld, "jpg", 3)) mime = IMAGE_JPG;
            else if(!strncmp(ld, "jpeg", 4)) mime = IMAGE_JPG;
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
            fd = fopen(file, "rb");
            if(fd)
			{
                fseek((FILE*)fd, 0, SEEK_END);
                length = (size_t) ftell((FILE*)fd);
                rewind((FILE*)fd);
			}
        }
        else if(!isAsset && filesPath && str)
        {
			type = TYPE_FILE;
            std::string temps(filesPath);
            temps += str + 2;
            file = strdup(temps.c_str());
            fd = fopen(file, "rb+");
            if(fd)
			{
                fseek((FILE*)fd, 0, SEEK_END);
                length = (size_t) ftell((FILE*)fd);
                rewind((FILE*)fd);
			}
        }
	}

	//////////////////////////////////////////////////////////////////////////////////////////////
	~CocoAssetFile()
	{
        if(fd)
        {
            fclose((FILE*)fd);
            fd = nullptr;
        }
        if(file) free(file);
        if(data) free(data);
	}

	//////////////////////////////////////////////////////////////////////////////////////////////
	void setMime(const char* str)
	{
		if(!strcmp(str, "image/png")) mime = IMAGE_PNG;
		else if(!strcmp(str, "image/jpg") || strcmp(str, "image/jpeg")) mime = IMAGE_JPG;
		else if(!strcmp(str, "audio/ogg")) mime = AUDIO_OGG;
		else if(!strcmp(str, "font/ttf,")) mime = FONT_TTF;
		else mime = MIME_OTHER;
	}

	//////////////////////////////////////////////////////////////////////////////////////////////
	inline const size_t& getLength() const { return length; }
	inline const char* getFullPath() const { return file; }

	//////////////////////////////////////////////////////////////////////////////////////////////
    // standard io functions pass-through
    // they update only the file, not the data!
	//////////////////////////////////////////////////////////////////////////////////////////////
	inline int seek(size_t offset, size_t origin)
	{
		switch(type)
		{
		case TYPE_FILE:
		case TYPE_ASSET:
			return fseek((FILE*)fd, (long) offset, (int) origin);
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

	//////////////////////////////////////////////////////////////////////////////////////////////
	inline int32_t tell()
	{
		switch(type)
		{
			case TYPE_FILE:
			case TYPE_ASSET:
            {
				long sz = ftell((FILE*)fd);
                return static_cast<int32_t>(sz);
            }
            case TYPE_DATA:
				return (int32_t) cursor;
		}
		return -1;
	}

	//////////////////////////////////////////////////////////////////////////////////////////////
	inline size_t read(void* dest, size_t size)
	{
		switch(type)
		{
		case TYPE_FILE:
		case TYPE_ASSET:
			return fread(dest, 1, size, (FILE*)fd);
		case TYPE_DATA:
			size_t ret = size;
			if(ret + cursor > length) ret = length - cursor;
			memcpy(dest, data + cursor, ret);
			cursor += ret;
			return ret;
		}
		return 0;
	}

	//////////////////////////////////////////////////////////////////////////////////////////////
    inline size_t write(const void* src, size_t size)
    {
    	return fwrite(src, 1, size, (FILE*)fd);
    }

	//////////////////////////////////////////////////////////////////////////////////////////////
    inline int flush()
    {
    	return fflush((FILE*)fd);
    }

	//////////////////////////////////////////////////////////////////////////////////////////////
	size_t append(void* d, size_t s)
	{
		if(type == TYPE_DATA)
		{
			realloc(data, length + s);
			memcpy(data + length, d, s);
			length += s;
			return s;
		}
		return 0;
	}

	//////////////////////////////////////////////////////////////////////////////////////////////
    uint8_t* getData()
    {
		if(!data && fd)
        {
            rewind((FILE*)fd);
            data = (uint8_t*)malloc(length + 1);
            data[length] = 0;
            fread(data, 1, length, (FILE*)fd);
        }
        return data;
    }
};

#endif
