#ifndef ARRAYBUFFER_H
#define ARRAYBUFFER_H

#include "Defines.h"
#include "fxCRL.h"
#include "fxAsset.h"

/*/////////////////////////////////////////////////////////////////////////////////////////////
    ___                          ____        ________
   /   |  ______________ ___  __/ __ )__  __/ __/ __/__  _____
  / /| | / ___/ ___/ __ `/ / / / __  / / / / /_/ /_/ _ \/ ___/
 / ___ |/ /  / /  / /_/ / /_/ / /_/ / /_/ / __/ __/  __/ /
/_/  |_/_/  /_/   \__,_/\__, /_____/\__,_/_/ /_/  \___/_/
                       /____/

/////////////////////////////////////////////////////////////////////////////////////////////*/

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

    //////////////////////////////////////////////////////////////////////////////////////////////
    void* operator [](const size_t& i)
    {
        if(i >= byteLength) return nullptr;
        return ((char*)data + i);
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

        //fxJSSetProperty(t->jsThis, WebGLWrapper::jsStr___uid, fxJSMakeNumber((size_t)t), fxJSPropertyAttributeReadOnly);
        //fxJSSetProperty(t->jsThis, WebGLWrapper::jsStr_byteLength, fxJSMakeNumber(t->byteLength), fxJSPropertyAttributeReadOnly);

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
            if(!strncmp(ld, "jpg", 3)) return NewFromImage_JPG(cstr, width, height);
            else if(!strncmp(ld, "png", 3)) return NewFromImage_PNG(cstr, width, height);
            else
            {
                LOGW("Invalid extension!\n");
                return fxJSEmptyValue();
            }
        }
    }

    /*/////////////////////////////////////////////////////////////////////////////////////////////
        ____  _   ________   ____
       / __ \/ | / / ____/  /  _/___ ___  ____ _____ ____
      / /_/ /  |/ / / __    / // __ `__ \/ __ `/ __ `/ _ \
     / ____/ /|  / /_/ /  _/ // / / / / / /_/ / /_/ /  __/
    /_/   /_/ |_/\____/  /___/_/ /_/ /_/\__,_/\__, /\___/
                                             /____/

    /////////////////////////////////////////////////////////////////////////////////////////////*/

    static fxJSValue NewFromImage_PNG(const char* cstr, uint32_t& width, uint32_t& height)
    {
        fxJSValue ret = fxJSEmptyValue();

        unsigned char sig[8];
        size_t rowbytes;
        png_bytepp rows;

        fxFile file(cstr, true);
        file.read(sig, 8);

        if(!png_sig_cmp(sig, 0, 8))
        {
            png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
            png_infop info_ptr = png_create_info_struct(png_ptr);
            if(png_ptr && info_ptr && !setjmp(png_jmpbuf(png_ptr)))
            {
                png_set_read_fn(png_ptr, (png_voidp)&file, png_from_memory);
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

        return ret;
    }

    //////////////////////////////////////////////////////////////////////////////////////////////
    static void png_from_memory(png_structp png_ptr, png_bytep readBytes, png_size_t readCount)
    {
    	fxFile* file = (fxFile*)png_get_io_ptr(png_ptr);
    	file->read(readBytes, readCount);
    }

    /*/////////////////////////////////////////////////////////////////////////////////////////////
           ______  ____________   ____
          / / __ \/ ____/ ____/  /  _/___ ___  ____ _____ ____
     __  / / /_/ / __/ / / __    / // __ `__ \/ __ `/ __ `/ _ \
    / /_/ / ____/ /___/ /_/ /  _/ // / / / / / /_/ / /_/ /  __/
    \____/_/   /_____/\____/  /___/_/ /_/ /_/\__,_/\__, /\___/
                                                  /____/

    /////////////////////////////////////////////////////////////////////////////////////////////*/

    static fxJSValue NewFromImage_JPG(const char* cstr, uint32_t& width, uint32_t& height)
    {
        fxJSValue ret = fxJSEmptyValue();

        fxFile file(cstr, true);

        size_t rowBytesIn, rowBytesOut;
        jpeg_decompress_struct cInfo;
        jpeg_error_mgr jError;
        cInfo.err = jpeg_std_error(&jError);
        jError.error_exit = jpg_error;
        jpeg_create_decompress(&cInfo);
        jpeg_mem_src(&cInfo, (unsigned char*)file.getData(), file.getLength());
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

        return ret;
    }

    //////////////////////////////////////////////////////////////////////////////////////////////
    static void jpg_error(j_common_ptr cInfo)
    {
        char pszMessage[JMSG_LENGTH_MAX];

        (*cInfo->err->format_message)(cInfo, pszMessage);

        LOGW("Jpeg Lib error: %s\n", pszMessage);
    }  

    //////////////////////////////////////////////////////////////////////////////////////////////
    /*
    //Slice
    ArrayBuffer(ArrayBuffer* old, long begin, long end = -1) : data(nullptr), byteLength(0)
    {
        if(old)
        {
            if(begin == -1) begin = old->byteLength;
            if(end == -1) end = old->byteLength;
            if(begin < end) byteLength = begin - end;

            data = malloc(byteLength);
            memcpy(data, old->data, byteLength);
        }
    }*/

};

/*/////////////////////////////////////////////////////////////////////////////////////////////
      ___                          ____        ________         _    ___
     /   |  ______________ ___  __/ __ )__  __/ __/ __/__  ____| |  / (_)__ _      __
    / /| | / ___/ ___/ __ `/ / / / __  / / / / /_/ /_/ _ \/ ___/ | / / / _ \ | /| / /
   / ___ |/ /  / /  / /_/ / /_/ / /_/ / /_/ / __/ __/  __/ /   | |/ / /  __/ |/ |/ /
  /_/  |_/_/  /_/   \__,_/\__, /_____/\__,_/_/ /_/  \___/_/    |___/_/\___/|__/|__/
                         /____/

/////////////////////////////////////////////////////////////////////////////////////////////*/

class ArrayBufferView
{
protected:

    static fxJSClass _ParentClass;
    static fxJSConstructor _ConstructorObject;

    ArrayBuffer* buffer;
    size_t byteLength;
    size_t byteOffset;
    fxJSObject jsThis;

public:

    //////////////////////////////////////////////////////////////////////////////////////////////
    inline static fxJSClass getJSClass() { return _ParentClass; }
    inline static fxJSConstructor getJSConstructor() { return fxJSChooseConstructor(_ParentClass, _ConstructorObject); }
    inline fxJSObject getJSObject() { return jsThis; }
    inline ArrayBuffer* getBuffer() { return buffer; }

    //////////////////////////////////////////////////////////////////////////////////////////////
    inline static void init()
    {
        fxJSClassTemplate temp = fxJSMakeClassTemplate();
        fxJSSetClassName(temp, "ArrayBufferView");
        _ParentClass = fxJSMakeClass(temp);
        _ConstructorObject = fxJSMakeConstructor(_ParentClass, nullptr);
        fxJSRetainConstructor(_ConstructorObject);
    }

    //////////////////////////////////////////////////////////////////////////////////////////////
    inline static void quit()
    {
        fxJSReleaseConstructor(_ConstructorObject);
        fxJSFreeClass(_ParentClass);
    }    
};

/*/////////////////////////////////////////////////////////////////////////////////////////////
    ______                     _____
   /_  __/_  ______  ___  ____/ /   |  ______________ ___  __
    / / / / / / __ \/ _ \/ __  / /| | / ___/ ___/ __ `/ / / /
   / / / /_/ / /_/ /  __/ /_/ / ___ |/ /  / /  / /_/ / /_/ /
  /_/  \__, / .___/\___/\__,_/_/  |_/_/  /_/   \__,_/\__, /
      /____/_/                                      /____/

/////////////////////////////////////////////////////////////////////////////////////////////*/

template<typename T> class TypedArray : public ArrayBufferView
{
private:

    static fxJSClass _Class;
    static fxJSConstructor _ConstructorObject;

    size_t length;

public:

    //////////////////////////////////////////////////////////////////////////////////////////////
    TypedArray(const size_t& i_length = 0) : length(i_length)
    {
        byteOffset = 0;
        byteLength = length * BYTES_PER_ELEMENT;
        fxJSValue num = fxJSMakeNumber(byteLength);
        fxJSObject obj = fxJSCallConstructor(ArrayBuffer::getJSConstructor(), 1, &num);
        buffer = fxJSCastNative(ArrayBuffer, obj);
    }

    //////////////////////////////////////////////////////////////////////////////////////////////
    template<typename O> TypedArray(const TypedArray<O>* array) : TypedArray(array->getLength())
    {
        for(size_t i = length; i--;)
            set(i, (T)array->get(i));
    }

    //////////////////////////////////////////////////////////////////////////////////////////////
    T get(const size_t& i) const
    {
        return (*(static_cast<T*>((*(this->buffer))[this->byteOffset + i * BYTES_PER_ELEMENT])));
    }

    //////////////////////////////////////////////////////////////////////////////////////////////
    bool set(const size_t& i, const T& value)
    {
        if(i < this->length)
        {
            //memcpy((*this->buffer)[this->byteOffset + i * BYTES_PER_ELEMENT], &value, BYTES_PER_ELEMENT);
            ((T*)(*this->buffer)[this->byteOffset])[i] = value;
            return true;
        }
        return false;
    }

    //////////////////////////////////////////////////////////////////////////////////////////////
    inline static fxJSClass getJSClass() { return _Class; }
    inline static fxJSConstructor getJSConstructor() { return fxJSChooseConstructor(_Class, _ConstructorObject); }
    static const size_t BYTES_PER_ELEMENT = sizeof(T);
    inline const size_t& getLength() const { return length; }

    //////////////////////////////////////////////////////////////////////////////////////////////
    inline static void init(const char* className)
    {
        fxJSClassTemplate temp = fxJSMakeClassTemplate();
        fxJSSetClassStorage(temp, 1);
        fxJSSetParentClass(temp, _ParentClass);
        fxJSSetClassName(temp, className);
        fxJSSetIndexedPropertyHandler(temp, _GetterIndexed, _SetterIndexed);
        fxJSSetClassConstructor(temp, _Constructor);
        fxJSSetClassFree(temp, _Free);
        _Class = fxJSMakeClass(temp);
        _ConstructorObject = fxJSMakeConstructor(_Class, _Constructor);
        fxJSRetainConstructor(_ConstructorObject);
        fxJSSetProperty(getJSConstructor(), fxCRL::jsStr_BYTES_PER_ELEMENT, fxJSMakeNumber(BYTES_PER_ELEMENT), fxJSPropertyAttributeReadOnly);
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
        TypedArray<T>* t = fxJSCastNative(TypedArray<T>, fxJSGetObject());
        delete t;
        fxJSFreeObject(fxJSGetObject());
        fxJSFreeMemory(sizeof(TypedArray<T>));
    }

    //////////////////////////////////////////////////////////////////////////////////////////////
    static fxJSBindConstructor(_Constructor)
    {
        //if(!info.IsConstructCall()) return info.This();
        size_t length = 0;
        TypedArray<T>* t = nullptr;
        if(fxJSGetArgCount() > 0)
        {
            if(fxJSIsNumber(fxJSGetArg(0)))
            {
                length = fxJSCastNumber(fxJSGetArg(0));
                t = new TypedArray<T>(length);
            }
            else if(fxJSIsObject(fxJSGetArg(0)))
            {
                fxJSObject obj = fxJSCastObject(fxJSGetArg(0));
                if(fxJSHasProperty(obj, fxCRL::jsStr_length))
                {
                    size_t s = fxJSCastNumber(fxJSGetProperty(obj, fxCRL::jsStr_length));
                    t = new TypedArray<T>(s);
                    for(size_t i = s; i--;)
                        t->set(i, (T)fxJSCastNumber(fxJSGetPropertyAt(obj, i)));
                }
            }
            /*
            else if(ArrayBuffer::getJSClass()->HasInstance(fxJSGetArg(0)))
            {
                // TODO
                t = new TypedArray<T>();
            }
            else if(TypedArray<int32_t>::getJSClass()->HasInstance(fxJSGetArg(0)))
            {
                t = new TypedArray<T>(fxJSCastNative(TypedArray<int32_t>, fxJSCastObject(fxJSGetArg(0))));
            }
            else if(TypedArray<float>::getJSClass()->HasInstance(fxJSGetArg(0)))
            {
                t = new TypedArray<T>(fxJSCastNative(TypedArray<float>, fxJSCastObject(fxJSGetArg(0))));
            }*/
        }
        else t = new TypedArray<T>();

        t->jsThis = fxJSConstructorObject(_Class);
        fxJSRetainObject(t->jsThis);
        fxJSSetObjectFree(t->jsThis, _Free);
        fxJSSetPrivate(t->jsThis, t);
        fxJSAllocMemory(sizeof(TypedArray<T>));
        
        fxJSSetProperty(t->jsThis, fxCRL::jsStr_length, fxJSMakeNumber(t->length), fxJSPropertyAttributeReadOnly);
        fxJSSetProperty(t->jsThis, fxCRL::jsStr_BYTES_PER_ELEMENT, fxJSMakeNumber(BYTES_PER_ELEMENT), fxJSPropertyAttributeReadOnly);
        fxJSSetProperty(t->jsThis, fxCRL::jsStr_buffer, t->buffer->getJSObject(), fxJSPropertyAttributeReadOnly);
        fxJSSetProperty(t->jsThis, fxCRL::jsStr_byteLength, fxJSMakeNumber(t->byteLength), fxJSPropertyAttributeReadOnly);
        fxJSSetProperty(t->jsThis, fxCRL::jsStr_byteOffset, fxJSMakeNumber(t->byteOffset), fxJSPropertyAttributeReadOnly);
        
        return t->jsThis;
    }

    //////////////////////////////////////////////////////////////////////////////////////////////
    static fxJSBindGetPropertyAt(_GetterIndexed)
    {
        #ifdef JAVASCRIPT_ENGINE_APPLE
            
			static char cstr[64];
            static char* endp;
            static size_t cstr_size;
            static long int index;
            static TypedArray<T>* t;
        
            cstr_size = fxJSStringGetSize(fxJSGetPropertyName());
            cstr[cstr_size] = 0;
            fxJSStringToBuffer(fxJSGetPropertyName(), cstr, cstr_size);
        
            index = strtol(cstr, &endp, 0);
            if(cstr == endp) return nullptr;
        
            t = fxJSGetNative(TypedArray<T>);
            if(!t || index < 0 || index >= t->length) return fxJSMakeUndefined();
        
            return fxJSMakeNumber(t->get(index));

        #elif JAVASCRIPT_ENGINE_V8
            
			TypedArray<T>* t = fxJSGetNative(TypedArray<T>);
            return fxJSMakeNumber(t->get(index));

        #endif
    }

    //////////////////////////////////////////////////////////////////////////////////////////////
    static fxJSBindSetPropertyAt(_SetterIndexed)
    {
        #ifdef JAVASCRIPT_ENGINE_APPLE
            static char cstr[64];
            static char* endp;
            static size_t cstr_size;
            static long int index;
            static TypedArray<T>* t;
        
            cstr_size = fxJSStringGetSize(fxJSGetPropertyName());
            cstr[cstr_size] = 0;
            fxJSStringToBuffer(fxJSGetPropertyName(), cstr, cstr_size);
            
            index = strtol(cstr, &endp, 0);
            if(cstr == endp) return false;
        
            t = fxJSGetNative(TypedArray<T>);
            if(fxJSIsNumber(fxJSGetPropertyValue()) && t && index >= 0 && index < t->length) t->set(index, fxJSCastNumber(fxJSGetPropertyValue()));
           
            return true;

        #elif JAVASCRIPT_ENGINE_V8

            TypedArray<T>* t = fxJSGetNative(TypedArray<T>);
            if(fxJSIsUint32(value))
            {
                T v = fxJSCastUint32(value);
                if(t->set(index, v)) return value;
            }
            else if(fxJSIsInt32(value))
            {
                T v = fxJSCastInt32(value);
                if(t->set(index, v)) return value;
            }
            else if(fxJSIsNumber(value))
            {
                T v = fxJSCastNumber(value);
                if(t->set(index, v)) return value;
            }
            return fxJSEmptyValue();

        #endif
    }
};

#endif // ARRAYBUFFER_H
