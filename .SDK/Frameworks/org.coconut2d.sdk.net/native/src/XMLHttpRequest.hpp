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
class XMLHttpRequest
{
public:

	//////////////////////////////////////////////////////////////////////////////////////////////
	// Curl Related Members

	static CURLM* curlm;
	static void init();
	static void tick();
	static void quit();
	static size_t curl_callback(void* contents, size_t size, size_t nmemb, void* ptr);
	static void curl_multiperform();

	CURL* curl;
	std::map<String, String> requestHeaders;
	std::map<String, String> responseHeaders;
	std::vector<char> responseHeadersBuffer;
	std::vector<char> responseDataBuffer;
	std::vector<char> requestDataBuffer;
	void curl_send();
	void curl_complete();

	//////////////////////////////////////////////////////////////////////////////////////////////
	// XMLHttpRequest members

	static const UINT UNSENT			= 0;
	static const UINT OPENED			= 1;
	static const UINT HEADERS_RECEIVED	= 2;
	static const UINT LOADING			= 3;
	static const UINT DONE				= 4;

	bool async;
	bool dataAvailable;
	unsigned short readyState;
	unsigned short status;
	String statusText;
	String responseText;
	String responseType;
	String responseURL;
	ArrayBuffer* response;

	XMLHttpRequest();
	~XMLHttpRequest();

	void open(String method, String url, bool async=true);
	void setRequestHeader(String header, String value);
	void send();
	void send(String data);
	void send(ArrayBufferView* data);
	void send(ArrayBuffer* data);
	void abort();
	String getResponseHeader(String header);
	String getAllResponseHeaders();

	//////////////////////////////////////////////////////////////////////////////////////////////
	// JavaScript to C++ bindings
	String __get_responseType() 		{ return responseType; }
	void __set_responseType(String v) 	{ responseType = v; }
	int __get_timeout() 				{ return 0; }
	void __set_timeout(int v) 			{}
	int __get_readyState() 				{ return readyState; }
	void __set_readyState(int v) 		{}
	int __get_status() 					{ return status; }
	void __set_status(int v) 			{}
	String __get_statusText() 			{ return statusText; }
	void __set_statusText(String v) 	{}
	String __get_responseText() 		{ return responseText; }
	void __set_responseText(String v) 	{}
	void __set_response(ArrayBuffer* v) {}
	ArrayBuffer* __get_response() 		{ return nullptr; }

};

#endif /* __XMLHTTPREQUEST_HPP__ */