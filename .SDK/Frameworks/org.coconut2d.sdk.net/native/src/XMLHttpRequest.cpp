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

////////////////////////////////////////////////////////////////////////////////////////////////////

#include "XMLHttpRequest.hpp"
#include "CocoAssetFile.h"

////////////////////////////////////////////////////////////////////////////////////////////////////

CURLM* XMLHttpRequest::curlm = nullptr;

////////////////////////////////////////////////////////////////////////////////////////////////////
void XMLHttpRequest::init()
{
	curlm = curl_multi_init();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void XMLHttpRequest::tick()
{
	int count = 0;
	while(curl_multi_perform(curlm, &count) == CURLM_CALL_MULTI_PERFORM);
	do
	{
		CURLMsg* cmsg = curl_multi_info_read(curlm, &count);
		if(cmsg && cmsg->msg == CURLMSG_DONE)
		{
			XMLHttpRequest* t = nullptr;
			curl_easy_getinfo(cmsg->easy_handle, CURLINFO_PRIVATE, reinterpret_cast<char**>(&t));
			switch(cmsg->data.result)
			{
				case CURLE_OK: t->complete(); break;
				default: trace("ERROR(XMLHttpRequest.cpp): CURL returned %d", cmsg->data.result);
			}
			curl_easy_cleanup(cmsg->easy_handle);
		}
	}
	while(count);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void XMLHttpRequest::quit()
{
	if(curlm) curlm = (curl_multi_cleanup(curlm), nullptr);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
XMLHttpRequest::XMLHttpRequest()
{
	readyState = UNSENT;
	freeData = true;
	data = new CocoAssetFile(0);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
XMLHttpRequest::~XMLHttpRequest()
{
	if(freeData) delete data;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void XMLHttpRequest::open(String method, String url, bool async)
{
	if(!strcasecmp(method.c_str(), "CONNECT")) requestMethod = "CONNECT";
	else if(!strcasecmp(method.c_str(), "DELETE")) requestMethod = "DELETE";
	else if(!strcasecmp(method.c_str(), "GET")) requestMethod = "GET";
	else if(!strcasecmp(method.c_str(), "HEAD")) requestMethod = "HEAD";
	else if(!strcasecmp(method.c_str(), "OPTIONS")) requestMethod = "OPTIONS";
	else if(!strcasecmp(method.c_str(), "POST")) requestMethod = "POST";
	else if(!strcasecmp(method.c_str(), "PUT")) requestMethod = "PUT";
	else if(!strcasecmp(method.c_str(), "TRACE")) requestMethod = "TRACE";
	else if(!strcasecmp(method.c_str(), "TRACK")) requestMethod = "TRACK";
	else requestMethod = method;
	if(requestMethod == "CONNECT" || requestMethod == "TRACE" || requestMethod == "TRACK")
		trace("ERROR(XMLHttpRequest.cpp): SecurityError");
	requestURL = url;
	responseText = "";
	statusText = "";
	synchronous = !async;
	requestHeaders.clear();
	readyState = OPENED;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void XMLHttpRequest::setRequestHeader(String header, String value)
{
	if(readyState != OPENED)
		trace("ERROR(XMLHttpRequest.cpp): InvalidStateError");

	if(!strcasecmp(header.c_str(), "Accept-Charset")
	|| !strcasecmp(header.c_str(), "Accept-Encoding")
	|| !strcasecmp(header.c_str(), "Access-Control-Requesr-Headers")
	|| !strcasecmp(header.c_str(), "Access-Control-Request-Method")
	|| !strcasecmp(header.c_str(), "Connection")
	|| !strcasecmp(header.c_str(), "Content-Length")
	|| !strcasecmp(header.c_str(), "Cookie")
	|| !strcasecmp(header.c_str(), "Cookie2")
	|| !strcasecmp(header.c_str(), "Date")
	|| !strcasecmp(header.c_str(), "DNT")
	|| !strcasecmp(header.c_str(), "Expect")
	|| !strcasecmp(header.c_str(), "Host")
	|| !strcasecmp(header.c_str(), "Keep-Alive")
	|| !strcasecmp(header.c_str(), "Origin")
	|| !strcasecmp(header.c_str(), "Referer")
	|| !strcasecmp(header.c_str(), "TE")
	|| !strcasecmp(header.c_str(), "Trailer")
	|| !strcasecmp(header.c_str(), "Transfer-Encoding")
	|| !strcasecmp(header.c_str(), "Upgrade")
	|| !strcasecmp(header.c_str(), "User-Agent")
	|| !strcasecmp(header.c_str(), "Via")
	|| !strncasecmp(header.c_str(), "Proxy-", 6)
	|| !strncasecmp(header.c_str(), "Sec-", 4)) return;

	std::map<String, String>::iterator it = requestHeaders.find(header);
	if(it == requestHeaders.end())
		requestHeaders.insert(std::pair<String, String>(header, value));
	else
		it->second += ", " + value;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
size_t XMLHttpRequest::writeHeader(void* contents, size_t size, size_t nmemb, void* ptr)
{
	std::vector<char>* v = static_cast<std::vector<char>*>(ptr);
	size_t s = size * nmemb;
	size_t ps = v->empty() ? 0 : v->size() - 1;
	v->resize(ps + s + 1);
	memcpy(v->data() + ps, contents, s);
	*(v->data() + ps + s) = 0;
	return s;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
size_t XMLHttpRequest::writeData(void* contents, size_t size, size_t nmemb, void* ptr)
{
	CocoAssetFile* v = static_cast<CocoAssetFile*>(ptr);
	return v->append(contents, size * nmemb);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void XMLHttpRequest::complete()
{
	readyState = DONE;
	Array<String>* splHeader = String(std::string(header.begin(), header.end())).split("\n");
	Array<String>* splStatus = (*splHeader)[0].split(" ");
	status = parseInt((*splStatus)[1]);
	statusText = (*splStatus)[2];
	for(size_t i = splHeader->size(); --i;)
	{
		if((*splHeader)[i] != "")
		{
			size_t pos = (*splHeader)[i].indexOf(":");
			if(pos != std::string::npos)
			{
				String key = (*splHeader)[i].substr(0, pos);
				String val = (*splHeader)[i].substr((*splHeader)[i].find_first_not_of(" ", pos + 1));
				std::map<String, String>::iterator it = responseHeaders.find(key);
				if(it != responseHeaders.end())
					it->second += ", " + val;
				else
					responseHeaders.insert(std::pair<String, String>(key, val));
			}
		}
	}
	delete splHeader;
	delete splStatus;
	data->setMime(getResponseHeader("Content-Type").c_str());
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void XMLHttpRequest::send()
{
	if(readyState != OPENED)
		trace("ERROR(XMLHttpRequest.cpp): InvalidStateError");

	CURL* curl = curl_easy_init();
	curl_easy_setopt(curl, CURLOPT_PRIVATE, static_cast<void*>(this));
	if(requestMethod == "GET") curl_easy_setopt(curl, CURLOPT_HTTPGET, 1);
	else if(requestMethod == "POST") curl_easy_setopt(curl, CURLOPT_HTTPPOST, 1);
	else trace("ERROR(XMLHttpRequest.cpp): Method not yet supported. Using the default (GET)");
	curl_slist* httpheader = nullptr;
	for(std::map<String, String>::iterator it = requestHeaders.begin(); it != requestHeaders.end(); it++)
		httpheader = curl_slist_append(httpheader, (it->first + ": " + it->second).c_str());
	curl_easy_setopt(curl, CURLOPT_HTTPHEADER, httpheader);
	curl_easy_setopt(curl, CURLOPT_NOSIGNAL, 1);
	curl_easy_setopt(curl, CURLOPT_URL, requestURL.c_str());
	curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1);
	curl_easy_setopt(curl, CURLOPT_USERAGENT, APPNAME);
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeData);
	curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION, writeHeader);
	curl_easy_setopt(curl, CURLOPT_WRITEHEADER, static_cast<void*>(&header));
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, static_cast<void*>(&data));
	if(synchronous)
	{
		curl_easy_perform(curl);
		complete();
		curl_easy_cleanup(curl);
	}
	else
	{
		curl_multi_add_handle(curlm, curl);
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void XMLHttpRequest::send(String data)
{
	TODO();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void XMLHttpRequest::send(ArrayBufferView* data)
{
	TODO();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void XMLHttpRequest::abort()
{
	TODO();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
String XMLHttpRequest::getResponseHeader(String header)
{
	if(readyState == UNSENT || readyState == OPENED) return "";
	std::map<String, String>::iterator it = responseHeaders.find(header);
	if(it != responseHeaders.end())
		return it->second;
	return "";
}

////////////////////////////////////////////////////////////////////////////////////////////////////
String XMLHttpRequest::getAllResponseHeaders()
{
	String ret = "";
	if(readyState == UNSENT || readyState == OPENED) return ret;
	for(std::map<String, String>::iterator it = responseHeaders.begin(); it != responseHeaders.end(); it++)
		ret += it->first + ": " + it->second;
	return ret;
}