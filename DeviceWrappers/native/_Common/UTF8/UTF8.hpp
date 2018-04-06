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

#ifndef __UTF8_HPP__
#define __UTF8_HPP__

#define WCHAR_T_BITS 16
#define u_wchar_t unsigned short
#define locale_is_utf8 1

#include <algorithm>
#include <cassert>
#include <clocale>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <functional>
#include <iostream>
#include <iterator>
#include <memory>
#include <sstream>
#include <stdarg.h>
#include <stdexcept>
#include <stdio.h>
#include <string>

/////////////////////////////////////////////////////////////////////////////
typedef struct
{
	#if WCHAR_T_BITS == 32
		unsigned int count;
		unsigned int value;
	#else
		unsigned int count : 16;
		unsigned int value : 16;
	#endif

} utf8_mbstate_t;

/////////////////////////////////////////////////////////////////////////////
class UTF8
{
public:
	UTF8(void);
	~UTF8(void);
	static utf8_mbstate_t internal;
	static size_t wcstombs(char* s, const wchar_t* pwcs, size_t n);
	static size_t wcsrtombs(char* dest, const wchar_t** srcp, size_t len, utf8_mbstate_t* ops);
    static void utf8_to_wstring(std::string& str, std::wstring& dest);
    static void wstring_to_utf8(std::wstring& str, std::string& dest);
};

#endif //__UTF8_HPP__

