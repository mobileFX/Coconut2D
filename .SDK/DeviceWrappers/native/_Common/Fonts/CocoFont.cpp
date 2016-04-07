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

#include "CocoFont.hpp"

#define BYTE_VALUE(V)	(uint8_t)(V<0?0:(V>255?255:V))

/////////////////////////////////////////////////////////////////////////////////////////////////////////
CocoFont::CocoFont(String fontName, float fontSize, bool bold, bool italic)
{
	height = (uint16_t) fontSize;

	CocoFontsCache::FONT_STYLE style;
	if(bold)
	{
		if(italic) style = CocoFontsCache::FONT_STYLE::BoldItalic;
		else style = CocoFontsCache::FONT_STYLE::Bold;
	}
	else
	{
		if(italic) style = CocoFontsCache::FONT_STYLE::Italic;
		else style = CocoFontsCache::FONT_STYLE::Regular;
	}

	face = CocoFontsCache::get(fontName, style);

	if(!face)
	{
		trace("Invalid font");
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
CocoFont::~CocoFont()
{
	while(chars.size())
	{
		delete[] chars.begin()->second.data;
		chars.erase(chars.begin());
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
void CocoFont::fillText(ArrayBuffer* imageDataBuffer, int width, String text, int x, int y, float R, float G, float B, float A)
{
	// We only use the ArrayBuffer of an Int32Array with byteOffset = 0 (BYTES_PER_ELEMENT = 4) in RGBA format

	if(FT_Set_Pixel_Sizes(face, 0, height))
	{
		trace("Freetype could not set font char size");
		return;
	}

	std::map<uint16_t, CocoFontChar>::iterator it;
	CocoFontChar* c = nullptr;

	for(int i = 0; i < text.size(); i++)
	{
        uint16_t ch = text.charCodeAt(i);
        if((it = chars.find(ch)) == chars.end())
		{
			// Retrieve glyph index from character code
			CocoFontChar chr;
			chr.charIndex = (uint16_t) FT_Get_Char_Index(face, (FT_ULong)(ch));

			// Load glyph image into the slot (erase previous one)
			if(!FT_Load_Glyph(face, chr.charIndex, FT_LOAD_NO_HINTING|FT_LOAD_RENDER)) //FT_LOAD_RENDER))
			{
				if(face->glyph->bitmap.pixel_mode == FT_PIXEL_MODE_GRAY)
				{
					chr.rect.pos.x = (int16_t) face->glyph->metrics.horiBearingX >> 6;
					chr.rect.pos.y = (int16_t) -(face->glyph->metrics.horiBearingY >> 6);//(face->size->metrics.ascender - face->glyph->metrics.horiBearingY) >> 6;
					chr.rect.size.x = (int16_t) face->glyph->bitmap.width;
					chr.rect.size.y = (int16_t) face->glyph->bitmap.rows;
					chr.horiAdvance = (uint16_t) face->glyph->advance.x >> 6;
					chr.data = new uint8_t[chr.rect.size.x * chr.rect.size.y];
					memcpy(chr.data, face->glyph->bitmap.buffer, (size_t)(chr.rect.size.x * chr.rect.size.y));
					it = chars.insert(std::pair<uint16_t, CocoFontChar>(ch, chr)).first;
				}
			}
		}

		// Kerning
		if(c && FT_HAS_KERNING(face))
		{
			std::map<uint16_t, int>::iterator kit = c->horiKernings.find(it->second.charIndex);
			if(kit == c->horiKernings.end())
			{
				FT_Vector tk;
				FT_Get_Kerning(face, c->charIndex, it->second.charIndex, FT_KERNING_DEFAULT, &tk);
				kit = c->horiKernings.insert(std::pair<uint16_t, int>(it->second.charIndex, tk.x)).first;
			}
			x += kit->second >> 6;
		}

		c = &(it->second);

		// Bitblt
		for(int32_t ix = c->rect.size.x; ix--;)
		{
			for(int32_t iy = c->rect.size.y; iy--;)
			{
				if( (x + c->rect.pos.x + ix) < width)
				{
					int32_t idx = (( y + c->rect.pos.y + iy) * width + (x + c->rect.pos.x + ix)) * 4;
					if(idx >= imageDataBuffer->byteLength) continue;
					uint8_t* cp = (uint8_t*)((*imageDataBuffer)[idx]);
					if(cp)// && c->data[iy * c->rect.size.x + ix])
					{
						cp[0] = BYTE_VALUE(255.0 * R);
						cp[1] = BYTE_VALUE(255.0 * G);
						cp[2] = BYTE_VALUE(255.0 * B);
						cp[3] = BYTE_VALUE(c->data[iy * c->rect.size.x + ix]);

					}
				}
			}
		}
		x += c->horiAdvance;

	}//loop
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
float CocoFont::measureText(String text)
{
	size_t ret = 0;
	if(FT_Set_Pixel_Sizes(face, 0, height))
	{
		trace("ERROR(CocoFont.cpp): Freetype could not set font char size");
	}
    else
    {
		std::map<uint16_t, CocoFontChar>::iterator it;
		CocoFontChar* c = nullptr;
		for(int i = 0; i < text.size(); i++)
		{
            uint16_t ch = text.charCodeAt(i);
			if((it = chars.find(ch)) == chars.end())
			{
				CocoFontChar c;
				c.charIndex = (uint16_t) FT_Get_Char_Index(face, (FT_ULong)(ch));
	            if(FT_Load_Glyph(face, c.charIndex, FT_LOAD_RENDER))
	            {
	            	trace("ERROR(CocoFont.cpp): Freetype could not load glyph");
	            }
	            else
	            {
	                if(face->glyph->bitmap.pixel_mode != FT_PIXEL_MODE_GRAY)
	                {
						trace("ERROR(CocoFont.cpp): Wrong FT_Pixel_Mode");
	                }
	                else
	                {
	                    c.rect.pos.x  = (int16_t) face->glyph->metrics.horiBearingX >> 6;
	                    c.rect.pos.y  = (int16_t) -(face->glyph->metrics.horiBearingY >> 6);//(face->size->metrics.ascender - face->glyph->metrics.horiBearingY) >> 6;
	                    c.rect.size.x = (int16_t) face->glyph->bitmap.width;
	                    c.rect.size.y = (int16_t) face->glyph->bitmap.rows;
	                    c.horiAdvance = (uint16_t) (face->glyph->advance.x >> 6);
	                    c.data = new uint8_t[c.rect.size.x * c.rect.size.y];
	                    memcpy(c.data, face->glyph->bitmap.buffer, (size_t)(c.rect.size.x * c.rect.size.y));
	                    it = chars.insert(std::pair<uint16_t, CocoFontChar>(ch, c)).first;
	                }
	            }
			}
			if(c && FT_HAS_KERNING(face))
			{
				std::map<uint16_t, int>::iterator kit = c->horiKernings.find(it->second.charIndex);
				if(kit == c->horiKernings.end())
				{
					FT_Vector tk;
	                FT_Get_Kerning(face, c->charIndex, it->second.charIndex, FT_KERNING_DEFAULT, &tk);
	                kit = c->horiKernings.insert(std::pair<uint16_t, int>(it->second.charIndex, tk.x)).first;
				}
				ret += (size_t)(kit->second >> 6);
			}
			c = &(it->second);
			ret += c->horiAdvance;
		}
    }
    return ret;
}
