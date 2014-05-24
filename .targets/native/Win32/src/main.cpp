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

#include "AssetFile.h"
#include "fxFontFace.h"
#include "fxAudioStream.h"
#include "fxDeviceWrapper.h"

//////////////////////////////////////////////////////////////////////////////////////////////
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	int width = 800;
	int height = 600;

	curl_global_init(CURL_GLOBAL_ALL);
	AssetFile::init("./assets/", (std::string(getenv("USERPROFILE")) + "/Coconut2D/").c_str());
	fxFontFace::init();
	fxAudioStream::init();

	#ifdef __XMLHTTPREQUEST_HPP__
	XMLHttpRequest::init();
	#endif

	fxDeviceWrapper w(width, height);

	#ifdef __XMLHTTPREQUEST_HPP__
	XMLHttpRequest::quit();
	#endif

	fxAudioStream::quit();
	fxFontFace::quit();
	AssetFile::quit();
	curl_global_cleanup();

	return 0;
}