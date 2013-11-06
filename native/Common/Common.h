#ifndef _Common_h
#define _Common_h

#include <cstdlib>
#include <list>
#include <array>
#include <map>
#include <fstream>
#include <atomic>
#include <mutex>
#include <thread>
#include <vector>

#include "Structs.h"

#define APPNAME "Coconut"
#define VERSION "0.1"
#define VENDOR "mobileFX"

////////////////////////////////////////////////////////////////
#ifdef IOS_APPLICATION
    #define PLATFORM "iOS"
    #define fxAPIGetKey(E) (*(const uint32_t*)(E))
    #define fxAPIGetMouseEventX(E) ([[[[(UIEvent*)E allTouches] allObjects] objectAtIndex: 0] locationInView:nil].x)
    #define fxAPIGetMouseEventY(E) ([[[[(UIEvent*)E allTouches] allObjects] objectAtIndex: 0] locationInView:nil].y)
    #define fxAPIGetTouchEventX(E, I) ([[[[(UIEvent*)E allTouches] allObjects] objectAtIndex: I] locationInView:nil].x)
    #define fxAPIGetTouchEventY(E, I) ([[[[(UIEvent*)E allTouches] allObjects] objectAtIndex: I] locationInView:nil].y)
    #define fxAPIGetChangedTouchEventX(E, I) ([[[[(UIEvent*)E allTouches] allObjects] objectAtIndex: I] locationInView:nil].x)
    #define fxAPIGetChangedTouchEventY(E, I) ([[[[(UIEvent*)E allTouches] allObjects] objectAtIndex: I] locationInView:nil].y)
    #define fxAPIGetTouchesLength(E) ([[(UIEvent*)E allTouches] count])
    #define fxAPIGetChangedTouchesLength(E) ([[(UIEvent*)E allTouches] count])
#elif ANDROID_APPLICATION
    #define PLATFORM "Android"
    #include <jni.h>
    #include <android_native_app_glue.h>
    #define fxAPIGetMouseEventX(E) AMotionEvent_getX((AInputEvent*)E, 0)
    #define fxAPIGetMouseEventY(E) AMotionEvent_getY((AInputEvent*)E, 0)
    #define fxAPIGetTouchEventX(E, I) AMotionEvent_getX((AInputEvent*)E, I)
    #define fxAPIGetTouchEventY(E, I) AMotionEvent_getY((AInputEvent*)E, I)
    #define fxAPIGetChangedTouchEventX(E, I) AMotionEvent_getX((AInputEvent*)E, I)
    #define fxAPIGetChangedTouchEventY(E, I) AMotionEvent_getY((AInputEvent*)E, I)
    #define fxAPIGetTouchesLength(E) AMotionEvent_getPointerCount((AInputEvent*)E)
    #define fxAPIGetChangedTouchesLength(E) AMotionEvent_getPointerCount((AInputEvent*)E)
#else
    #define PLATFORM "General"
    #define fxAPIGetKey(E)(*(const uint32_t*)(E))
    #define fxAPIGetMouseEventX(E) (((QMouseEvent*)(E))->x())
    #define fxAPIGetMouseEventY(E) (((QMouseEvent*)(E))->y())
    #define fxAPIGetTouchEventX(E, I) (((QMouseEvent*)(E))->x())
    #define fxAPIGetTouchEventY(E, I) (((QMouseEvent*)(E))->y())
    #define fxAPIGetChangedTouchEventX(E, I) (((QMouseEvent*)(E))->x())
    #define fxAPIGetChangedTouchEventY(E, I) (((QMouseEvent*)(E))->y())
    #define fxAPIGetTouchesLength(E) (((QEvent*)(E))->type() == QEvent::MouseButtonRelease ? 0 : 1)
    #define fxAPIGetChangedTouchesLength(E) 1
#endif
////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////
#ifdef ENABLE_FX_DEBUG
    #ifdef ANDROID_APPLICATION
        #include <android/log.h>
        #define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, APPNAME, __VA_ARGS__))
        #define LOGW(...) ((void)__android_log_print(ANDROID_LOG_WARN, APPNAME, __VA_ARGS__))
    #else
        #include <cstdio>
        #define LOGI(...) {fprintf(stdout, __VA_ARGS__); fflush(stdout);}
        #define LOGW(...) {fprintf(stderr, __VA_ARGS__); fflush(stderr);}
    #endif
