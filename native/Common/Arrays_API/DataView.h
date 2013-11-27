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
//	    ____        __       _    ___             
//	   / __ \____ _/ /_____ | |  / (_)__ _      __
//	  / / / / __ `/ __/ __ `/ | / / / _ \ | /| / /
//	 / /_/ / /_/ / /_/ /_/ /| |/ / /  __/ |/ |/ / 
//	/_____/\__,_/\__/\__,_/ |___/_/\___/|__/|__/  
//	                                              
// ==================================================================================================================================

#ifndef _DataView_h
#define _DataView_h

#include "Common.h"
#include "ArrayBufferView.h"

class DataView : public ArrayBufferView
{
private:
    
    static fxJSClass _Class;
    static fxJSConstructor _ConstructorObject;
    
public:
    
    //////////////////////////////////////////////////////////////////////////////////////////////
    DataView(ArrayBuffer* i_buffer, size_t i_byteOffset, size_t i_byteLength)
    {
        this->buffer = i_buffer;
        this->byteOffset = i_byteOffset;
        this->byteLength = i_byteLength;
    }
    
    //////////////////////////////////////////////////////////////////////////////////////////////
    inline static fxJSClass getJSClass() { return _Class; }
    inline static fxJSConstructor getJSConstructor() { return fxJSChooseConstructor(_Class, _ConstructorObject); }
    
    //////////////////////////////////////////////////////////////////////////////////////////////
    inline static void init()
    {
        fxJSFunctionCB fun[] =
        {
            {"getInt8", _get<int8_t>, fxJSPropertyAttributeNone},
            {"getUint8", _get<uint8_t>, fxJSPropertyAttributeNone},
            {"getInt16", _get<int16_t>, fxJSPropertyAttributeNone},
            {"getUint16", _get<uint16_t>, fxJSPropertyAttributeNone},
            {"getInt32", _get<int32_t>, fxJSPropertyAttributeNone},
            {"getUint32", _get<uint32_t>, fxJSPropertyAttributeNone},
            {"getFloat32", _get<float>, fxJSPropertyAttributeNone},
            {"getFloat64", _get<double>, fxJSPropertyAttributeNone},
            {"setInt8", _set<int8_t>, fxJSPropertyAttributeNone},
            {"setUint8", _set<uint8_t>, fxJSPropertyAttributeNone},
            {"setInt16", _set<int16_t>, fxJSPropertyAttributeNone},
            {"setUint16", _set<uint16_t>, fxJSPropertyAttributeNone},
            {"setInt32", _set<int32_t>, fxJSPropertyAttributeNone},
            {"setUint32", _set<uint32_t>, fxJSPropertyAttributeNone},
            {"setFloat32", _set<float>, fxJSPropertyAttributeNone},
            {"setFloat64", _set<double>, fxJSPropertyAttributeNone},
            {nullptr, nullptr, fxJSPropertyAttributeNone}
        };
        fxJSClassTemplate temp = fxJSMakeClassTemplate();
        fxJSSetClassStorage(temp, 1);
        fxJSSetParentClass(temp, _ParentClass);
        fxJSSetClassName(temp, "DataView");
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
        DataView* t = fxJSCastNative(DataView, fxJSGetObject());
        delete t;
        fxJSFreeObject(fxJSGetObject());
        fxJSFreeMemory(sizeof(DataView));
    }
    
    //////////////////////////////////////////////////////////////////////////////////////////////
    static fxJSBindConstructor(_Constructor)
    {
        if(fxJSGetArgCount() > 0 && fxJSIsInstanceOf(fxJSGetArg(0), ArrayBuffer))
        {
            ArrayBuffer* buffer = fxJSCastNative(ArrayBuffer, fxJSCastObject(fxJSGetArg(0)));
            size_t byteOffset = 0;
            size_t byteLength = buffer->getByteLength();
            if(fxJSGetArgCount() > 1 && fxJSIsNumber(fxJSGetArg(1))) byteOffset = fxJSCastNumber(fxJSGetArg(1));
            if(fxJSGetArgCount() > 2 && fxJSIsNumber(fxJSGetArg(2))) byteLength = fxJSCastNumber(fxJSGetArg(2));
            DataView* t = new DataView(buffer, byteOffset, byteLength);
            
            t->jsThis = fxJSConstructorObject(_Class);
            fxJSRetainObject(t->jsThis);
            fxJSSetObjectFree(t->jsThis, _Free);
            fxJSSetPrivate(t->jsThis, t);
            fxJSAllocMemory(sizeof(DataView));
            
            fxJSSetProperty(t->jsThis, fxCRL::jsStr_buffer, t->buffer->getJSObject(), fxJSPropertyAttributeReadOnly);
            fxJSSetProperty(t->jsThis, fxCRL::jsStr_byteLength, fxJSMakeNumber(t->byteLength), fxJSPropertyAttributeReadOnly);
            fxJSSetProperty(t->jsThis, fxCRL::jsStr_byteOffset, fxJSMakeNumber(t->byteOffset), fxJSPropertyAttributeReadOnly);
            
            return t->jsThis;
        }
        
        return fxJSCastObject(fxJSMakeUndefined());
    }
    
    template<typename T> static T& flip(T& value, bool littleEndian)
    {
        if(sizeof(T) > 1 && fxCRL::isLittleEndian() != littleEndian)
        {
            uint8_t t;
            uint8_t* v = reinterpret_cast<uint8_t*>(&value);
            for(size_t i = sizeof(T) / 2; i--;)
            {
                t = *(v + i);
                *(v + i) = *(v + sizeof(T) - 1 - i);
                *(v + sizeof(T) - 1 - i) = t;
            }
        }
        return value;
    }

    //////////////////////////////////////////////////////////////////////////////////////////////
    template<typename T> T get(size_t byteOffset, bool littleEndian)
    {
        return flip<T>((*(static_cast<T*>((*(this->buffer))[this->byteOffset + byteOffset]))), littleEndian);
    }
    
    //////////////////////////////////////////////////////////////////////////////////////////////
    template<typename T> bool set(size_t bytOffset, T value, bool littleEndian)
    {
        if(byteOffset + sizeof(T) > this->byteLength) return false;
        flip<T>(value, littleEndian);
        memcpy((*this->buffer)[this->byteOffset + byteOffset], &value, sizeof(T));
        return true;
    }
    
    template<typename T> static fxJSBindFunction(_get)
    {
        if(fxJSGetArgCount() > 0 && fxJSIsNumber(fxJSGetArg(0)))
        {
            DataView* t= fxJSGetNative(DataView);
            size_t byteOffset = fxJSCastNumber(fxJSGetArg(0));
            bool littleEndian = false;
            if(fxJSGetArgCount() > 1) littleEndian = fxJSCastBoolean(fxJSGetArg(1));
            return fxJSMakeNumber(t->get<T>(byteOffset, littleEndian));
        }
        return fxJSMakeUndefined();
    }
    
    template<typename T> static fxJSBindFunction(_set)
    {
        if(fxJSGetArgCount() > 1 && fxJSIsNumber(fxJSGetArg(0)) && fxJSIsNumber(fxJSGetArg(1)))
        {
            DataView* t= fxJSGetNative(DataView);
            size_t byteOffset = fxJSCastNumber(fxJSGetArg(0));
            T value = fxJSCastNumber(fxJSGetArg(1));
            bool littleEndian = false;
            if(fxJSGetArgCount() > 1) littleEndian = fxJSCastBoolean(fxJSGetArg(1));
            t->set<T>(byteOffset, value, littleEndian);
        }
        return fxJSMakeUndefined();
    }
};

#endif


