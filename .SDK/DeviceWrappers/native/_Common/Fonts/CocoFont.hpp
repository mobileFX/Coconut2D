/* ***** BEGIN LICENSE BLOCK *****
 *
 * Copyright (C) 2013-2014 www.coconut2D.org
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

#ifndef __CocoEngine__CocoFont__
#define __CocoEngine__CocoFont__

#include "Coconut2D.hpp"
#include "fxFontFace.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////
struct CocoFontChar
{
    uint16_t charIndex;
    fxRect<int16_t> rect;
    uint16_t horiAdvance;
    std::map<uint16_t, int> horiKernings;
    uint8_t *data; // we use 1 byte per pixel (FT_PIXEL_MODE_GRAY)
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////
class CocoFont
{
public:
    std::map<uint16_t, CocoFontChar> chars;
    FT_Face face;
    uint16_t height;
	CocoFont(float fontSize, String fontName, bool bold, bool oblique);
	~CocoFont();
	void fillText(ArrayBuffer* imageDataBuffer, int width, String text, float x, float y, float R, float G, float B, float A);
	float measureText(String text);
};

#endif /* defined(__CocoEngine__CocoFont__) */