#else
    #define LOGI(...)
    #define LOGW(...)
#endif
////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////
#ifdef ENABLE_PNG_SUPPORT
    #include <png.h>
#elif !DISABLE_PNG_SUPPORT
    #warning "Building without PNG support!"
#endif
////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////
#ifdef ENABLE_JPEG_SUPPORT
	#undef FALSE
	#undef TRUE
    #include <jpeglib.h>
#elif !DISABLE_JPEG_SUPPORT
    #warning "Building without JPEG support!"
#endif
////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////
#ifdef ENABLE_OGG_SUPPORT
    #define AUDIO_SAMPLE_SIZE 2
    #define AUDIO_FORMAT_MONO AL_FORMAT_MONO16
    #define AUDIO_FORMAT_STEREO AL_FORMAT_STEREO16
    #include <tremor/ivorbisfile.h>
#elif !DISABLE_OGG_SUPPORT
    #warning "Building without Vorbis OGG support!"
#endif
////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////
#ifdef ENABLE_OPENAL_SUPPORT
    #ifdef IOS_APPLICATION
        #include <OpenAL/al.h>
        #include <OpenAL/alc.h>
    #else
        #include <AL/al.h>
        #include <AL/alc.h>
    #endif
#elif !DISABLE_OPENAL_SUPPORT
    #warning "Building without Audio support!"
#endif
////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////
#ifdef ENABLE_FREETYPE_SUPPORT
    #include <ft2build.h>
    #include FT_FREETYPE_H
#elif !DISABLE_FREETYPE_SUPPORT
    #warning "Building without Font support!"
#endif
////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////
#ifdef ENABLE_CURL_SUPPORT
    #include <curl.h>
#elif !DISABLE_CURL_SUPPORT
    #warning "Building without XMLHttpRequest support!"
#endif
////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////
#ifdef ENABLE_OPENGL_SUPPORT
    #ifdef ANDROID_APPLICATION
        #include <EGL/egl.h>
        #include <GLES2/gl2.h>
    #elif IOS_APPLICATION
        #include <OpenGLES/ES2/gl.h>
    #else
        #include <QtOpenGL/QtOpenGL>
    #endif
#elif !DISABLE_OPENGL_SUPPORT
    #warning "Building without OpenGL support!"
#endif
////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////
#define JSINTERVAL_MIN 4
#define JSTOUCHLIST_MAX_LENGTH 5
#define SHADER_SOURCE_BUFFER_SIZE 4096
#define INFO_LOG_BUFFER_SIZE 4096
#define fxObjectUID size_t

