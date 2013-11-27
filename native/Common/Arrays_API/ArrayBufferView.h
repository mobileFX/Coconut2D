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
//	    ___                          ____        ________         _    ___             
//	   /   |  ______________ ___  __/ __ )__  __/ __/ __/__  ____| |  / (_)__ _      __
//	  / /| | / ___/ ___/ __ `/ / / / __  / / / / /_/ /_/ _ \/ ___/ | / / / _ \ | /| / /
//	 / ___ |/ /  / /  / /_/ / /_/ / /_/ / /_/ / __/ __/  __/ /   | |/ / /  __/ |/ |/ / 
//	/_/  |_/_/  /_/   \__,_/\__, /_____/\__,_/_/ /_/  \___/_/    |___/_/\___/|__/|__/  
//	                       /____/                                                      
// ==================================================================================================================================

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


