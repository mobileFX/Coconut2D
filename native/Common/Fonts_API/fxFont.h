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
//	   ______                 ______            __ 
//	  / ____/___  _________  / ____/___  ____  / /_
//	 / /   / __ \/ ___/ __ \/ /_  / __ \/ __ \/ __/
//	/ /___/ /_/ / /__/ /_/ / __/ / /_/ / / / / /_  
//	\____/\____/\___/\____/_/    \____/_/ /_/\__/  
//	                                               
// ==================================================================================================================================

#ifndef _fxFont_h
#define _fxFont_h

#include "Common.h"
#include "ArrayBuffer.h"
#include "fxFontFace.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////
struct fxFontChar
{
    size_t i;
    fxRect<int16_t> rect;
    uint16_t horiAdvance;
    int* horiKernings;
    unsigned char *data; // we use 1 byte per pixel (FT_PIXEL_MODE_GRAY)
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////
class fxFont
{
protected:
    
    static fxJSClass _Class;
    static fxJSConstructor _ConstructorObject;
    
    std::map<fxJSChar, fxFontChar> chars;
    uint16_t height;
    uint16_t maxHoriAdvance;
    fxJSObject jsThis;
    
public:
    
    /////////////////////////////////////////////////////////////////////////////////////////////////////////
    inline static fxJSClass getJSClass() { return _Class; }
    inline static fxJSConstructor getJSConstructor() { return fxJSChooseConstructor(_Class, _ConstructorObject); }
    inline fxJSObject getJSObject() { return jsThis; }
    