#ifdef JAVASCRIPT_ENGINE_V8
    #include <v8.h>
    #ifdef ENABLE_V8_DEBUG_AGENT
        #include <v8-debug.h>
    #endif

    using fxJSGlobalContext = v8::Persistent<v8::Context>;
    using fxJSContext = v8::Handle<v8::Context>;
    using fxJSValue = v8::Handle<v8::Value>;
    using fxJSObject = v8::Handle<v8::Object>;
    using fxJSArray = v8::Handle<v8::Array>;
    using fxJSFunction = v8::Handle<v8::Function>;
    using fxJSConstructor = v8::Handle<v8::Function>;
    using fxJSClass = v8::Persistent<v8::FunctionTemplate>;
    using fxJSClassTemplate = v8::Handle<v8::FunctionTemplate>;
    using fxJSString = v8::Handle<v8::String>;
    using fxJSGlobalString = v8::Persistent<v8::String>;
    using fxJSGlobalObject = v8::Persistent<v8::Object>;
    using fxJSPropertyAttributes = v8::PropertyAttribute;
    using fxJSScript = v8::Handle<v8::Script>;

    #define V8_SCOPE() v8::Isolate::Scope isolate(fxCRL::v8_isolate); v8::Locker lock(fxCRL::v8_isolate); v8::HandleScope hs(fxCRL::v8_isolate);

    typedef struct
    {
        const char* name;
        v8::InvocationCallback callAsFunction;
        fxJSPropertyAttributes attributes;
    } fxJSFunctionCB;
    using fxJSChar = uint16_t;

    #define fxJSPropertyAttributeNone v8::PropertyAttribute::None
    #define fxJSPropertyAttributeReadOnly v8::PropertyAttribute::ReadOnly
    #define fxJSPropertyAttributeDontEnum v8::PropertyAttribute::DontEnum
    #define fxJSPropertyAttributeDontDelete v8::PropertyAttribute::DontDelete

    #define fxJSBindGetProperty(F) v8::Handle<v8::Value> F(v8::Local<v8::String> property, const v8::AccessorInfo& info)
    #define fxJSBindGetPropertyAt(F) v8::Handle<v8::Value> F(uint32_t index, const v8::AccessorInfo& info)
    #define fxJSBindSetProperty(F) v8::Handle<v8::Value> F(v8::Local<v8::String> property, v8::Local<v8::Value> value, const v8::AccessorInfo& info)
    #define fxJSBindSetPropertyAt(F) v8::Handle<v8::Value> F(uint32_t index, v8::Local<v8::Value> value, const v8::AccessorInfo& info)
    #define fxJSBindFree(F) void F(v8::Isolate* iso, v8::Persistent<v8::Value> object, void* parameter)
    #define fxJSBindConstructor(F) v8::Handle<v8::Value> F(const v8::Arguments& info)
    #define fxJSBindFunction(F) v8::Handle<v8::Value> F(const v8::Arguments& info)
    #define fxJSBindHasInstance(F) bool F(v8::Handle<v8::Value> object)

    #define fxJSFreeGetNative(C) (static_cast<C*>(parameter))
    #define fxJSGetNative(C) (static_cast<C*>(v8::Local<v8::External>::Cast(info.This()->GetInternalField(0))->Value()))
    #define fxJSCastNative(C, O) (static_cast<C*>(v8::Local<v8::External>::Cast(O->ToObject()->GetInternalField(0))->Value()))
    #define fxJSAllocString(T) v8::String::New(T)
    #define fxJSAllocGlobalString(T) v8::Persistent<v8::String>::New(v8::Isolate::GetCurrent(), v8::String::New(T))
    #define fxJSAllocStringCopy(T) T->ToString()
    #define fxJSFreeString(T)
    #define fxJSFreeGlobalString(T) T.Dispose(v8::Isolate::GetCurrent())
    #define fxJSFreeClass(T) T.Dispose(v8::Isolate::GetCurrent())

    #define fxJSAllocGlobalContext(V) v8::Context::New(nullptr, V)
    #define fxJSFreeGlobalContext(T) T->Exit();\
    T.Dispose(v8::Isolate::GetCurrent())
    #define fxJSGetGlobalObject(T) T->Global()
    #define fxJSRunScript(S, U) v8::Script::Compile(S, U)->Run()

    #define fxJSSetProperty(O, S, P, A) O->Set(S, P, A)
    #define fxJSSetPropertyAt(I, S, P, A) O->Set(I, P, A)
    #define fxJSIsEmpty(O) O.IsEmpty()
    #define fxJSIsNumber(V) V->IsNumber()
    #define fxJSIsInt32(V) V->IsInt32()
    #define fxJSIsUint32(V) V->IsUint32()
    #define fxJSIsString(V) V->IsString()
    #define fxJSIsFunction(V) V->IsFunction()
    #define fxJSIsInstanceOf(O, C) C::getJSClass()->HasInstance(O)
    //#define fxJSIsArray(V) V->IsArray()
    #define fxJSIsObject(V) V->IsObject()
    #define fxJSIsClass(O, C) C->HasInstance(O)
    #define fxJSEmpty() v8::Handle<v8::Data>()
    #define fxJSEmptyClass() v8::Handle<v8::FunctionTemplate>()
    #define fxJSEmptyObject() v8::Handle<v8::Object>()
    #define fxJSEmptyValue() v8::Handle<v8::Value>()
    #define fxJSEmptyContext() v8::Handle<v8::Context>()
    #define fxJSEmptyFunction() v8::Handle<v8::Function>()
    #define fxJSEmptyScript() v8::Handle<v8::Script>()
    #define fxJSEmptyGlobalContext() v8::Persistent<v8::Context>()
    #define fxJSRetain(O) (O = v8::Persistent<v8::Value>::New(v8::Isolate::GetCurrent(), O))
    #define fxJSRetainFunction(O) (O = v8::Persistent<v8::Function>::New(v8::Isolate::GetCurrent(), O))
    #define fxJSRetainObject(O) (O = v8::Persistent<v8::Object>::New(v8::Isolate::GetCurrent(), O))
    #define fxJSRelease(O) v8::Persistent<v8::Value>(O).Dispose(v8::Isolate::GetCurrent())
    #define fxJSReleaseFunction(O) v8::Persistent<v8::Function>(O).Dispose(v8::Isolate::GetCurrent())
    #define fxJSReleaseObject(O) v8::Persistent<v8::Object>(O).Dispose(v8::Isolate::GetCurrent())
    #define fxJSRetainConstructor(O)
    #define fxJSReleaseConstructor(O)

    #define fxJSCastNumber(V) V->NumberValue()
    #define fxJSCastInt32(V) V->Int32Value()
    #define fxJSCastUint32(V) V->Uint32Value()
    #define fxJSCastBoolean(V) V->BooleanValue()
    #define fxJSAllocScript(V) v8::Persistent<v8::Script>::New(v8::Isolate::GetCurrent(), v8::Script::Compile(V->ToString()))
    #define fxJSFreeScript(V) v8::Persistent<v8::Script>(V).Dispose(v8::Isolate::GetCurrent())
    #define fxJSCallScript(V) V->Run()

    #define fxJSMakeClassTemplate() v8::FunctionTemplate::New()
    #define fxJSMakeClass(C) v8::Persistent<v8::FunctionTemplate>::New(v8::Isolate::GetCurrent(), C)
    #define fxJSMakeObject(C) C->NewInstance()
    #define fxJSMakeEmptyObject() v8::Object::New()
    #define fxJSMakeConstructor(C, F) v8::Handle<v8::Function>()
    #define fxJSMakeFunctionWithCallback(S, T) v8::FunctionTemplate::New(T)->GetFunction()
    #define fxJSMakeNumber(T) v8::Number::New(T)
    #define fxJSMakeUndefined() v8::Undefined()
    #define fxJSMakeBoolean(T) v8::Boolean::New(T)
    #define fxJSMakeNull() v8::Null()
    #define fxJSMakeString(T) T

    #define fxJSGetObject() object
    #define fxJSGetArgCount() info.Length()
    #define fxJSGetArg(I) info[I]
    #define fxJSGetPropertyName() property
    #define fxJSGetPropertyValue() value
    #define fxJSStringGetSize(V) V->Utf8Length()
    #define fxJSStringGetLength(V) V->Length()
    #define fxJSStringToUnicode(T, B, S) T->Write(B, 0, S)
    #define fxJSStringToBuffer(T, B, S) T->WriteUtf8(B, S)
    #define fxJSGetProperty(O, V) O->Get(V)
    #define fxJSGetPropertyAt(O, I) O->Get(I)

    #define fxJSCallFunction(F, G, C, V) F->Call(G, C, V)
    #define fxJSSetPrivate(O, T) O->SetInternalField(0, v8::External::New(T))
    #define fxJSCastObject(V) V->ToObject()
    //#define fxJSCastArray(V) v8::Handle<v8::Array>::Cast(V->ToObject())
    #define fxJSCastFunction(V) v8::Handle<v8::Function>::Cast(V->ToObject())

    #define fxJSInit()	v8::Isolate* iso = v8::Isolate::New();\
    iso->Enter();\
    v8::HandleScope hs;
    #define fxJSQuit()
    #define fxJSHandleScope() v8::HandleScope hs;
    #define fxJSContextScope(C) v8::Context::Scope cs(C);

    #define fxJSSetterTrue()
    #define fxJSSetterFalse()

    #define fxJSSetClassName(T, S) T->SetClassName(v8::String::New(S))
    #define fxJSSetClassFunctions(T, F) for(size_t _i = 0; F[_i].name; _i++) T->InstanceTemplate()->Set(v8::String::New(F[_i].name), v8::FunctionTemplate::New(F[_i].callAsFunction), F[_i].attributes)
    #define fxJSSetParentClass(T, C) T->Inherit(C)
    #define fxJSSetClassConstructor(T, C) T->SetCallHandler(C)
    #define fxJSChooseConstructor(C, O) C->GetFunction()
    #define fxJSSetClassStorage(T, N) T->InstanceTemplate()->SetInternalFieldCount(N)
    #define fxJSSetClassFree(C, F)
    #define fxJSSetIndexedPropertyHandler(T, G, S) T->InstanceTemplate()->SetIndexedPropertyHandler(G, S)
    #define fxJSSetObjectFree(O, F) v8::Persistent<v8::Object>(O).MakeWeak(v8::Isolate::GetCurrent(), nullptr, F)
    #define fxJSFreeObject(O) O.ClearWeak(v8::Isolate::GetCurrent())
    #define fxJSFreeMemory(S) v8::V8::AdjustAmountOfExternalAllocatedMemory(-S)
    #define fxJSAllocMemory(S) v8::V8::AdjustAmountOfExternalAllocatedMemory(S)

    #define fxJSConstructorObject(O) info.This()
    #define fxJSGetArrayLength(A) A->Length()
    #define fxJSHasProperty(O, S) O->Has(S)

    #define fxJSMakeFunctionCallback(S, C) v8::FunctionTemplate::New(C)->GetFunction()
    #define fxJSCallConstructor(C, A, V) C->NewInstance(A, V)
    /*
     
     #define fxStrCaseEqual(T1, T2) (!strcasecmp(T1, T2))
     #define fxJSStringEqual(JT, CT) JSStringIsEqualToUTF8CString(JT, CT)
     
     
     //#define fxJSBindAlloc(F) void F(v8::ObjectSpace space, v8::AllocationAction action, int size)
     //#define fxJSBindFree(F) template<class C> void F(v8::Persistent<v8::Value> object, void* parameter)
     //#define fxJSBindFunction(F) JSValueRef F(JSContextRef ctx, JSObjectRef function, JSObjectRef object, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
     //#define fxJSBindContructor(F) JSObjectRef F(JSContextRef ctx, JSObjectRef constructor, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
     //#define fxJSBindHasProperty(F) bool F(JSContextRef ctx, JSObjectRef object, JSStringRef propertyName);
     #define fxJSBindGetProperty(F) v8::Handle<v8::Value> F(v8::Local<v8::String> property, const v8::AccessorInfo& info)
     //#define fxJSBindSetProperty(F) bool F(JSContextRef ctx, JSObjectRef object, JSStringRef propertyName, JSValueRef value, JSValueRef* exception)
     //#define fxJSBindDeleteProperty(F) bool F(JSContextRef ctx, JSObjectRef object, JSStringRef propertyName, JSValueRef* exception)
     //#define fxJSBindGetProperties(F) void F(JSContextRef ctx, JSObjectRef object, JSPropertyNameAccumulatorRef propertyNames)
     //#define fxJSBindHasInstance(F) bool F(JSContextRef ctx, JSObjectRef constructor, JSValueRef possibleInstance, JSValueRef* exception)
     //#define fxJSBindConvert(F) JSValueRef F(JSContextRef ctx, JSObjectRef object, JSType type, JSValueRef* exception)
     
     #define fxJSRetain(T) (T = v8::Persistent<v8::Object>::New(T))
     #define fxJSRelease(T) v8::Persistent<v8::Object>(T).Dispose()
     
     #define fxJSSetProperty(O, S, P, A) O->Set(S, P, A)
     
     #define fxJSGetNative(C) (static_cast<C*>(v8::Local<v8::External>::Cast(info.Holder()->GetInternalField(0))->Value()))
     #define fxJSCastNative(C, O) (static_cast<C*>(v8::Local<v8::External>::Cast(O)->Value()))
     */
