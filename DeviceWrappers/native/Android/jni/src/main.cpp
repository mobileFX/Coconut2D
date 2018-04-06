/* ***** BEGIN LICENSE BLOCK *****
 *
 * Copyright (C) 2013-2017 www.mobilefx.com
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

#include "Audio/CocoAudioSystem.h"
#include "CocoDeviceWrapper.h"

#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <fstream>
#include <sstream>
#include <libgen.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

#define CONFIGURATION_$(UCONFIGURATION)
#define DEBUG_HOST_IP "$(DEBUG_HOST_IP)"
#define DEBUG_HOST_PORT $(DEBUG_HOST_PORT)

void android_main(android_app* app)
{
	app_dummy();

	std::setlocale(LC_ALL, "en_US.UTF-8");

	CocoAssetFile::init(app->activity->assetManager, "/data/data/com.mobilefx.cocoengine/files/");

	/*
	$(FONTS_LIST)
	*/

	CocoAudioSystem::init();

	#ifdef __XMLHTTPREQUEST_HPP__
	curl_global_init(CURL_GLOBAL_ALL);
	XMLHttpRequest::init();
	#endif

	CocoDeviceWrapper w(app);

	#ifdef __XMLHTTPREQUEST_HPP__
	XMLHttpRequest::quit();
	curl_global_cleanup();
	#endif

	CocoAudioSystem::quit();

	CocoAssetFile::quit();
}
