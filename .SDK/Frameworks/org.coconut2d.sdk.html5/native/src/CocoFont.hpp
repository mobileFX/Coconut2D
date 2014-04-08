//
//  CocoFont.hpp
//  CocoEngine
//
//  Created by Administrator on 1/24/14.
//
//

#ifndef __CocoEngine__CocoFont__
#define __CocoEngine__CocoFont__

#include "Coconut2D.hpp"
#include "fxFontFace.h"
#include "ArrayBuffer.hpp"

/////////////////////////////////////////////////////////////////////////////////////////////////////////
struct CocoFontChar
{
    size_t i;
    fxRect<int16_t> rect;
    uint16_t horiAdvance;
    int* horiKernings;
    unsigned char *data; // we use 1 byte per pixel (FT_PIXEL_MODE_GRAY)
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////
class CocoFont
{
public:
    std::map<uint16_t, CocoFontChar> chars;
    uint16_t height;
    uint16_t maxHoriAdvance;
	CocoFont(float fontSize, String fontName, fxFontFace::FONT_STYLE style, String fontChars);
	~CocoFont();
	void fillText(ArrayBuffer* imageDataBuffer, int width, String text, float x, float y);
	float measureText(String text);
};

#endif /* defined(__CocoEngine__CocoFont__) */
