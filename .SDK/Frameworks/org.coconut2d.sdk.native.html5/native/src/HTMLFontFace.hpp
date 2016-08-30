/* ***** BEGIN LICENSE BLOCK *****
*
* Copyright (C) 2013-2016 www.mobilefx.com
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
//	    __  __________  _____    ______            __  ______
//	   / / / /_  __/  |/  / /   / ____/___  ____  / /_/ ____/___ _________
//	  / /_/ / / / / /|_/ / /   / /_  / __ \/ __ \/ __/ /_  / __ `/ ___/ _ \
//	 / __  / / / / /  / / /___/ __/ / /_/ / / / / /_/ __/ / /_/ / /__/  __/
//	/_/ /_/ /_/ /_/  /_/_____/_/    \____/_/ /_/\__/_/    \__,_/\___/\___/
//
// ==================================================================================================================================

#ifndef __HTMLFontFace_H__
#define __HTMLFontFace_H__

#include "Coconut2D.hpp"

class HTMLFontFace
{
private:
	HTMLFontFace(FT_Face ftFace, cairo_font_face_t *crFace);

public:
	FT_Face _ftFace;
	cairo_font_face_t *_crFace;

	~HTMLFontFace();

	static bool parseCSSFont(String font, String& fontFamily, int32_t& fontSizeInPixels, String& fontStyle, String& fontWeight);
	static String getFontName(String faceName, String faceStyle, String faceWeight);
	static HTMLFontFace* getFont(String fontName);
	static String getFontPath(String fontName);
};

extern bool _initLibrary;
extern FT_Library ftLibrary;
extern cairo_user_data_key_t key;
extern std::map<String, HTMLFontFace*> fontsCache;

#endif // __HTML_FONTFACE_H__
