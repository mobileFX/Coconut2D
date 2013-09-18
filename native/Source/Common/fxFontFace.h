#ifndef _fxFontFace_h
#define _fxFontFace_h

#include "Common.h"
#include "fxFile.h"

#ifdef ENABLE_FREETYPE_SUPPORT

class fxFontFace : public fxFile
{
private:
    static FT_Library ftLibrary;
    static std::map<std::string, fxFontFace*> fonts;
protected:
    FT_Face ftFace;
    bool ftKerning;
public:
    static void add(const char* str, bool isAsset = true)
    {
        std::string name(str);
        name = name.substr(name.find_last_of("/\\") + 1);
        name = name.substr(0, name.find_last_of("."));
        fonts.insert(std::pair<std::string, fxFontFace*>(name, new fxFontFace(str, isAsset)));
        LOGI("@font-face %s loaded\n", name.c_str());
    }
    static const fxFontFace* get(const char* str)
    {
        std::map<std::string, fxFontFace*>::iterator it = fonts.find(std::string(str));
        if(it != fonts.end()) return it->second;
        return nullptr;
    }
    static void init()
    {
        if(FT_Init_FreeType(&ftLibrary)) { LOGW("Could not initialize FreeType library!\n"); }
        else { LOGI("FreeType OK!\n"); }
    }
    static void quit()
    {
        std::map<std::string, fxFontFace*>::iterator it = fonts.begin();
        while(it != fonts.end()) delete (it++)->second;
        fonts.clear();
        FT_Done_FreeType(ftLibrary);
    }
    
    fxFontFace(const char* str, bool isAsset) : fxFile(str, isAsset), ftFace(nullptr)
    {
        int er = 0;
        if((er = FT_New_Memory_Face(ftLibrary, (const FT_Byte*)getData(), length, 0, &ftFace)))
        {
            LOGW("Could not load FreeType Face(%d)!\n", er);
        }
        /*else if(FT_Select_Charmap(ftFace, FT_ENCODING_UNICODE))
         {
         LOGW("Could not select UNICODE encoding!\n");
         }*/
        ftKerning = FT_HAS_KERNING(ftFace);
    }
    ~fxFontFace()
    {
        if(!ftFace) return;
        FT_Done_Face(ftFace);
        ftFace = nullptr;
    }
    inline FT_Face getFace() const { return ftFace; }
    inline bool hasKerning() const { return ftKerning; }
};
#else

class fxFontFace : public fxFile
{
public:
    static void add(const char* str, bool isAsset = true) { LOGW("Fonts not supported!\n"); }
    static const fxFontFace* get(const char* str) { LOGW("Fonts not supported!\n"); return nullptr; }
    static void init() { LOGW("Fonts not supported!\n"); }
    static void quit(){ LOGW("Fonts not supported!\n"); }
    
    fxFontFace(const char* str, bool isAsset) : fxFile(str, isAsset) { LOGW("Fonts not supported!\n"); }
    ~fxFontFace() {}
    inline void getFace() const { LOGW("Fonts not supported!\n"); }
    inline bool hasKerning() const { LOGW("Fonts not supported!\n"); return false; }
};

#endif /* ENABLE_FREETYPE_SUPPORT */

#endif
