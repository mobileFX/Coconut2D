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

// ==================================================================================================================================
//	   _  __ __  _____    __  ____  __        ____                             __
//	  | |/ //  |/  / /   / / / / /_/ /_____  / __ \___  ____ ___  _____  _____/ /_
//	  |   // /|_/ / /   / /_/ / __/ __/ __ \/ /_/ / _ \/ __ `/ / / / _ \/ ___/ __/
//	 /   |/ /  / / /___/ __  / /_/ /_/ /_/ / _, _/  __/ /_/ / /_/ /  __(__  ) /_
//	/_/|_/_/  /_/_____/_/ /_/\__/\__/ .___/_/ |_|\___/\__, /\__,_/\___/____/\__/
//	                               /_/                  /_/
// ==================================================================================================================================

#include "XMLHttpRequest.hpp"

CURLM* XMLHttpRequest::curlm = nullptr;

////////////////////////////////////////////////////////////////////////////////////////////////////
void XMLHttpRequest::init()
{
	curl_global_init(CURL_GLOBAL_ALL);
	curlm = curl_multi_init();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void XMLHttpRequest::quit()
{
	if(curlm)
		curlm = (curl_multi_cleanup(curlm), nullptr);
	curl_global_cleanup();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void XMLHttpRequest::tick()
{
	curl_multiperform();
}

// ==================================================================================================================================
//	    ____           __
//	   /  _/___  _____/ /_____ _____  ________
//	   / // __ \/ ___/ __/ __ `/ __ \/ ___/ _ \
//	 _/ // / / (__  ) /_/ /_/ / / / / /__/  __/
//	/___/_/ /_/____/\__/\__,_/_/ /_/\___/\___/
//
// ==================================================================================================================================

//////////////////////////////////////////////////////////////////////////////////////////////
XMLHttpRequest::XMLHttpRequest()
{
	curl = NULL;
	readyState = UNSENT;
	dataAvailable = false;
	status = UNSENT;
	response = nullptr;
}

//////////////////////////////////////////////////////////////////////////////////////////////
XMLHttpRequest::~XMLHttpRequest()
{
	delete response;

	if(curl)
	{
		curl_easy_cleanup(curl);
		curl = NULL;
		requestHeaders.clear();
		responseHeaders.clear();
		responseHeadersBuffer.clear();
		responseDataBuffer.clear();
		requestDataBuffer.clear();
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////
void XMLHttpRequest::open(String method, String url, bool async)
{
	status = UNSENT;
	statusText = "";
	responseType = "";
	responseText = "";
	response = nullptr;
	dataAvailable = false;
	this->async = async;

	if(url.at(0)=='.')
	{
		/*
		// Hack for reading local files
		AssetFile* file = AssetFile::open(url.c_str());
		if(file)
		{
			response = ArrayBuffer::NewFromBytes(file);
			if(response->IsObject())
			{
				// Persist the ArrayBuffer
				v8::Persistent<v8::Object>::New(response->ToObject());

				// Set response flags
				status = 200;
				statusText = "OK";
				dataAvailable=true;
				responseType = "arraybuffer";
				responseURL = std::string("file:///") + std::string(file->file);
				readyState=DONE;

				delete file;
			}
		}
		*/
	}
	else
	{
		// Start a libcurl easy session
		curl = curl_easy_init();

		// Store "this" as a private pointer to curl
		curl_easy_setopt(curl, CURLOPT_PRIVATE, static_cast<void*>(this));

		// Set http method
		std::transform(method.begin(), method.end(), method.begin(), ::toupper);
		if(method=="GET") curl_easy_setopt(curl, CURLOPT_HTTPGET, 1);
		else if(method=="POST") curl_easy_setopt(curl, CURLOPT_HTTPPOST, 1);

		// Set url
		curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

		// skip all signal handling
		curl_easy_setopt(curl, CURLOPT_NOSIGNAL, 1);

		// follow HTTP 3xx redirects
		curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1);

		// set user agent
		curl_easy_setopt(curl, CURLOPT_USERAGENT, APPNAME);

		// set callback for writing received data
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, curl_callback);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, static_cast<void*>(&responseDataBuffer));

		//  set callback for writing received header data
		curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION, curl_callback);
		curl_easy_setopt(curl, CURLOPT_WRITEHEADER, static_cast<void*>(&responseHeadersBuffer));

		responseURL = url;
		readyState = OPENED;
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////
void XMLHttpRequest::setRequestHeader(String header, String value)
{
	if(curl)
	{
		// Add a header to the collection
		std::map<String, String>::iterator it = requestHeaders.find(header);
		if(it == requestHeaders.end())
		{
			requestHeaders.insert(std::pair<String, String>(header, value));
		}
		else
		{
			it->second += ", " + value;
		}
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////
void XMLHttpRequest::send()
{
	send("");
}

//////////////////////////////////////////////////////////////////////////////////////////////
void XMLHttpRequest::send(String data)
{
	if(curl)
	{
		UINT cb = data.size();
		if(cb>0)
		{
			// TODO: convert string to UTF8
			requestDataBuffer.clear();
			requestDataBuffer.resize(cb + 1);
			memcpy(requestDataBuffer.data(), data.c_str(), cb);
			*(requestDataBuffer.data() + cb) = 0;
		}

		curl_send();
		readyState=LOADING;
		tick();
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////
void XMLHttpRequest::send(ArrayBufferView* data)
{
	if(data)
		send( data->buffer);
}

//////////////////////////////////////////////////////////////////////////////////////////////
void XMLHttpRequest::send(ArrayBuffer* ab)
{
	if(curl && ab)
	{
		if(ab->byteLength>0)
		{
			requestDataBuffer.clear();
			requestDataBuffer.resize((size_t)(ab->byteLength+1));
			memcpy(requestDataBuffer.data(), ab->data, (size_t)(ab->byteLength));
			*(requestDataBuffer.data()+ab->byteLength) = 0;
		}
		curl_send();
		readyState=LOADING;
		tick();
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////
void XMLHttpRequest::abort()
{
	if(curl)
	{
		// Unavailable in curl
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////
String XMLHttpRequest::getResponseHeader(String header)
{
	if(curl)
	{
		std::map<String, String>::iterator it = responseHeaders.find(header);
		if(it != responseHeaders.end())
		{
			return it->second;
		}
	}
	return "";
}

//////////////////////////////////////////////////////////////////////////////////////////////
String XMLHttpRequest::getAllResponseHeaders()
{
	String ret = "";

	if(curl)
	{
		for(std::map<String, String>::iterator it = responseHeaders.begin(); it != responseHeaders.end(); it++)
		{
			ret += it->first + ": " + it->second + "\n";
		}
	}
	return ret;
}


////////////////////////////////////////////////////////////////////////////////////////////////////
void XMLHttpRequest::curl_send()
{
	// Pass headers to curl
	curl_slist* httpheader = nullptr;
	for(std::map<String, String>::iterator it = requestHeaders.begin(); it != requestHeaders.end(); it++)
	{
		httpheader = curl_slist_append(httpheader, (it->first + ": " + it->second).c_str());
	}
	curl_easy_setopt(curl, CURLOPT_HTTPHEADER, httpheader);

	if(requestDataBuffer.size())
	{
		// Set data length
		curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, requestDataBuffer.size());

		// pass in a pointer to the data - curl will not copy
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, requestDataBuffer.data());
	}

	if(async)
	{
		// add the easy handle to a multi session
		curl_multi_add_handle(curlm, curl);
	}
	else
	{
		// perform a blocking file transfer
		curl_easy_perform(curl);
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void XMLHttpRequest::curl_complete()
{
	// Split headers
	Array<String>* splHeader = String(std::string(responseHeadersBuffer.begin(), responseHeadersBuffer.end())).split("\n");

	// Get status code
	Array<String>* splStatus = (*splHeader)[0].split(" ");
	status = (unsigned short) parseInt((*splStatus)[1]);

	// Get status text
	statusText = (*splStatus)[2];

	// Init response type
	responseType = "";

	// Read response headers
	for(int32_t i = splHeader->size(); --i;)
	{
		if((*splHeader)[i] != "")
		{
			int32_t pos = (*splHeader)[i].indexOf(":");
			if(pos != -1)
			{
				String key = (*splHeader)[i].substr(0, pos);
				String val = (*splHeader)[i].substr((int32_t)(*splHeader)[i].find_first_not_of(" ", (size_t)pos + 1));
				std::map<String, String>::iterator it = responseHeaders.find(key);
				if(it != responseHeaders.end())
				{
					it->second += ", " + val;
				}
				else
				{
					if(key=="Content-Type")	responseType = val;
					responseHeaders.insert(std::pair<String, String>(key, val));
				}
			}
		}
	}
	delete splHeader;
	delete splStatus;

	// Get response text and try to get an ArrayBuffer
	responseText = std::string(responseDataBuffer.begin(), responseDataBuffer.end());
	response = new ArrayBuffer(responseText.size());
	memcpy(response->data, (unsigned char*)responseText.c_str(), (size_t)responseText.size());
	if(responseType.indexOf("text")==-1 && responseType.indexOf("html")==-1 && responseType.indexOf("xml")==-1 && responseType.indexOf("json")==-1 && responseType.indexOf("javascript")==-1)
		responseType = "arraybuffer";

	// Data are now available
	dataAvailable = true;
	readyState = DONE;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void XMLHttpRequest::curl_multiperform()
{
	int still_running = 0;
	do
	{
		CURLMcode code = CURLM_OK;

		// If code is CURLM_CALL_MULTI_PERFORM we must call curl_multi_perform again immediately.
		while((code = curl_multi_perform(curlm, &still_running))==CURLM_CALL_MULTI_PERFORM);

		if(code==CURLM_OK)
		{
			// Ask the multi handle if there are any messages from the individual transfers.
			int msgs_in_queue = 0;
			CURLMsg* cmsg = curl_multi_info_read(curlm, &msgs_in_queue);
			if(cmsg && cmsg->msg == CURLMSG_DONE)
			{
				XMLHttpRequest* t = nullptr;
				curl_easy_getinfo(cmsg->easy_handle, CURLINFO_PRIVATE, reinterpret_cast<char**>(&t));
				switch(cmsg->data.result)
				{
				case CURLE_OK:
					t->curl_complete();
					break;
				}
			}
		}
	}
	while(still_running);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
size_t XMLHttpRequest::curl_callback(void* contents, size_t size, size_t nmemb, void* ptr)
{
	std::vector<char>* v = static_cast<std::vector<char>*>(ptr);
	size_t s = size * nmemb;
	size_t ps = v->empty() ? 0 : v->size() - 1;
	v->resize(ps + s + 1);
	memcpy(v->data() + ps, contents, s);
	*(v->data() + ps + s) = 0;
	return s;
}
