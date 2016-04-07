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
//	   ______                 ______            __       ______           __
//	  / ____/___  _________  / ____/___  ____  / /______/ ____/___ ______/ /_  ___
//	 / /   / __ \/ ___/ __ \/ /_  / __ \/ __ \/ __/ ___/ /   / __ `/ ___/ __ \/ _ \
//	/ /___/ /_/ / /__/ /_/ / __/ / /_/ / / / / /_(__  ) /___/ /_/ / /__/ / / /  __/
//	\____/\____/\___/\____/_/    \____/_/ /_/\__/____/\____/\__,_/\___/_/ /_/\___/
//
// ==================================================================================================================================

#ifndef __COCOFONTSMANAGER_HPP__
#define __COCOFONTSMANAGER_HPP__

/////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "Coconut2D.hpp"

/////////////////////////////////////////////////////////////////////////////////////////////////////////

class CocoFontsCache
{
public:

	enum FONT_STYLE
	{
		None,
		Regular,
		Italic,
		Bold,
		BoldItalic
	};

private:
    static FT_Library ftLibrary;
    static std::map<CocoFontsCache, FT_Face> fonts;

protected:
	std::string name;
	FONT_STYLE style;

public:
	bool operator<(const CocoFontsCache& b) const;
    static void add(std::string name, FONT_STYLE style, const char* filename);
    static FT_Face get(std::string name, FONT_STYLE style);
    static void init();
    static void quit();

	CocoFontsCache(std::string i_name, FONT_STYLE i_style);
	CocoFontsCache();
};

#endif // __COCOFONTSMANAGER_HPP__


