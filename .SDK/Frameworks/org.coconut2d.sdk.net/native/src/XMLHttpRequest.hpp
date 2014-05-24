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

// ==================================================================================================================================
//	   _  __ __  _____    __  ____  __        ____                             __
//	  | |/ //  |/  / /   / / / / /_/ /_____  / __ \___  ____ ___  _____  _____/ /_
//	  |   // /|_/ / /   / /_/ / __/ __/ __ \/ /_/ / _ \/ __ `/ / / / _ \/ ___/ __/
//	 /   |/ /  / / /___/ __  / /_/ /_/ /_/ / _, _/  __/ /_/ / /_/ /  __(__  ) /_
//	/_/|_/_/  /_/_____/_/ /_/\__/\__/ .___/_/ |_|\___/\__, /\__,_/\___/____/\__/
//	                               /_/                  /_/
// ==================================================================================================================================

#ifndef __XMLHTTPREQUEST_HPP__
#define __XMLHTTPREQUEST_HPP__

////////////////////////////////////////////////////////////////////////////////////////////////////

#include "Coconut2D.hpp"

#undef OPENED

////////////////////////////////////////////////////////////////////////////////////////////////////
enum XMLHttpRequestResponseType
{
	TypeNone,
	TypeArrayBuffer,
	TypeBlob,
	TypeDocument,
	TypeJSON,
	TypeText
};

////////////////////////////////////////////////////////////////////////////////////////////////////
class XMLHttpRequest
{
public:
	static CURLM* curlm;
	static void init();
	static void tick();
	static void quit();

	XMLHttpRequest();
	~XMLHttpRequest();

	String requestMethod;
	String requestURL;
	std::map<String, String> requestHeaders;
	std::map<String, String> responseHeaders;
	bool synchronous;
	static size_t writeHeader(void* contents, size_t size, size_t nmemb, void* ptr);
	static size_t writeData(void* contents, size_t size, size_t nmemb, void* ptr);
	std::vector<char> header;
	bool freeData;
	CocoAssetFile* data;
	void complete();

	const unsigned short UNSENT = 0;
	const unsigned short OPENED = 1;
	const unsigned short HEADERS_RECEIVED = 2;
	const unsigned short LOADING = 3;
	const unsigned short DONE = 4;
	unsigned short readyState;

	void open(String method, String url, bool async = true);
	void setRequestHeader(String header, String value);
	void send();
	void send(String data);
	void send(ArrayBufferView* data);
	void abort();

	unsigned short status;
	String statusText;
	String getResponseHeader(String header);
	String getAllResponseHeaders();
	XMLHttpRequestResponseType responseType;
	String responseText;
};

#endif /* __XMLHTTPREQUEST_HPP__ */