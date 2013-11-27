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
//	    ___             ___          ___    ____  ____
//	   /   | __  ______/ (_)___     /   |  / __ \/  _/
//	  / /| |/ / / / __  / / __ \   / /| | / /_/ // /  
//	 / ___ / /_/ / /_/ / / /_/ /  / ___ |/ ____// /   
//	/_/  |_\__,_/\__,_/_/\____/  /_/  |_/_/   /___/   
//	                                                  
// ==================================================================================================================================

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



