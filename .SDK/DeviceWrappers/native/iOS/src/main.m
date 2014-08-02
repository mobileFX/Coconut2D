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

@class CocoDeviceWrapper;

#import <UIKit/UIKit.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <libgen.h>

#import "Coconut2D.hpp"
#import "CocoAssetFile.h"
#import "Fonts/CocoFontsCache.h"
#import "Audio/CocoAudioStream.h"
#import "CocoDeviceWrapper.h"

char* CocoAssetFile::filesPath;
char* CocoAssetFile::assetPath;

#define CONFIGURATION_$(UCONFIGURATION)
#define DEBUG_HOST_IP 	"$(DEBUG_HOST_IP)"
#define DEBUG_HOST_PORT $(DEBUG_HOST_PORT)

////////////////////////////////////////////////////////////////////////////////////////////////////
int main(int argc, char *argv[])
{
	int ret = -1;

	// Redirect the standard error stream to a remote console
	#if defined CONFIGURATION_DEBUG
	{
		trace("Connecting to iOS Debug Server: %s", DEBUG_HOST_IP);
		struct sockaddr_in debugserver_sockaddr = { AF_INET, 0, htons(DEBUG_HOST_PORT), { 0 }, { 0 } };
		debugserver_sockaddr.sin_addr.s_addr = inet_addr(DEBUG_HOST_IP);
		int debug_socket = socket (AF_INET, SOCK_STREAM, IPPROTO_TCP);
		trace("Socket Handle: %d",debug_socket);
		if((debug_socket!=-1) && (connect(debug_socket, (struct sockaddr *) &debugserver_sockaddr, sizeof (debugserver_sockaddr))!=-1))
		{
			dup2(debug_socket, STDERR_FILENO);
			trace("Connected%s\n", "");
		}
		else
		{
			trace("Failed to connect%s\n", "");
		}
	}
	#endif

	// Get application documents folder
	std::string documentsDir([[NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES) objectAtIndex:0] fileSystemRepresentation]);
	documentsDir += "/";
	trace("Application Documents Folder: %s", documentsDir.c_str());

	// Get bundle folder
	std::string bundleDir([[[NSBundle mainBundle] resourcePath] fileSystemRepresentation]);
	bundleDir += "/assets/";
	trace("Application Bundle Folder: %s", bundleDir.c_str());

	// Initialize
	curl_global_init(CURL_GLOBAL_ALL);
	CocoAssetFile::init(documentsDir.c_str(), bundleDir.c_str());

	CocoFontsCache::init();
	$(IOS_FONTS_LIST)
	CocoAudioStream::init();

	#ifdef __XMLHTTPREQUEST_HPP__
	XMLHttpRequest::init();
	#endif

    // Start the application
	@autoreleasepool { ret = UIApplicationMain(argc, argv, nil, NSStringFromClass([CocoDeviceWrapper class])); }

	// Dispose resources

	#ifdef __XMLHTTPREQUEST_HPP__
	XMLHttpRequest::quit();
	#endif

	CocoAudioStream::quit();
	CocoFontsCache::quit();
	CocoAssetFile::quit();

	curl_global_cleanup();

	// Done!
	return ret;
}
