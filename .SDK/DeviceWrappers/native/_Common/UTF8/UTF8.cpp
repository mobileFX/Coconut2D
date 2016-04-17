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

#include <stdlib.h>
#include <string.h>
#include "UTF8/UTF8.hpp"

utf8_mbstate_t UTF8::internal;

/////////////////////////////////////////////////////////////////////////////
UTF8::UTF8(void)
{
}

/////////////////////////////////////////////////////////////////////////////
UTF8::~UTF8(void)
{
}

/////////////////////////////////////////////////////////////////////////////
size_t UTF8::wcsrtombs(char* dest, const wchar_t** srcp, size_t len, utf8_mbstate_t* ops)
{
	utf8_mbstate_t* ps = (utf8_mbstate_t*) ops;

	if(ps == NULL)
		ps = &internal;

	const wchar_t* src = *srcp;
	if(!locale_is_utf8)
	{
		if(dest != NULL)
		{
			char* destptr = dest;
			for(;;src++)
			{
				u_wchar_t wc = (u_wchar_t) (*src);
				if (wc < 0x100)
				{
					if (len == 0)
					{
						*srcp = src;
						break;
					}
					len--;
					*destptr = (char) wc;
					if (wc == (wchar_t)'\0')
					{
						*srcp = NULL;
						break;
					}
					destptr++;
				}
				else
				{
					*srcp = src;
					return (size_t)(-1);
				}
			}
			return (size_t)(destptr - dest);
		}
		else
		{
			/* Ignore dest and len. */
			int totalcount = 0;
			for(;;src++)
			{
				u_wchar_t wc = (u_wchar_t) (*src);
				if(wc < 0x100)
				{
					if(wc == (wchar_t)'\0')
						break;
					totalcount++;
				}
				else
				{
					return (size_t)(-1);
				}
			}
			return (size_t) totalcount;
		}
	}
	else
	{
		if (dest != NULL)
		{
			char* destptr = dest;
			if (ps->count > 0)
			{
				unsigned int wc = ps->value;
				size_t count = ps->count;
				do
				{
					if (len == 0)
					{
						ps->count = (unsigned int) count;
						return (size_t)(destptr - dest);
					}
					len--;
					*destptr++ = (char)(((wc >> (6 * --count)) & 0x3F) | 0x80);

				} while (count > 0);

				ps->count = 0;
			}

			for (;; src++)
			{
				u_wchar_t wc = (u_wchar_t) (*src);
				size_t count;
				unsigned char c;
				if(wc < 0x80)
				{
					if(wc == (wchar_t)'\0')
					{
						if(len == 0)
						{
							*srcp = src;
							break;
						}
						*destptr = '\0';
						*srcp = NULL;
						break;
					}
					count = 0;
					c = (unsigned char) wc;
				}
				else if (wc < 0x800)
				{
					count = 1;
					c = (unsigned char) ((wc >> 6) | 0xC0);
				}
				else
				#if WCHAR_T_BITS == 32
				if (wc < 0x10000)
				#endif
				{
					count = 2;
					c = (unsigned char) ((wc >> 12) | 0xE0);
				}
				#if WCHAR_T_BITS == 32
				else if (wc < 0x200000)
				{
					count = 3;
					c = (unsigned char) ((wc >> 18) | 0xF0);
				}
				else if (wc < 0x4000000)
				{
					count = 4;
					c = (unsigned char) ((wc >> 24) | 0xF8);
				}
				else if (wc < 0x80000000)
				{
					count = 5;
					c = (unsigned char) ((wc >> 30) | 0xFC);
				}
				else
				{
					*srcp = src;
					return (size_t)(-1);
				}
				#endif
				if (len == 0)
				{
					*srcp = src;
					break;
				}
				len--;
				*destptr++ = (char) c;
				if (count > 0)
				do
				{
					if(len == 0)
					{
						ps->count = (unsigned int) count;
						ps->value = wc;
						*srcp = src+1;
						return (size_t)(destptr - dest);
					}
					len--;
					*destptr++ = (char)(((wc >> (6 * --count)) & 0x3F) | 0x80);
				} while (count > 0);
			}
			return (size_t)(destptr - dest);
		}
		else
		{
			/* Ignore dest and len. */
			size_t totalcount = ps->count;
			ps->count = 0;
			for(;; src++)
			{
				u_wchar_t wc = (u_wchar_t) (*src);
				size_t count;
				if(wc < 0x80)
				{
					if(wc == (wchar_t)'\0')
					{
						*srcp = NULL;
						break;
					}
					count = 1;
				}
				else if (wc < 0x800)
				{
					count = 2;
				}
				else
				#if WCHAR_T_BITS == 32
				if (wc < 0x10000)
				#endif
				{
					count = 3;
				}
				#if WCHAR_T_BITS == 32
				else if (wc < 0x200000)
				{
					count = 4;
				}
				else if (wc < 0x4000000)
				{
					count = 5;
				}
				else if (wc < 0x80000000)
				{
					count = 6;
				}
				else
				{
					*srcp = src;
					return (size_t)(-1);
				}
				#endif
				totalcount += count;
			}
			return totalcount;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////
size_t UTF8::wcstombs(char* s, const wchar_t* pwcs, size_t n)
{
	utf8_mbstate_t state;
	memset(&state, 0, sizeof(utf8_mbstate_t));
	return UTF8::wcsrtombs(s, &pwcs, n, &state);
}

/////////////////////////////////////////////////////////////////////////////
void UTF8::utf8_to_wstring(std::string& src, std::wstring& dest)
{
    dest.clear();

	wchar_t w = 0;
	int bytes = 0;
	wchar_t err = L'?';

	for (size_t i = 0, L = src.length(); i < L ; i++)
	{
		unsigned char c = (unsigned char)src[i];
		if (c <= 0x7f)
		{
			//first byte
			if (bytes)
			{
				dest.push_back(err);
				bytes = 0;
			}
			dest.push_back((wchar_t)c);
		}
		else if (c <= 0xbf)
		{
			//second/third/etc byte
			if (bytes)
			{
				w = ((w << 6)|(c & 0x3f));
				bytes--;
				if (bytes == 0)
					dest.push_back(w);
			}
			else
				dest.push_back(err);
		}
		else if (c <= 0xdf)
		{
			//2byte sequence start
			bytes = 1;
			w = c & 0x1f;
		}
		else if (c <= 0xef)
		{
			//3byte sequence start
			bytes = 2;
			w = c & 0x0f;
		}
		else if (c <= 0xf7)
		{
			//3byte sequence start
			bytes = 3;
			w = c & 0x07;
		}
		else
		{
			dest.push_back(err);
			bytes = 0;
		}
	}
	if (bytes)
		dest.push_back(err);
}

/////////////////////////////////////////////////////////////////////////////
void UTF8::wstring_to_utf8(std::wstring& src, std::string& dest)
{
    dest.clear();
	for (size_t i = 0, L = src.length(); i < L ; i++)
	{
		wchar_t w = src[i];
		if (w <= 0x7f)
			dest.push_back((char)w);
		else if (w <= 0x7ff)
		{
			dest.push_back((int8_t)(0xc0 | ((w >> 6)& 0x1f)));
			dest.push_back((int8_t)(0x80| (w & 0x3f)));
		}
		else if (w <= 0xffff)
		{
			dest.push_back((int8_t)(0xe0 | ((w >> 12)& 0x0f)));
			dest.push_back((int8_t)(0x80| ((w >> 6) & 0x3f)));
			dest.push_back((int8_t)(0x80| (w & 0x3f)));
		}
		else if (w <= 0x10ffff)
		{
			dest.push_back((int8_t)(0xf0 | ((w >> 18)& 0x07)));
			dest.push_back((int8_t)(0x80| ((w >> 12) & 0x3f)));
			dest.push_back((int8_t)(0x80| ((w >> 6) & 0x3f)));
			dest.push_back((int8_t)(0x80| (w & 0x3f)));
		}
		else
			dest.push_back('?');
	}
}

/*
std::ostream& operator<<(std::ostream& f, const std::wstring& s)
{
	std::string s1 = UTF8::wstring_to_utf8(s);
	f << s1;
	return f;
}

std::istream& operator>>(std::istream& f, std::wstring& s)
{
	std::string s1;
	f >> s1;
	s1 = UTF8::utf8_to_wstring(s);
	return f;
}
*/
