#ifndef _ArrayBufferView_h
#define _ArrayBufferView_h

#include "Common.h"
#include "ArrayBuffer.h"

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

#endif