#elif JAVASCRIPT_ENGINE_APPLE
    #include <JavaScriptCore/JavaScriptCore.h>

    using fxJSGlobalContext = JSGlobalContextRef;
    using fxJSContext = JSContextRef;
    using fxJSValue = JSValueRef;
    using fxJSObject = JSObjectRef;
    using fxJSArray = JSObjectRef;
    using fxJSFunction = JSObjectRef;
    using fxJSConstructor = JSObjectRef;
    using fxJSClass = JSClassRef;
    using fxJSClassTemplate = JSClassDefinition;
    using fxJSString = JSStringRef;
    using fxJSGlobalString = JSStringRef;
    using fxJSGlobalObject = JSObjectRef;
    using fxJSScript = JSStringRef;

    using fxJSFunctionCB = JSStaticFunction;
    using fxJSChar = JSChar;

    #define V8_SCOPE()

    #define fxJSPropertyAttributeNone kJSPropertyAttributeNone
    #define fxJSPropertyAttributeReadOnly kJSPropertyAttributeReadOnly
    #define fxJSPropertyAttributeDontEnum kJSPropertyAttributeDontEnum
    #define fxJSPropertyAttributeDontDelete kJSPropertyAttributeDontDelete

    #define fxStrCaseEqual(T1, T2) (!strcasecmp(T1, T2))
    #define fxJSStringEqual(JT, CT) JSStringIsEqualToUTF8CString(JT, CT)

    #define fxJSBindAlloc(F) void F(JSContextRef ctx, JSObjectRef object)
    #define fxJSBindFree(F) void F(JSObjectRef object)
    #define fxJSBindFunction(F) JSValueRef F(JSContextRef ctx, JSObjectRef function, JSObjectRef object, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    #define fxJSBindConstructor(F) JSObjectRef F(JSContextRef ctx, JSObjectRef constructor, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
    #define fxJSBindHasProperty(F) bool F(JSContextRef ctx, JSObjectRef object, JSStringRef propertyName);
    #define fxJSBindGetProperty(F) JSValueRef F(JSContextRef ctx, JSObjectRef object, JSStringRef propertyName, JSValueRef* exception)
    #define fxJSBindGetPropertyAt(F) JSValueRef F(JSContextRef ctx, JSObjectRef object, JSStringRef propertyName, JSValueRef* exception)
    #define fxJSBindSetProperty(F) bool F(JSContextRef ctx, JSObjectRef object, JSStringRef propertyName, JSValueRef value, JSValueRef* exception)
    #define fxJSBindSetPropertyAt(F) bool F(JSContextRef ctx, JSObjectRef object, JSStringRef propertyName, JSValueRef value, JSValueRef* exception)
    #define fxJSBindDeleteProperty(F) bool F(JSContextRef ctx, JSObjectRef object, JSStringRef propertyName, JSValueRef* exception)
    #define fxJSBindGetProperties(F) void F(JSContextRef ctx, JSObjectRef object, JSPropertyNameAccumulatorRef propertyNames)
    #define fxJSBindHasInstance(F) bool F(JSContextRef ctx, JSObjectRef constructor, JSValueRef possibleInstance, JSValueRef* exception)
    #define fxJSBindConvert(F) JSValueRef F(JSContextRef ctx, JSObjectRef object, JSType type, JSValueRef* exception)

    #define fxJSAllocGlobalContext() JSGlobalContextCreate(nullptr)
    #define fxJSFreeGlobalContext(T) JSGlobalContextRelease(T)
    #define fxJSGetGlobalObject(T) JSContextGetGlobalObject(T)
    #define fxJSMakeUndefined() JSValueMakeUndefined(fxCRL::js_context)
    #define fxJSMakeClass(T) JSClassCreate(&T)
    #define fxJSMakeClassTemplate() kJSClassDefinitionEmpty
    #define fxJSMakeArray(C, A) JSObjectMakeArray(fxCRL::js_context, C, A, nullptr)
    #define fxJSAllocString(T) JSStringCreateWithUTF8CString(T)
    #define fxJSAllocGlobalString(T) JSStringCreateWithUTF8CString(T)
    #define fxJSAllocStringCopy(T) JSValueToStringCopy(fxCRL::js_context, T, nullptr)
    #define fxJSStringGetSize(T) JSStringGetMaximumUTF8CStringSize(T)
    #define fxJSStringGetLength(V) JSStringGetLength(V)
    #define fxJSStringToUnicode(T, B, S) memcpy(B, JSStringGetCharactersPtr(T), S * sizeof(*B))
    #define fxJSStringToBuffer(T,B,S) JSStringGetUTF8CString(T, B, S)
    #define fxJSStringGetNative(T) JSStringGetCharactersPtr(T)
    #define fxJSMakeString(T) JSValueMakeString(fxCRL::js_context, T)
    #define fxJSFreeString(T) JSStringRelease(T)
    #define fxJSFreeGlobalString(T) JSStringRelease(T)
    #define fxJSFreeClass(T) JSClassRelease(T)
    #define fxJSMakeNumber(T) JSValueMakeNumber(fxCRL::js_context, T)
    #define fxJSMakeBoolean(T) JSValueMakeBoolean(fxCRL::js_context, T)
    #define fxJSMakeNull() JSValueMakeNull(fxCRL::js_context);

    #define fxJSRetain(O) JSValueProtect(fxCRL::js_context, O)
    #define fxJSRetainObject(O) JSValueProtect(fxCRL::js_context, O)
    #define fxJSRetainFunction(F) JSValueProtect(fxCRL::js_context, F)
    #define fxJSRetainConstructor(O) JSValueProtect(fxCRL::js_context, O)
    #define fxJSRelease(O) JSValueUnprotect(fxCRL::js_context, O)
    #define fxJSReleaseConstructor(O) JSValueUnprotect(fxCRL::js_context, O)

    #define fxJSIsString(T) JSValueIsString(fxCRL::js_context, T)
    #define fxJSIsFunction(T) JSObjectIsFunction(fxCRL::js_context, JSValueToObject(fxCRL::js_context, T, nullptr))
    #define fxJSIsNumber(T) JSValueIsNumber(fxCRL::js_context, T)
    #define fxJSIsBoolean(T) JSValueIsBoolean(fxCRL::js_context, T)
    #define fxJSIsClass(O, C) JSValueIsObjectOfClass(fxCRL::js_context, O, C)
    #define fxJSIsNull(T) JSValueIsNull(fxCRL::js_context, T)
    #define fxJSIsObject(O) JSValueIsObject(fxCRL::js_context, O)
    #define fxJSIsInstanceOf(O, C) JSValueIsInstanceOfConstructor(fxCRL::js_context, O, C::getJSConstructor(), nullptr)
    //#define fxJSIsArray(O) JSValueIsInstanceOfConstructor(fxCRL::js_context, O, fxCRL::_ArrayConstructor, nullptr)
    #define fxJSIsEmpty(O) (O == nullptr)
    #define fxJSEmpty() nullptr
    #define fxJSEmptyObject() nullptr
    #define fxJSEmptyClass() nullptr
    #define fxJSEmptyValue() nullptr
    #define fxJSEmptyContext() nullptr
    #define fxJSEmptyFunction() nullptr
    #define fxJSEmptyScript() nullptr
    #define fxJSEmptyGlobalContext() nullptr

    #define fxJSCastNumber(T) JSValueToNumber(fxCRL::js_context, T, nullptr)
    #define fxJSCastBoolean(T) JSValueToBoolean(fxCRL::js_context, T)

    #define fxJSGetObject() object
    #define fxJSGetFunction() function
    #define fxJSGetArg(I) arguments[I]
    #define fxJSGetArgCount() argumentCount
    #define fxJSGetPropertyValue() value
    #define fxJSGetPropertyName() propertyName
    #define fxJSGetConstructor() constructor
    #define fxJSChooseConstructor(C, O) O

    #define fxJSCallFunction(F, G, C, V) JSObjectCallAsFunction(fxCRL::js_context, F, G, C, V, nullptr)
    #define fxJSFreeGetNative(C) (static_cast<C*>(JSObjectGetPrivate(object)))
    #define fxJSGetNative(C) (static_cast<C*>(JSObjectGetPrivate(object)))
    #define fxJSCastNative(C, O) (static_cast<C*>(JSObjectGetPrivate(O)))
    #define fxJSCastObject(V) JSValueToObject(fxCRL::js_context, V, nullptr)
    //#define fxJSCastArray(V) JSValueToObject(fxCRL::js_context, V, nullptr)
    #define fxJSCastFunction(V) JSValueToObject(fxCRL::js_context, V, nullptr)
    #define fxJSMakeObject(C) JSObjectMake(fxCRL::js_context, C, nullptr)
    #define fxJSMakeEmptyObject() JSObjectMake(fxCRL::js_context, nullptr, nullptr)
    #define fxJSMakeConstructor(C, F) JSObjectMakeConstructor(fxCRL::js_context, C, F)
    #define fxJSMakeFunction(N, U, C, A, S, L) JSObjectMakeFunction(fxCRL::js_context, N, C, A, S, U, L, nullptr)
    #define fxJSMakeFunctionCallback(S, T) JSObjectMakeFunctionWithCallback(fxCRL::js_context, S, T)
    #define fxJSRunScript(S, U) JSEvaluateScript(fxCRL::js_context, S, nullptr, U, 0, nullptr)
    #define fxJSSetPrivate(T, P) JSObjectSetPrivate(T, P)
    #define fxJSSetProperty(O, S, P, A) JSObjectSetProperty(fxCRL::js_context, O, S, P, A, nullptr)
    #define fxJSSetPropertyAt(I, S, P, A) JSObjectSetPropertyAtIndex(fxCRL::js_context, O, I, P, nullptr)
    #define fxJSGetProperty(O, S) JSObjectGetProperty(fxCRL::js_context, O, S, nullptr)
    #define fxJSGetPropertyAt(O, I) JSObjectGetPropertyAtIndex(fxCRL::js_context, O, I, nullptr)
    #define fxJSGetPrototype(O) JSObjectGetPrototype(fxCRL::js_context, O)
    #define fxJSSetPrototype(O, T) JSObjectSetPrototype(fxCRL::js_context, O, T)
    #define fxJSAllocScript(V) JSValueToStringCopy(fxCRL::js_context, V, nullptr)
    #define fxJSFreeScript(V) JSStringRelease(V)
    #define fxJSCallScript(V) JSEvaluateScript(fxCRL::js_context, V, nullptr, nullptr, 0, nullptr)

    #define fxJSInit()
    #define fxJSQuit()
    #define fxJSHandleScope()
    #define fxJSContextScope(C)
    #define fxJSSetterTrue() true
    #define fxJSSetterFalse() false

    #define fxJSSetClassName(T, S) (T.className = S)
    #define fxJSSetClassFunctions(T, F) (T.staticFunctions = F)
    #define fxJSSetParentClass(T, C) (T.parentClass = C)
    #define fxJSSetClassConstructor(T, C) T.callAsConstructor = C
    #define fxJSSetClassStorage(T, N)
    #define fxJSSetClassFree(C, F) (C.finalize = F)
    #define fxJSSetIndexedPropertyHandler(T, G, S) T.getProperty = G; T.setProperty = S
    #define fxJSSetObjectFree(O, F)
    #define fxJSFreeObject(O) (O = nullptr)
    #define fxJSFreeMemory(S)
    #define fxJSAllocMemory(S)

    #define fxJSGetArrayLength(A) JSValueToNumber(fxCRL::js_context, JSObjectGetProperty(fxCRL::js_context, A, fxCRL::jsStr_length, nullptr), nullptr)
    #define fxJSHasProperty(O, S) JSObjectHasProperty(fxCRL::js_context, O, S)

    #define fxJSConstructorObject(C) JSObjectMake(fxCRL::js_context, C, nullptr)
    #define fxJSCallConstructor(C, A, V) JSObjectCallAsConstructor(fxCRL::js_context, C, A, V, nullptr)
#else
    #error "Please choose a JavaScript Engine using JAVASCRIPT_ENGINE_V8 for V8 or JAVASCRIPT_ENGINE_APPLE for JavaScriptCore"
#endif
////////////////////////////////////////////////////////////////

#endif
