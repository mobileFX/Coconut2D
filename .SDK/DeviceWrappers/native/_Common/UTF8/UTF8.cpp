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
