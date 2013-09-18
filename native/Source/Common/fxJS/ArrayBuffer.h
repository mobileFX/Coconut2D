#ifndef _ArrayBuffer_h
#define _ArrayBuffer_h

#include "Common.h"
#include "fxCRL.h"

class ArrayBuffer
{
private:
    static fxJSClass _Class;
    static fxJSConstructor _ConstructorObject;
    
    void* data;
    size_t byteLength;
    fxJSObject jsThis;
    
    //////////////////////////////////////////////////////////////////////////////////////////////
    ArrayBuffer(size_t i_byteLength) : data(nullptr), byteLength(i_byteLength)
    {
        data = malloc(byteLength);
        clear();
    }
    
    ~ArrayBuffer()
    {
        free(data);
        data = nullptr;
    }
    
public:
    
    //////////////////////////////////////////////////////////////////////////////////////////////
    inline static const fxJSClass& getJSClass() { return _Class; }
    inline static const fxJSConstructor& getJSConstructor() { return fxJSChooseConstructor(_Class, _ConstructorObject); }
    inline fxJSObject getJSObject() { return jsThis; }
    inline void clear() { memset(data, 0, byteLength); }
    inline size_t getByteLength() { return byteLength; }
    
    //////////////////////////////////////////////////////////////////////////////////////////////
    void* operator [](const size_t& i)
    {
        if(i >= byteLength) return nullptr;
        return ((char*)data + i);
    }
    
	//////////////////////////////////////////////////////////////////////////////////////////////
	inline static void* getArrayBufferPointer(fxObjectUID uid, unsigned int offset)
	{
		ArrayBuffer* t = (ArrayBuffer*)(uid);
		return (*t)[offset];
	}
	
    //////////////////////////////////////////////////////////////////////////////////////////////
    inline static void init()
    {
        fxJSFunctionCB fun[] =
        {
            {"clear", _clear, fxJSPropertyAttributeNone},
            {nullptr, nullptr, fxJSPropertyAttributeNone}
        };
        
        fxJSClassTemplate temp = fxJSMakeClassTemplate();
        fxJSSetClassStorage(temp, 1);
        fxJSSetClassName(temp, "ArrayBuffer");
        fxJSSetClassConstructor(temp, _Constructor);
        fxJSSetClassFunctions(temp, fun);
        fxJSSetClassFree(temp, _Free);
        _Class = fxJSMakeClass(temp);
        _ConstructorObject = fxJSMakeConstructor(_Class, _Constructor);
        fxJSRetainConstructor(_ConstructorObject);
    }
    
    //////////////////////////////////////////////////////////////////////////////////////////////
    inline static void quit()
    {
    	fxJSReleaseConstructor(_ConstructorObject);
    	fxJSFreeClass(_Class);
    }
    
    //////////////////////////////////////////////////////////////////////////////////////////////
    static fxJSBindFree(_Free)
    {
        ArrayBuffer *t = fxJSCastNative(ArrayBuffer, fxJSGetObject());
        delete t;
        fxJSFreeObject(fxJSGetObject());
        fxJSFreeMemory(sizeof(ArrayBuffer));
    }
    
    //////////////////////////////////////////////////////////////////////////////////////////////
    static fxJSBindConstructor(_Constructor)
    {
        //if(!info.IsConstructCall()) return info.This();
        size_t length = 0;
        if(fxJSGetArgCount() > 0 && fxJSIsNumber(fxJSGetArg(0))) length = fxJSCastNumber(fxJSGetArg(0));
        ArrayBuffer* t = new ArrayBuffer(length);
        
        t->jsThis = fxJSConstructorObject(_Class);
        fxJSRetainObject(t->jsThis);
        fxJSSetObjectFree(t->jsThis, _Free);
        fxJSSetPrivate(t->jsThis, t);
        fxJSAllocMemory(sizeof(ArrayBuffer));
        
        fxJSSetProperty(t->jsThis, fxCRL::jsStr___uid, fxJSMakeNumber((size_t)t), fxJSPropertyAttributeReadOnly);
        fxJSSetProperty(t->jsThis, fxCRL::jsStr_byteLength, fxJSMakeNumber(t->byteLength), fxJSPropertyAttributeReadOnly);
        
        return t->jsThis;
    }
    
    //////////////////////////////////////////////////////////////////////////////////////////////
    static fxJSBindFunction(_clear)
    {
        fxJSGetNative(ArrayBuffer)->clear();
        return fxJSMakeUndefined();
    }
    
    //////////////////////////////////////////////////////////////////////////////////////////////
    static fxJSValue NewFromImage(const char* cstr, uint32_t& width, uint32_t& height)
    {
        char* ld = (char*) strrchr(cstr, '.');
        if(!ld)
        {
            LOGW("Invalid file!\n");
            return fxJSEmptyValue();
        }
        else
        {
            ld++;
            
        #ifdef ENABLE_PNG_SUPPORT
            if(!strncmp(ld, "png", 3)) return NewFromImage_PNG(cstr, width, height);
            else
        #endif /* ENABLE_PNG_SUPPORT */
        
        #ifdef ENABLE_JPEG_SUPPORT
            if(!strncmp(ld, "jpg", 3)
            || !strncmp(ld, "jpe", 3)
            || !strncmp(ld, "jif", 3)
            || !strncmp(ld, "jfi", 3)
            || !strncmp(ld, "jpeg", 4)
            || !strncmp(ld, "jfif", 4)) return NewFromImage_JPEG(cstr, width, height);
            else
        #endif /* ENABLE_JPEG_SUPPORT */
                
            {
                LOGW("Extension \".%s\" not supported!\n", ld);
                return fxJSEmptyValue();
            }
        }
    }

