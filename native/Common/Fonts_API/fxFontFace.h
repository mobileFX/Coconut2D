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
//	    ____     ______            __  ______              
//	   / __/  __/ ____/___  ____  / /_/ ____/___ _________ 
//	  / /_| |/_/ /_  / __ \/ __ \/ __/ /_  / __ `/ ___/ _ \
//	 / __/>  </ __/ / /_/ / / / / /_/ __/ / /_/ / /__/  __/
//	/_/ /_/|_/_/    \____/_/ /_/\__/_/    \__,_/\___/\___/ 
//	                                                       
// ==================================================================================================================================

#ifndef _fxFontFace_h
#define _fxFontFace_h

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


