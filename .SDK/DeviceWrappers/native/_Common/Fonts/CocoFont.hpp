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
