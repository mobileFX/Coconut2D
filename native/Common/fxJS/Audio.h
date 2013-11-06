#ifndef _Audio_h
#define _Audio_h

#include "Common.h"
#include "fxCRL.h"
#include "fxAudioStream.h"

class Audio
{
protected:
    
    static fxJSClass _Class;
    static fxJSConstructor _ConstructorObject;
    static fxObjectUID counter;
    
    fxObjectUID uid;
    fxJSObject jsThis;
    
public:
    
    //////////////////////////////////////////////////////////////////////////////////////////////
    Audio(fxObjectUID i_uid) : uid(i_uid) {}
    ~Audio() { fxAudioStream::remove(uid); }
    
    //////////////////////////////////////////////////////////////////////////////////////////////
    inline static fxJSClass getJSClass() { return _Class; }
    inline static fxJSConstructor getJSConstructor() { return fxJSChooseConstructor(_Class, _ConstructorObject); }
    inline fxJSObject getJSObject() { return jsThis; }
    
    //////////////////////////////////////////////////////////////////////////////////////////////
    inline static void init()
    {
        counter = 0;
        fxJSFunctionCB fun[] =
        {
            {"play", _play, fxJSPropertyAttributeNone},
            {"pause", _pause, fxJSPropertyAttributeNone},
            {nullptr, nullptr, fxJSPropertyAttributeNone}
        };
        fxJSClassTemplate temp = fxJSMakeClassTemplate();
        fxJSSetClassStorage(temp, 1);
        fxJSSetClassName(temp, "Audio");
        fxJSSetClassConstructor(temp, _Constructor);
        fxJSSetClassFree(temp, fxCRL::JSFreeCB<Audio>);
        fxJSSetClassFunctions(temp, fun);
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
    static fxJSBindFunction(_play)
    {
        Audio* t = fxJSGetNative(Audio);
        fxAudioStream* a = fxAudioStream::get(t->uid);
        if(a) a->play();
        return fxJSMakeUndefined();
    }
    
    //////////////////////////////////////////////////////////////////////////////////////////////
    static fxJSBindFunction(_pause)
    {
        Audio* t = fxJSGetNative(Audio);
        fxAudioStream* a = fxAudioStream::get(t->uid);
        if(a) a->stop();
        return fxJSMakeUndefined();
    }
    
    //////////////////////////////////////////////////////////////////////////////////////////////
    static fxJSBindConstructor(_Constructor)
    {
        Audio* t = new Audio(++counter);
        if(fxJSGetArgCount() > 0 && fxJSIsString(fxJSGetArg(0)))
        {
            fxJSString jsrc = fxJSAllocStringCopy(fxJSGetArg(0));
            size_t jsrcsize = fxJSStringGetSize(jsrc);
            
            char* csrc = new char[jsrcsize + 1];
            csrc[jsrcsize] = 0;
            fxJSStringToBuffer(jsrc, csrc, jsrcsize);
            
            fxAudioStream::add(t->uid, csrc);
            
            delete[] csrc;
            fxJSFreeString(jsrc);
        }
        
        t->jsThis = fxJSConstructorObject(_Class);
        fxJSRetainObject(t->jsThis);
        fxJSSetObjectFree(t->jsThis, fxCRL::JSFreeCB<Audio>);
        fxJSSetPrivate(t->jsThis, t);
        
        fxJSAllocMemory(sizeof(Audio));
        
        return t->jsThis;
    }
    
};

#endif
