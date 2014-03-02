//
//  CocoFont.cpp
//  CocoEngine
//
//  Created by Administrator on 1/24/14.
//
//

#include "CocoFont.hpp"

#ifdef ENABLE_FREETYPE_SUPPORT
/////////////////////////////////////////////////////////////////////////////////////////////////////////
CocoFont::CocoFont(float fontSize, String fontName, fxFontFace::FONT_STYLE style, String fontChars) : height(fontSize)
{
	const FT_Face face = fxFontFace::get(fontName, style);
	if(face)
	{
        //if(FT_Set_Char_Size(face, 0, height << 6, 0, 0)) { LOGW("Error Freetype: Could not set font char size\n"); }
        if(FT_Set_Pixel_Sizes(face, 0, height)) { LOGW("Error Freetype: Could not set font char size\n"); }
        else
        {
            FT_UInt char_index[fontChars.size()];
            for(size_t i = fontChars.size(); i--;) char_index[i] = FT_Get_Char_Index(face, (FT_ULong)(fontChars[i]));
            for(size_t l = fontChars.size(); l--;)
            {
                if(FT_Load_Glyph(face, char_index[l], FT_LOAD_RENDER)) { LOGW("Error FreeType: Could not load glyph\n"); }
                else
                {
                    if(face->glyph->bitmap.pixel_mode != FT_PIXEL_MODE_GRAY) { LOGW("Wrong FT_Pixel_Mode!\n"); }
                    else
                    {
                        CocoFontChar c;
                        c.i = l;
                        c.rect.pos.x = face->glyph->metrics.horiBearingX >> 6;
                        c.rect.pos.y = (face->size->metrics.ascender - face->glyph->metrics.horiBearingY) >> 6;
                        c.rect.size.x = face->glyph->bitmap.width;
                        c.rect.size.y = face->glyph->bitmap.rows;
                        c.horiAdvance = face->glyph->advance.x >> 6;
                        if(c.horiAdvance > maxHoriAdvance) maxHoriAdvance = c.horiAdvance;
                        c.data = new unsigned char[c.rect.size.x * c.rect.size.y];
                        memcpy(c.data, face->glyph->bitmap.buffer, c.rect.size.x * c.rect.size.y);
                        if(FT_HAS_KERNING(face)) c.horiKernings = nullptr;
                        else
                        {
                            c.horiKernings = new int[fontChars.size()];
                            FT_Vector tk;
                            for(size_t r = fontChars.size(); r--;)
                            {
                                FT_Get_Kerning(face, char_index[l], char_index[r], FT_KERNING_DEFAULT, &tk);
                                c.horiKernings[r] = tk.x;
                            }
                        }
                        chars.insert(std::pair<uint16_t, CocoFontChar>(fontChars[l], c));
                    }
                }
            }
        }
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
void CocoFont::fillText(ArrayBuffer* imageDataBuffer, int width, String text, float x, float y)
{   // We only use the ArrayBuffer of an Int32Array with byteOffset = 0 (BYTES_PER_ELEMENT = 4) in RGBA format
	std::map<uint16_t, CocoFontChar>::iterator it;
	CocoFontChar* c = nullptr;
	for(size_t i = 0; i < text.size(); i++)
	{
		if((it = chars.find(text[i])) == chars.end()) return;
		if(c && c->horiKernings) x += c->horiKernings[it->second.i];
		c = &(it->second);
		for(size_t ix = c->rect.size.x; ix--;)
			for(size_t iy = c->rect.size.y; iy--;)
			{
				unsigned char* cp = (unsigned char*)((*imageDataBuffer)[((y + c->rect.pos.y + iy) * width + (x + c->rect.pos.x + ix)) * 4]);
				if(cp && c->data[iy * c->rect.size.x + ix])
				{
					cp[0] = 0xFF;
					cp[1] = 0xFF;
					cp[2] = 0xFF;
					cp[3] |= c->data[iy * c->rect.size.x + ix];
				}
			}
		x += c->horiAdvance;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
float CocoFont::measureText(String text)
{
	size_t ret = 0;
	std::map<uint16_t, CocoFontChar>::iterator it;
	CocoFontChar* c = nullptr;
	for(size_t i = 0; i < text.size(); i++)
	{
		if((it = chars.find(text[i])) == chars.end()) return ret;
		if(c && c->horiKernings) ret += c->horiKernings[it->second.i];
		c = &(it->second);
		ret += c->horiAdvance;
	}
	return ret;
}

#else
/////////////////////////////////////////////////////////////////////////////////////////////////////////
CocoFont::CocoFont(float fontSize, String fontName, String fontChars)
{
	LOGW("Fonts not supported!\n");
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////
void CocoFont::fillText(ArrayBuffer* imageDataBuffer, int width, String text, float x, float y)
{
	LOGW("Fonts not supported!\n");
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////
float CocoFont::measureText(String text)
{
	LOGW("Fonts not supported!\n");
	return 0.0f;
}
#endif
