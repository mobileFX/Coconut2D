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

@class fxDeviceWrapper;

#import <UIKit/UIKit.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <libgen.h>

#import "Coconut2D.hpp"
#import "AssetFile.h"
#import "fxFontFace.h"
#import "fxAudioStream.h"
#import "fxDeviceWrapper.h"

extern char* AssetFile::filesPath;
extern char* AssetFile::assetPath;
CocoEngine* engine;

//#define DEBUG_LOG_TO_REMOTE_CONSOLE "$(LOCALHOST_IP)"

////////////////////////////////////////////////////////////////////////////////////////////////////
int main(int argc, char *argv[])
{
	int ret = -1;

	// Redirect the standard error stream to a remote console
	#if defined DEBUG_LOG_TO_REMOTE_CONSOLE
	{
		struct sockaddr_in debugserver_sockaddr = { AF_INET, 0, 0x8813, { 0 }, { 0 } };
		debugserver_sockaddr.sin_addr.s_addr = inet_addr(DEBUG_LOG_TO_REMOTE_CONSOLE);
		int debug_socket = socket (AF_INET, SOCK_STREAM, IPPROTO_TCP);
		if((debug_socket!=-1) && (connect(debug_socket, (struct sockaddr *) &debugserver_sockaddr, sizeof (debugserver_sockaddr))!=-1))
			dup2(debug_socket, STDERR_FILENO);
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
	AssetFile::init(documentsDir.c_str(), bundleDir.c_str());
	fxFontFace::init();
	fxAudioStream::init();

    // Start the application
	@autoreleasepool { ret = UIApplicationMain(argc, argv, nil, NSStringFromClass([fxDeviceWrapper class])); }

	// Dispose resources
	fxAudioStream::quit();
	fxFontFace::quit();
	AssetFile::quit();

	// Done!
	return ret;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void trace(const char* fmt, ...)
{
	char* buff = (char*) malloc(2048);
	va_list vl;
	va_start(vl, fmt);
	vsprintf(buff, fmt, vl);
	va_end(vl);
	NSLog(@"%s\n",buff);
	free(buff);
}

