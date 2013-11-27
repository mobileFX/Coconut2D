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

#ifndef _fxCRL_h
#define _fxCRL_h

#include "Common.h"
//#include "fxArgs.h"
#include "fxDeviceWrapper.h"

typedef struct
{
    std::chrono::milliseconds interval;
    std::chrono::steady_clock::time_point next;
    size_t argc;
    fxJSValue* args;
    fxJSValue callback;
    fxJSScript script;
}
structJSTimer;

/////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace fxCRL
{
    enum class fxEvent : uint8_t
    {
        LOAD = 0,
        FOCUS,
        BLUR,
        UNLOAD,
        RESIZE,
        CLICK,
        KEYDOWN,
        KEYPRESS,
        KEYUP,
        TOUCHSTART,
        TOUCHMOVE,
        TOUCHEND,
        TOUCHCANCEL,
        GESTURESTART,
        GESTURECHANGE,
        GESTUREEND
    };
    
    // Helper static functions used globally
    template<class C> inline fxJSBindFree(JSFreeCB)
    {
        C* t = fxJSFreeGetNative(C);
        if(t) delete t;
        fxJSFreeObject(fxJSGetObject());
        fxJSFreeMemory(sizeof(C));
    }
    
    extern fxJSGlobalContext js_context;
    #ifdef JAVASCRIPT_ENGINE_V8
    extern v8::Isolate* v8_isolate;
    #endif
    
    extern fxJSGlobalString jsStr_localStorage;
    
    extern fxJSGlobalString jsStr_onreadystatechange;
    extern fxJSGlobalString jsStr_onload;
    extern fxJSGlobalString jsStr_responseText;
    
    extern fxJSGlobalString jsStr___uid;
    extern fxJSGlobalString jsStr_length;
    extern fxJSGlobalString jsStr_buffer;
    extern fxJSGlobalString jsStr_width;
    extern fxJSGlobalString jsStr_height;
    extern fxJSGlobalString jsStr_maxAdvance;
    extern fxJSGlobalString jsStr_byteLength;
    extern fxJSGlobalString jsStr_byteOffset;
    extern fxJSGlobalString jsStr_BYTES_PER_ELEMENT;
    
    extern fxJSGlobalString jsStr_load;
    extern fxJSGlobalString jsStr_focus;
    extern fxJSGlobalString jsStr_blur;
    extern fxJSGlobalString jsStr_unload;
    extern fxJSGlobalString jsStr_resize;
    extern fxJSGlobalString jsStr_click;
    
    extern fxJSGlobalString jsStr_keydown;
    extern fxJSGlobalString jsStr_keypress;
    extern fxJSGlobalString jsStr_keyup;
    extern fxJSGlobalString jsStr_which;
    
    extern fxJSGlobalString jsStr_touchstart;
    extern fxJSGlobalString jsStr_touchmove;
    extern fxJSGlobalString jsStr_touchend;
    extern fxJSGlobalString jsStr_touchcancel;
    
    extern fxJSGlobalString jsStr_clientX;
    extern fxJSGlobalString jsStr_clientY;
    extern fxJSGlobalString jsStr_screenX;
    extern fxJSGlobalString jsStr_screenY;
    extern fxJSGlobalString jsStr_touches;
    extern fxJSGlobalString jsStr_changedTouches;
    
    void init(int argc, char *argv[], const fxScreen& scr, fxDeviceWrapper* dev);
    void quit();
    void tick();
    void paint();
    void handleEvent(fxObjectUID uid, fxEvent type, void* data = nullptr);
    void dispatchDebugMessages();
    //void* getArrayBufferPointer(fxObjectUID uid, unsigned int offset);
    void eraseTimer(const std::map<size_t, structJSTimer>::iterator&);
    void tickTimers(const std::chrono::steady_clock::time_point&);
    void loadStorage(const char* str = "./localStorage.json");
    void saveStorage(const char* str = "./localStorage.json");
    
    #ifdef JAVASCRIPT_ENGINE_V8
    v8::Handle<v8::String> ReadFile(const char* name);
    void ReportException(v8::TryCatch* try_catch);
    const char* toCString(const v8::String::Utf8Value& value);
    #endif
    
    #ifdef ENABLE_V8_DEBUG_AGENT
    void OnProcessDebugMessages();
    void OnDebugEvent(const v8::Debug::EventDetails& details);
    #endif
    
    bool isLittleEndian();
    
    // Private namespace
    namespace
    {
        fxScreen screen;
        fxDeviceWrapper* device;
        bool _isLittleEndian;
        
        std::chrono::steady_clock::time_point start_time = std::chrono::steady_clock::now();
        
        #ifdef ENABLE_V8_DEBUG_AGENT
        std::chrono::steady_clock::time_point debug_break_time = start_time;
        #endif
        
        fxJSFunction js_requestAnimationFrameCallback = fxJSEmptyFunction();
        
        fxJSObject js_JSON = fxJSEmptyObject();
        fxJSFunction js_JSON_parse = fxJSEmptyFunction();
        fxJSFunction js_JSON_stringify = fxJSEmptyFunction();
        fxJSObject js_localStorage = fxJSEmptyObject();
        
        fxJSObject js_CallbackManager = fxJSEmptyObject();
        fxJSFunction js_DispatchFunction = fxJSEmptyFunction();
        fxJSObject js_EventObject = fxJSEmptyObject();
        fxJSObject js_TouchesObject = fxJSEmptyObject();
        fxJSObject js_ChangedTouchesObject = fxJSEmptyObject();
        fxJSObject js_Touches[JSTOUCHLIST_MAX_LENGTH];
        fxJSObject js_ChangedTouches[JSTOUCHLIST_MAX_LENGTH];
        std::map<size_t, structJSTimer> jsTimerList;
        size_t jsTimerID = 0;
    }
    
    // Native method bindings
    fxJSBindFunction(__debug_break);
    fxJSBindFunction(__alert);
    fxJSBindFunction(__setTimeout);
    fxJSBindFunction(__setInterval);
    fxJSBindFunction(__clearTimeout);
    fxJSBindFunction(__clearInterval);
    fxJSBindFunction(__requestAnimationFrame);
    fxJSBindFunction(__ImageData_loadImage);
    fxJSBindFunction(__registerManager);
    fxJSBindFunction(__registerCallback);
    fxJSBindFunction(__hintShowInput);
    fxJSBindFunction(__hintHideInput);
};

#endif

