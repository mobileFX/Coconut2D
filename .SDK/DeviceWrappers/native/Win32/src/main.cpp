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

#include "CocoAssetFile.h"
#include "CocoFontsCache.h"
#include "CocoAudioStream.h"
#include "CocoDeviceWrapper.h"

//////////////////////////////////////////////////////////////////////////////////////////////
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	int width = $(SURFACE_WIDTH);
	int height = $(SURFACE_HEIGHT);

	CocoAssetFile::init("./assets/", (std::string(getenv("USERPROFILE")) + "/Coconut2D/").c_str());

	CocoFontsCache::init();
	CocoFontsCache::add("Helvetica", CocoFontsCache::FONT_STYLE::Regular, "./fonts/Helvetica.ttf");
	CocoFontsCache::add("Helvetica", CocoFontsCache::FONT_STYLE::Bold, "./fonts/Helvetica-Bold.ttf");
	CocoFontsCache::add("Helvetica", CocoFontsCache::FONT_STYLE::Italic, "./fonts/Helvetica-Italic.ttf");
	CocoFontsCache::add("Helvetica", CocoFontsCache::FONT_STYLE::BoldItalic, "./fonts/Helvetica-BoldItalic.ttf");
	CocoFontsCache::add("HelveticaNeue", CocoFontsCache::FONT_STYLE::Regular, "./fonts/HelveticaNeue.ttf");
	CocoFontsCache::add("HelveticaNeue", CocoFontsCache::FONT_STYLE::Bold, "./fonts/HelveticaNeue-Bold.ttf");
	CocoFontsCache::add("HelveticaNeue", CocoFontsCache::FONT_STYLE::Italic, "./fonts/HelveticaNeue-Italic.ttf");
	CocoFontsCache::add("HelveticaNeue", CocoFontsCache::FONT_STYLE::BoldItalic, "./fonts/HelveticaNeue-BoldItalic.ttf");
	CocoFontsCache::add("Arial", CocoFontsCache::FONT_STYLE::Regular, "./fonts/Arial.ttf");
	CocoFontsCache::add("Arial", CocoFontsCache::FONT_STYLE::Bold, "./fonts/Arial-Bold.ttf");
	CocoFontsCache::add("Arial", CocoFontsCache::FONT_STYLE::Italic, "./fonts/Arial-Italic.ttf");
	CocoFontsCache::add("Arial", CocoFontsCache::FONT_STYLE::BoldItalic, "./fonts/Arial-BoldItalic.ttf");
	CocoFontsCache::add("Consolas", CocoFontsCache::FONT_STYLE::Regular, "./fonts/Consolas.ttf");
	CocoFontsCache::add("Consolas", CocoFontsCache::FONT_STYLE::Bold, "./fonts/Consolas-Bold.ttf");
	CocoFontsCache::add("Consolas", CocoFontsCache::FONT_STYLE::Italic, "./fonts/Consolas-Italic.ttf");
	CocoFontsCache::add("Consolas", CocoFontsCache::FONT_STYLE::BoldItalic, "./fonts/Consolas-BoldItalic.ttf");
	CocoAudioStream::init();

	curl_global_init(CURL_GLOBAL_ALL);

	#ifdef __XMLHTTPREQUEST_HPP__
	XMLHttpRequest::init();
	#endif

	CocoDeviceWrapper w(width, height);

	#ifdef __XMLHTTPREQUEST_HPP__
	XMLHttpRequest::quit();
	#endif

	CocoAudioStream::quit();
	CocoFontsCache::quit();
	CocoAssetFile::quit();
	curl_global_cleanup();

	return 0;
}