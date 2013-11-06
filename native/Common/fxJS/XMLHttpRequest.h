#ifndef _XMLHttpRequest_h
#define _XMLHttpRequest_h

#include "Common.h"
#include "fxCRL.h"

class XMLHttpRequest
{
protected:
    
    static fxJSClass _Class;
    static fxJSConstructor _ConstructorObject;
    static fxObjectUID counter;
    
    static std::list<XMLHttpRequest*> requestList;
    
    enum class HttpMethod : uint8_t
    {
        None = 0,
        Get,
        Head,
        Post,
        Put,
        Delete,
        Trace,
        Connect
    } method;
    
    char* url;
    std::atomic_flag waiting;
    std::vector<char> header;
    std::vector<char> data;
    
    #ifdef ENABLE_CURL_SUPPORT
    CURLcode result;
    #endif /* ENABLE_CURL_SUPPORT */
    
    fxObjectUID uid;
    fxJSObject jsThis;
    std::thread* tRequest;
    
public:
    
    /////////////////////////////////////////////////////////////////////////////////////////////////////////
    XMLHttpRequest() : method(HttpMethod::None), url(nullptr), waiting(ATOMIC_FLAG_INIT), header(1), data(1), uid(counter++) {}
    ~XMLHttpRequest() { delete[] url; if(tRequest) { tRequest->join(); delete tRequest; } }
    
    /////////////////////////////////////////////////////////////////////////////////////////////////////////
    inline static fxJSClass getJSClass() { return _Class; }
    inline static fxJSConstructor getJSConstructor() { return fxJSChooseConstructor(_Class, _ConstructorObject); }
    inline fxJSObject getJSObject() { return jsThis; }
    
    /////////////////////////////////////////////////////////////////////////////////////////////////////////
    inline static void init()
    {
        counter = 0;
        fxJSFunctionCB fun[] =
        {
            {"open", _open, fxJSPropertyAttributeNone},
            {"setRequestHeader", _setRequestHeader, fxJSPropertyAttributeNone},
            {"send", _send, fxJSPropertyAttributeNone},
            {"abort", _abort, fxJSPropertyAttributeNone},
            {nullptr, nullptr, fxJSPropertyAttributeNone}
        };
        fxJSClassTemplate temp = fxJSMakeClassTemplate();
        fxJSSetClassStorage(temp, 1);
        fxJSSetClassName(temp, "XMLHttpRequest");
        fxJSSetClassConstructor(temp, _Constructor);
        fxJSSetClassFree(temp, fxCRL::JSFreeCB<XMLHttpRequest>);
        fxJSSetClassFunctions(temp, fun);
        _Class = fxJSMakeClass(temp);
        _ConstructorObject = fxJSMakeConstructor(_Class, _Constructor);
        fxJSRetainConstructor(_ConstructorObject);
    }
    
    /////////////////////////////////////////////////////////////////////////////////////////////////////////
    inline static void quit()
    {
        fxJSReleaseConstructor(_ConstructorObject);
        fxJSFreeClass(_Class);
    }
    
    /////////////////////////////////////////////////////////////////////////////////////////////////////////
    static size_t tomemory(void* contents, size_t size, size_t nmemb, void* ptr)
    {
        std::vector<char>* v = static_cast<std::vector<char>*>(ptr);
        size_t s = size * nmemb;
        //LOGI("resize: %zu + %zu\n", strlen(&(*v)[0]), s);
        size_t ps = v->size() - 1;
        v->resize(ps + s + 1);
        memcpy(&((*v)[ps]), contents, s);
        (*v)[ps + s] = 0;
        //LOGI("size: %zu\n", v->size());
        return s;
    }
    
    /////////////////////////////////////////////////////////////////////////////////////////////////////////
    static void tick()
    {
        #ifdef ENABLE_CURL_SUPPORT
        std::list<XMLHttpRequest*>::iterator it = requestList.begin();
        while(it != requestList.end())
        {
            if(!((*it)->waiting.test_and_set()))
            {
                V8_SCOPE();
                if((*it)->result == CURLE_OK)
                {
                    fxJSString jstr = fxJSAllocString(&((*it)->data[0]));
                    fxFile::createWithData("./http.txt", &((*it)->data[0]));
                    fxJSSetProperty((*it)->jsThis, fxCRL::jsStr_responseText, fxJSMakeString(jstr), fxJSPropertyAttributeNone);
                    fxJSFreeString(jstr);
                    fxJSValue js_onload = fxJSGetProperty((*it)->jsThis, fxCRL::jsStr_onload);
                    if(!fxJSIsFunction(js_onload))
                    {
                        LOGW("NOT A FUNCTION!");
                    }
                    else
                    {
                        fxJSCallFunction(fxJSCastFunction(js_onload), (*it)->jsThis, 0, nullptr);
                    }
                }
                else
                {
                    LOGW("curl error: %s\n", curl_easy_strerror((*it)->result));
                }
                requestList.erase(it++);
            }
            else ++it;
        }
        #endif
    }
    
