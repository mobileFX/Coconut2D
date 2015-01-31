#ifndef __UTF8_HPP__
#define __UTF8_HPP__

#define WCHAR_T_BITS 16
#define u_wchar_t unsigned short
#define locale_is_utf8 1

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
};

#endif //__UTF8_HPP__

