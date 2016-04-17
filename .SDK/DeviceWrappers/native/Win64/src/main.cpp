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

#define _WIN32_WINNT  0x501

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "Coconut2D.hpp"
#include "CocoAssetFile.h"
#include "Fonts/CocoFontsCache.h"
#include "Audio/CocoAudioStream.h"
#include "CocoDeviceWrapper.h"

#define CONFIGURATION_$(UCONFIGURATION)
#define DEBUG_HOST_IP "$(DEBUG_HOST_IP)"
#define DEBUG_HOST_PORT $(DEBUG_HOST_PORT)

//////////////////////////////////////////////////////////////////////////////////////////////
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	std::setlocale(LC_ALL, "en_US.UTF-8");

	// Preferred width and height
	int width = $(SURFACE_WIDTH);
	int height = $(SURFACE_HEIGHT);

	// Set folder of assets and resources (for Android compatibility)
	CocoAssetFile::init("./assets/", (std::string(getenv("USERPROFILE")) + "/Coconut2D/").c_str());

	// Initialize Fonts
	CocoFontsCache::init();
	$(FONTS_LIST)

	// Initialize Audio
	CocoAudioStream::init();

	// Initialize HTTP
	#ifdef __XMLHTTPREQUEST_HPP__
	XMLHttpRequest::init();
	#endif

	// Create Device Wrapper
	CocoDeviceWrapper app(width, height);

	// Quit HTTP
	#ifdef __XMLHTTPREQUEST_HPP__
	XMLHttpRequest::quit();
	#endif

	// Quit Audio
	CocoAudioStream::quit();

	// Quit Fonts
	CocoFontsCache::quit();

	// Quit Assets
	CocoAssetFile::quit();

	return 0;
}