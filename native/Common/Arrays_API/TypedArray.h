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
//	  ______                     _____                         
//	 /_  __/_  ______  ___  ____/ /   |  ______________ ___  __
//	  / / / / / / __ \/ _ \/ __  / /| | / ___/ ___/ __ `/ / / /
//	 / / / /_/ / /_/ /  __/ /_/ / ___ |/ /  / /  / /_/ / /_/ / 
//	/_/  \__, / .___/\___/\__,_/_/  |_/_/  /_/   \__,_/\__, /  
//	    /____/_/                                      /____/   
// ==================================================================================================================================

#ifndef _TypedArray_h
#define _TypedArray_h

#include "Common.h"
#include "ArrayBufferView.h"

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
    
    #ifdef JAVASCRIPT_ENGINE_APPLE
        
    //////////////////////////////////////////////////////////////////////////////////////////////
    static fxJSBindGetPropertyAt(_GetterIndexed)
    {
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
    }
    
    //////////////////////////////////////////////////////////////////////////////////////////////
    static fxJSBindSetPropertyAt(_SetterIndexed)
    {
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
    }
    
    #elif JAVASCRIPT_ENGINE_V8
    
    //////////////////////////////////////////////////////////////////////////////////////////////
    static fxJSBindGetPropertyAt(_GetterIndexed)
    {
        TypedArray<T>* t = fxJSGetNative(TypedArray<T>);
        return fxJSMakeNumber(t->get(index));
    }
    
    
    //////////////////////////////////////////////////////////////////////////////////////////////
    static fxJSBindSetPropertyAt(_SetterIndexed)
    {
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
    }
    
    #endif /* JAVASCRIPT_ENGINE_ */
    
};

#endif