    /////////////////////////////////////////////////////////////////////////////////////////////////////////
    inline static void init()
    {
        fxJSFunctionCB fun[] = {
            {"fillText", _fillText, fxJSPropertyAttributeNone},
            {"measureText", _measureText, fxJSPropertyAttributeNone},
            {nullptr, nullptr, fxJSPropertyAttributeNone}
        };
        fxJSClassTemplate temp = fxJSMakeClassTemplate();
        fxJSSetClassStorage(temp, 1);
        fxJSSetClassName(temp, "fxFont");
        fxJSSetClassConstructor(temp, _Constructor);
        fxJSSetClassFree(temp, fxCRL::JSFreeCB<fxFont>);
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
    static fxJSBindConstructor(_Constructor)
    {
        fxJSValue ret = fxJSMakeNull();
        //if(!info.IsConstructCall()) return info.This();
        if(fxJSGetArgCount() > 2
           && fxJSIsNumber(fxJSGetArg(0))
           && fxJSIsString(fxJSGetArg(1))
           && fxJSIsString(fxJSGetArg(2)))
        {
            fxJSString jfont = fxJSAllocStringCopy(fxJSGetArg(1));
            fxJSString jchars = fxJSAllocStringCopy(fxJSGetArg(2));
            size_t jfontsize = fxJSStringGetSize(jfont);
            size_t charlen = fxJSStringGetLength(jchars);
            
            char* cfont = new char[jfontsize + 1];
            cfont[jfontsize] = 0;
            fxJSChar* cchars = new fxJSChar[charlen];
            
            fxJSStringToBuffer(jfont, cfont, jfontsize);
            fxJSStringToUnicode(jchars, cchars, charlen);
            
            const fxFontFace* fc = fxFontFace::get(cfont);
            if(!fc) { LOGW("Wrong font-face!\n"); }
            else
            {
                double size = fxJSCastNumber(fxJSGetArg(0));
                
                fxFont* t = new fxFont(size, fc, cchars, charlen);
                
                t->jsThis = fxJSConstructorObject(_Class);
                fxJSRetainObject(t->jsThis);
                fxJSSetObjectFree(t->jsThis, fxCRL::JSFreeCB<fxFont>);
                fxJSSetPrivate(t->jsThis, t);
                
                fxJSSetProperty(t->jsThis, fxCRL::jsStr_height, fxJSMakeNumber(t->height), fxJSPropertyAttributeReadOnly);
                fxJSSetProperty(t->jsThis, fxCRL::jsStr_maxAdvance, fxJSMakeNumber(t->maxHoriAdvance), fxJSPropertyAttributeReadOnly);
                
                fxJSAllocMemory(sizeof(fxFont));
                
                ret = t->jsThis;
            }
            
            delete[] cfont;
            delete[] cchars;
            fxJSFreeString(jfont);
            fxJSFreeString(jchars);
        }
        return fxJSCastObject(ret);
    }
    
#ifdef ENABLE_FREETYPE_SUPPORT
    /////////////////////////////////////////////////////////////////////////////////////////////////////////
    fxFont(uint16_t i_height, const fxFontFace* fc, fxJSChar* i_chars, size_t i_charlen) : height(i_height), maxHoriAdvance(0)
    {
        FT_Face face = fc->getFace();
        //if(FT_Set_Char_Size(face, 0, height << 6, 0, 0)) { LOGW("Error Freetype: Could not set font char size\n"); }
        if(FT_Set_Pixel_Sizes(face, 0, height)) { LOGW("Error Freetype: Could not set font char size\n"); }
        else
        {
            FT_UInt char_index[i_charlen];
            for(size_t i = i_charlen; i--;) char_index[i] = FT_Get_Char_Index(face, (FT_ULong)(i_chars[i]));
            for(size_t l = i_charlen; l--;)
            {
                if(FT_Load_Glyph(face, char_index[l], FT_LOAD_RENDER)) { LOGW("Error FreeType: Could not load glyph\n"); }
                else
                {
                    if(face->glyph->bitmap.pixel_mode != FT_PIXEL_MODE_GRAY) { LOGW("Wrong FT_Pixel_Mode!\n"); }
                    else
                    {
                        fxFontChar c;
                        c.i = l;
                        c.rect.pos.x = face->glyph->metrics.horiBearingX >> 6;
                        c.rect.pos.y = (face->size->metrics.ascender - face->glyph->metrics.horiBearingY) >> 6;
                        c.rect.size.x = face->glyph->bitmap.width;
                        c.rect.size.y = face->glyph->bitmap.rows;
                        c.horiAdvance = face->glyph->advance.x >> 6;
                        if(c.horiAdvance > maxHoriAdvance) maxHoriAdvance = c.horiAdvance;
                        c.data = new unsigned char[c.rect.size.x * c.rect.size.y];
                        memcpy(c.data, face->glyph->bitmap.buffer, c.rect.size.x * c.rect.size.y);
                        if(!fc->hasKerning()) c.horiKernings = nullptr;
                        else
                        {
                            c.horiKernings = new int[i_charlen];
                            FT_Vector tk;
                            for(size_t r = i_charlen; r--;)
                            {
                                FT_Get_Kerning(face, char_index[l], char_index[r], FT_KERNING_DEFAULT, &tk);
                                c.horiKernings[r] = tk.x;
                            }
                        }
                        chars.insert(std::pair<fxJSChar, fxFontChar>(i_chars[l], c));
                    }
                }
            }
        }
    }
#else
	/////////////////////////////////////////////////////////////////////////////////////////////////////////
    fxFont(uint16_t i_height, const fxFontFace* fc, fxJSChar* i_chars, size_t i_charlen) : height(i_height), maxHoriAdvance(0)
    {
        LOGW("Fonts not supported!\n");
    }
#endif
    
    /////////////////////////////////////////////////////////////////////////////////////////////////////////
    static fxJSBindFunction(_fillText)
    {
        if(fxJSGetArgCount() > 2
           && fxJSIsClass(fxJSGetArg(0), ArrayBuffer::getJSClass())
           && fxJSIsNumber(fxJSGetArg(1))
           && fxJSIsString(fxJSGetArg(2)))
        {
            fxFont* t = fxJSGetNative(fxFont);
            fxPoint<int> pos = {0, 0};
            if(fxJSGetArgCount() > 3 && fxJSIsNumber(fxJSGetArg(3))) pos.x = fxJSCastNumber(fxJSGetArg(3));
            if(fxJSGetArgCount() > 4 && fxJSIsNumber(fxJSGetArg(4))) pos.y = fxJSCastNumber(fxJSGetArg(4));
            ArrayBuffer* ab = fxJSCastNative(ArrayBuffer, fxJSCastObject(fxJSGetArg(0)));
            
            fxJSString jstr = fxJSAllocStringCopy(fxJSGetArg(2));
            size_t str_len = fxJSStringGetLength(jstr);
            
            fxJSChar* cstr = new fxJSChar[str_len];
            fxJSStringToUnicode(jstr, cstr, str_len);
            
            t->fillText(ab, fxJSCastNumber(fxJSGetArg(1)), cstr, str_len, pos);
            
            delete[] cstr;
            fxJSFreeString(jstr);
        }
        return fxJSMakeUndefined();
    }
    
    /////////////////////////////////////////////////////////////////////////////////////////////////////////
    static fxJSBindFunction(_measureText)
    {
        if(fxJSGetArgCount() > 0
           && fxJSIsString(fxJSGetArg(0)))
        {
            fxFont* t = fxJSGetNative(fxFont);
            
            fxJSString jstr = fxJSAllocStringCopy(fxJSGetArg(0));
            size_t str_len = fxJSStringGetLength(jstr);
            
            fxJSChar* cstr = new fxJSChar[str_len];
            fxJSStringToUnicode(jstr, cstr, str_len);
            
            size_t ret = t->measureText(cstr, str_len);
            
            delete[] cstr;
            fxJSFreeString(jstr);
            
            return fxJSMakeNumber(ret);
        }
        return fxJSMakeUndefined();
    }
    
    /////////////////////////////////////////////////////////////////////////////////////////////////////////
    void fillText(ArrayBuffer* buffer, size_t width, fxJSChar* str, size_t str_len, fxPoint<int> pen)
    {   // We only use the ArrayBuffer of an Int32Array with byteOffset = 0 (BYTES_PER_ELEMENT = 4) in RGBA format
        std::map<fxJSChar, fxFontChar>::iterator it;
        fxFontChar* c = nullptr;
        for(size_t i = 0; i < str_len; i++)
        {
            if((it = chars.find(str[i])) == chars.end()) return;
            if(c && c->horiKernings) pen.x += c->horiKernings[it->second.i];
            c = &(it->second);
            for(size_t ix = c->rect.size.x; ix--;)
                for(size_t iy = c->rect.size.y; iy--;)
                {
                    unsigned char* cp = (unsigned char*)((*buffer)[((pen.y + c->rect.pos.y + iy) * width + (pen.x + c->rect.pos.x + ix)) * 4]);
                    if(cp && c->data[iy * c->rect.size.x + ix])
                    {
                        cp[0] = 0xFF;
                        cp[1] = 0xFF;
                        cp[2] = 0xFF;
                        cp[3] |= c->data[iy * c->rect.size.x + ix];
                    }
                }
            pen.x += c->horiAdvance;
        }
    }
    
    /////////////////////////////////////////////////////////////////////////////////////////////////////////
    size_t measureText(fxJSChar* str, size_t str_len)
    {
        size_t ret = 0;
        std::map<fxJSChar, fxFontChar>::iterator it;
        fxFontChar* c = nullptr;
        for(size_t i = 0; i < str_len; i++)
        {
            if((it = chars.find(str[i])) == chars.end()) return ret;
            if(c && c->horiKernings) ret += c->horiKernings[it->second.i];
            c = &(it->second);
            ret += c->horiAdvance;
        }
        return ret;
    }
};

#endif