    #ifdef ENABLE_PNG_SUPPORT
	// ==================================================================================================================================
	//	    ____  _   ________
	//	   / __ \/ | / / ____/
	//	  / /_/ /  |/ / / __
	//	 / ____/ /|  / /_/ /
	//	/_/   /_/ |_/\____/
	//
	// ==================================================================================================================================
    
    static fxJSValue NewFromImage_PNG(const char* cstr, uint32_t& width, uint32_t& height)
    {
        fxJSValue ret = fxJSEmptyValue();
        
        unsigned char sig[8];
        size_t rowbytes;
        png_bytepp rows;
        
        fxFile* file = fxFile::open(cstr);
        if(!file) return ret;
        
        file->read(sig, 8);
        
        if(!png_sig_cmp(sig, 0, 8))
        {
            png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
            png_infop info_ptr = png_create_info_struct(png_ptr);
            if(png_ptr && info_ptr && !setjmp(png_jmpbuf(png_ptr)))
            {
                png_set_read_fn(png_ptr, (png_voidp)file, png_from_memory);
                png_set_sig_bytes(png_ptr, 8);
                png_read_png(png_ptr, info_ptr, PNG_TRANSFORM_EXPAND | PNG_TRANSFORM_STRIP_16 | PNG_TRANSFORM_GRAY_TO_RGB | PNG_TRANSFORM_PACKING, nullptr);
                width = png_get_image_width(png_ptr, info_ptr);
                height = png_get_image_height(png_ptr, info_ptr);
                rows = png_get_rows(png_ptr, info_ptr);
                rowbytes = png_get_rowbytes(png_ptr, info_ptr);
                
                fxJSValue vsize = fxJSMakeNumber(height * rowbytes);
                fxJSObject obj = fxJSCallConstructor(getJSConstructor(), 1, &vsize);
                ArrayBuffer* t = fxJSCastNative(ArrayBuffer, obj);
                
                for(uint32_t i = height; i--;)
                    memcpy((*t)[rowbytes * i], rows[i], rowbytes);
                
                ret = obj;
            }
            png_destroy_read_struct(&png_ptr, &info_ptr, nullptr);
        }
        delete file;
        return ret;
    }
    
    //////////////////////////////////////////////////////////////////////////////////////////////
    static void png_from_memory(png_structp png_ptr, png_bytep readBytes, png_size_t readCount)
    {
    	fxFile* file = (fxFile*)png_get_io_ptr(png_ptr);
    	file->read(readBytes, readCount);
    }
    #endif /* ENABLE_PNG_SUPPORT */
    
    #ifdef ENABLE_JPEG_SUPPORT
	// ==================================================================================================================================
	//	       ______  ____________
	//	      / / __ \/ ____/ ____/
	//	 __  / / /_/ / __/ / / __
	//	/ /_/ / ____/ /___/ /_/ /
	//	\____/_/   /_____/\____/
	//
	// ==================================================================================================================================
    
    static fxJSValue NewFromImage_JPEG(const char* cstr, uint32_t& width, uint32_t& height)
    {
        fxJSValue ret = fxJSEmptyValue();
        
        fxFile* file = fxFile::open(cstr);
        if(!file) return ret;
        
        size_t rowBytesIn, rowBytesOut;
        jpeg_decompress_struct cInfo;
        jpeg_error_mgr jError;
        cInfo.err = jpeg_std_error(&jError);
        jError.error_exit = jpeg_error;
        jpeg_create_decompress(&cInfo);
        jpeg_mem_src(&cInfo, (unsigned char*)file->getData(), file->getLength());
        jpeg_read_header(&cInfo, TRUE);
        jpeg_start_decompress(&cInfo);
        width = cInfo.output_width;
        height = cInfo.output_height;
        rowBytesIn = width * cInfo.output_components;
        rowBytesOut = width * sizeof(uint32_t);
        
        fxJSValue vsize = fxJSMakeNumber(height * rowBytesOut);
        fxJSObject obj = fxJSCallConstructor(getJSConstructor(), 1, &vsize);
        ArrayBuffer* t = fxJSCastNative(ArrayBuffer, obj);
        
        JSAMPLE* pSample = (JSAMPLE*)malloc(rowBytesIn);
        
        JSAMPROW pRow[1];
        pRow[0] = pSample;
        unsigned char* ptrRow;
        
        unsigned char* ptr = (unsigned char*)((*t)[0]);
        for(uint32_t i = height; i--;)
        {
            jpeg_read_scanlines(&cInfo, pRow, 1);
            ptrRow = (unsigned char*)(&(pRow[0][0]));
            for(uint32_t r = width; r--; ptr += 4, ptrRow += 3)
            {
                memcpy(ptr, ptrRow, 3);
                ptr[3] = 0xFF;
            }
        }
        
        free(pSample);
        jpeg_finish_decompress(&cInfo);
        jpeg_destroy_decompress(&cInfo);
        ret = obj;
        
        delete file;
        return ret;
    }
    
    //////////////////////////////////////////////////////////////////////////////////////////////
    static void jpeg_error(j_common_ptr cInfo)
    {
        char pszMessage[JMSG_LENGTH_MAX];
        
        (*cInfo->err->format_message)(cInfo, pszMessage);
        
        LOGW("Jpeg Lib error: %s\n", pszMessage);
    }
    #endif /* ENABLE_JPEG_SUPPORT */    
};

#endif