    /////////////////////////////////////////////////////////////////////////////////////////////////////////
    static void request(XMLHttpRequest* t)
    {
        #ifdef ENABLE_CURL_SUPPORT
        CURL* curl = curl_easy_init();
        //curl_slist* httpheader = nullptr;
        //httpheader = curl_slist_append(httpheader, "Accept-Charset: UTF-8");
        //httpheader = curl_slist_append(httpheader, "Accept:");
        //curl_easy_setopt(curl, CURLOPT_HTTPHEADER, httpheader);
        curl_easy_setopt(curl, CURLOPT_NOSIGNAL, 1);
        curl_easy_setopt(curl, CURLOPT_URL, t->url);
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1);
        curl_easy_setopt(curl, CURLOPT_USERAGENT, APPNAME);
        //curl_easy_setopt(curl, CURLOPT_VERBOSE, 1);
        //curl_easy_setopt(curl, CURLOPT_HEADER, 1);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, tomemory);
        curl_easy_setopt(curl, CURLOPT_WRITEHEADER, static_cast<void*>(&t->header));
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, static_cast<void*>(&t->data));
        t->result = curl_easy_perform(curl);
        t->waiting.clear();
        //curl_slist_free_all(httpheader);
        curl_easy_cleanup(curl);
        #endif
    }
    
    /////////////////////////////////////////////////////////////////////////////////////////////////////////
    static fxJSBindFunction(_open)
    {
        if(fxJSGetArgCount() > 1
           && fxJSIsString(fxJSGetArg(0))
           && fxJSIsString(fxJSGetArg(1)))
        {
            XMLHttpRequest* t = fxJSGetNative(XMLHttpRequest);
            
            fxJSString jmethod = fxJSAllocStringCopy(fxJSGetArg(0));
            fxJSString jurl = fxJSAllocStringCopy(fxJSGetArg(1));
            
            size_t jmethodsize = fxJSStringGetSize(jmethod);
            size_t jurlsize = fxJSStringGetSize(jurl);
            
            char* cmethod = new char[jmethodsize + 1]; cmethod[jmethodsize] = 0;
            t->url = new char[jurlsize + 1]; t->url[jurlsize] = 0;
            
            fxJSStringToBuffer(jmethod, cmethod, jmethodsize);
            fxJSStringToBuffer(jurl, t->url, jurlsize);
            
            fxJSFreeString(jmethod);
            fxJSFreeString(jurl);
            
            if(!strncmp(cmethod, "GET", 3)) t->method = HttpMethod::Get;
            else if(!strncmp(cmethod, "HEAD", 4)) t->method = HttpMethod::Head;
            else if(!strncmp(cmethod, "POST", 4)) t->method = HttpMethod::Post;
            else if(!strncmp(cmethod, "PUT", 3)) t->method = HttpMethod::Put;
            else if(!strncmp(cmethod, "DELETE", 6)) t->method = HttpMethod::Delete;
            else if(!strncmp(cmethod, "TRACE", 5)) t->method = HttpMethod::Trace;
            else if(!strncmp(cmethod, "CONNECT", 7)) t->method = HttpMethod::Connect;
        }
        return fxJSMakeUndefined();
    }
    
    /////////////////////////////////////////////////////////////////////////////////////////////////////////
    static fxJSBindFunction(_setRequestHeader)
    {
        return fxJSMakeUndefined();
    }
    
    /////////////////////////////////////////////////////////////////////////////////////////////////////////
    static fxJSBindFunction(_send)
    {
        #ifdef ENABLE_CURL_SUPPORT
        XMLHttpRequest* t = fxJSGetNative(XMLHttpRequest);
        if(fxJSGetArgCount() > 0)
        {
            // TODO: parse data to send
        }
        t->waiting.test_and_set();
        t->tRequest = new std::thread(request, t);
        requestList.push_back(t);
        #else
        LOGW("XMLHttpRequest not supported!");
        #endif /* ENABLE_CURL_SUPPORT */
        return fxJSMakeUndefined();
    }
    
    /////////////////////////////////////////////////////////////////////////////////////////////////////////
    static fxJSBindFunction(_abort)
    {
        return fxJSMakeUndefined();
    }
    
    /////////////////////////////////////////////////////////////////////////////////////////////////////////
    static fxJSBindConstructor(_Constructor)
    {
        XMLHttpRequest* t = new XMLHttpRequest();
        
        t->jsThis = fxJSConstructorObject(_Class);
        fxJSRetainObject(t->jsThis);
        fxJSSetObjectFree(t->jsThis, fxCRL::JSFreeCB<XMLHttpRequest>);
        fxJSSetPrivate(t->jsThis, t);
        fxJSSetProperty(t->jsThis, fxCRL::jsStr___uid, fxJSMakeNumber(t->uid), fxJSPropertyAttributeReadOnly);
        
        fxJSAllocMemory(sizeof(XMLHttpRequest));
        
        return t->jsThis;
    }
    
};

#endif
