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

@class CocoDeviceWrapper;

#import <UIKit/UIKit.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <libgen.h>

#import "Coconut2D.hpp"
#import "Fonts/CocoFontsCache.h"
#import "Audio/CocoAudioStream.h"
#import "CocoDeviceWrapper.h"

char* CocoAssetFile::filesPath;
char* CocoAssetFile::assetPath;

#define CONFIGURATION_DEBUG

////////////////////////////////////////////////////////////////////////////////////////////////////
int main(int argc, char *argv[])
{
	int ret = -1;
	std::setlocale(LC_ALL, "en_US.UTF-8");

	// Get application documents folder
	std::string documentsDir([[NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES) objectAtIndex:0] fileSystemRepresentation]);
	documentsDir += "/";

	// Get bundle folder
	std::string bundleDir([[[NSBundle mainBundle] resourcePath] fileSystemRepresentation]);
	bundleDir += "/assets/";

	// Initialize
	curl_global_init(CURL_GLOBAL_ALL);
	CocoAssetFile::init(documentsDir.c_str(), bundleDir.c_str());

	// Initialize Fonts
	CocoFontsCache::init();
	$(FONTS_LIST)

	// Initialize Audio
	CocoAudioStream::init();

	// Initialize HTTP
	#ifdef __XMLHTTPREQUEST_HPP__
	XMLHttpRequest::init();
	#endif

    // Start the application
	@autoreleasepool { ret = UIApplicationMain(argc, argv, nil, NSStringFromClass([CocoDeviceWrapper class])); }

	// Dispose resources

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

	curl_global_cleanup();

	// Done!
	return ret;
}
