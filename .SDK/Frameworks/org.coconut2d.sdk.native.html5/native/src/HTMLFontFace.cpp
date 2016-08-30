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
//	    __  __________  _____    ______            __  ______
//	   / / / /_  __/  |/  / /   / ____/___  ____  / /_/ ____/___ _________
//	  / /_/ / / / / /|_/ / /   / /_  / __ \/ __ \/ __/ /_  / __ `/ ___/ _ \
//	 / __  / / / / /  / / /___/ __/ / /_/ / / / / /_/ __/ / /_/ / /__/  __/
//	/_/ /_/ /_/ /_/  /_/_____/_/    \____/_/ /_/\__/_/    \__,_/\___/\___/
//
// ==================================================================================================================================

#include "HTMLFontFace.hpp"

///////////////////////////////////////////////////////////////////////////////////////////////////

FT_Library ftLibrary;
bool _initLibrary = true;
cairo_user_data_key_t key;
std::map<String, HTMLFontFace*> fontsCache;

///////////////////////////////////////////////////////////////////////////////////////////////////
HTMLFontFace::HTMLFontFace(FT_Face ftFace, cairo_font_face_t *crFace)
{
	_ftFace = ftFace;
	_crFace = crFace;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
HTMLFontFace::~HTMLFontFace()
{
	cairo_font_face_destroy(_crFace);
}

///////////////////////////////////////////////////////////////////////////////////////////////////
HTMLFontFace* HTMLFontFace::getFont(String fontName)
{
	if (fontsCache.find(fontName) != fontsCache.end())
	{
		return fontsCache[fontName];
	}

	FT_Face ftFace;
	FT_Error ftError;
	cairo_font_face_t *crFace;

	// Initialize FreeType Library
	if (_initLibrary)
	{
		_initLibrary = false;
		ftError = FT_Init_FreeType(&ftLibrary);
		if (ftError) return nullptr;
	}

	// Open font file
	String fileName = getFontPath(fontName);
	CocoAssetFile* file = CocoAssetFile::open(fileName);

	// Create new FreeType font face from file
	ftError = FT_New_Memory_Face(ftLibrary, (const FT_Byte*) file->getData(), (long) file->bytesLength(), 0, &ftFace);
	if (ftError) return nullptr;

	// Create new Cairo font face.
	crFace = cairo_ft_font_face_create_for_ft_face(ftFace, 0);

  	// FreeType provides the ability to synthesize different glyphs from a base font, which is useful if you lack those glyphs from a true bold or oblique font
  	//cairo_ft_font_face_set_synthesize(crFace, CAIRO_FT_SYNTHESIZE_BOLD | CAIRO_FT_SYNTHESIZE_OBLIQUE);

	// If the Cairo font face is released, release the FreeType font face as well.
	int status = cairo_font_face_set_user_data(crFace, &key, ftFace, (cairo_destroy_func_t) FT_Done_Face);
	if (status)
	{
		cairo_font_face_destroy(crFace);
		FT_Done_Face(ftFace);
		delete file;
		return nullptr;
	}

	// Explicit reference count the Cairo font face.
	cairo_font_face_reference(crFace);

	// Save font in cache
	fontsCache[fontName] = new HTMLFontFace(ftFace, crFace);

	// return font
	return fontsCache[fontName];

	// Note: file remains in memory, might want to fix this
}

///////////////////////////////////////////////////////////////////////////////////////////////////
String HTMLFontFace::getFontName(String faceName, String faceStyle, String faceWeight)
{
	String FontName = faceName;

	if (faceStyle == "normal") faceStyle = "";
	if (faceWeight != "bold") faceWeight = "";

	if (faceStyle.size() > 0 && faceWeight.size() > 0)
	{
		// Arial Bold Italic
		FontName = faceName + " " + faceWeight + " " + faceStyle;
	}
	else if (faceStyle.size() > 0)
	{
		// Arial Italic
		FontName = faceName + " " + faceStyle;
	}
	if (faceWeight.size() > 0)
	{
		// Arial Bold
		FontName = faceName + " " + faceWeight;
	}

	return FontName;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
String HTMLFontFace::getFontPath(String fontName)
{
	#ifdef IOS_APPLICATION

		return fontName;

	#elif ANDROID_APPLICATION

		return fontName;

	#elif WIN32_APPLICATION

		static const LPWSTR fontRegistryPath = L"Software\\Microsoft\\Windows NT\\CurrentVersion\\Fonts";
		HKEY hKey;
		LONG result;
		std::wstring wsFaceName(fontName.begin(), fontName.end());

		// Open Windows font registry key
		result = RegOpenKeyEx(HKEY_LOCAL_MACHINE, fontRegistryPath, 0, KEY_READ, &hKey);
		if (result != ERROR_SUCCESS)
		{
			return "";
		}

		DWORD maxValueNameSize, maxValueDataSize;
		result = RegQueryInfoKey(hKey, 0, 0, 0, 0, 0, 0, 0, &maxValueNameSize, &maxValueDataSize, 0, 0);
		if (result != ERROR_SUCCESS)
		{
			return "";
		}

		DWORD valueIndex = 0;
		LPWSTR valueName = new WCHAR[maxValueNameSize];
		LPBYTE valueData = new BYTE[maxValueDataSize];
		DWORD valueNameSize, valueDataSize, valueType;
		std::wstring wsFontFile;

		// Look for a matching font name
		do
		{
			wsFontFile.clear();
			valueDataSize = maxValueDataSize;
			valueNameSize = maxValueNameSize;

			result = RegEnumValue(hKey, valueIndex, valueName, &valueNameSize, 0, &valueType, valueData, &valueDataSize);

			valueIndex++;

			if (result != ERROR_SUCCESS || valueType != REG_SZ) {
				continue;
			}

			std::wstring wsValueName(valueName, valueNameSize);

			// Found a match
			if (_wcsnicmp(wsFaceName.c_str(), wsValueName.c_str(), wsFaceName.length()) == 0)
			{
				wsFontFile.assign((LPWSTR) valueData, valueDataSize);
				break;
			}
		} while (result != ERROR_NO_MORE_ITEMS);

		delete[] valueName;
		delete[] valueData;

		RegCloseKey(hKey);

		if (wsFontFile.empty())
		{
			return "";
		}

		// Build full font file path
		WCHAR winDir[MAX_PATH];
		GetWindowsDirectory(winDir, MAX_PATH);

		std::wstringstream ss;
		ss << winDir << "\\Fonts\\" << wsFontFile;
		wsFontFile = ss.str();

		return String(std::string(wsFontFile.begin(), wsFontFile.end()));

	#endif
}

///////////////////////////////////////////////////////////////////////////////////////////////////
bool HTMLFontFace::parseCSSFont(String font, String& fontFamily, int32_t& fontSizeInPixels, String& fontStyle, String& fontWeight)
{
	fontStyle = "normal";
	fontWeight = "normal";
	fontFamily = "Arial";

	String v(font);
	Array<String>* spl = v.split(" ");
	String fontVariant = "normal";
	String fontSize = "medium";
	String lineHeight = "normal";

	int32_t s = 0;
	String str = "";
	for (int32_t i = 0; i < spl->size(); i++)
	{
		str = (*spl)[i];
		if (!str)
		{
			continue;
		}
		switch (s)
		{
		case 3:
		{
			{
				int32_t idx = str.indexOf("/");
				if (idx != -1)
				{
					fontSize = str.substr(0, idx);
					String lh = str.substr(idx + 1);
					if (lh)
					{
						lineHeight = lh;
						s++;
					}
				}
				else
				{
					fontSize = str;
				}
				s++;
				break;
			}
		}
		break;
		case 4:
		{
			{
				int32_t idx = str.indexOf("/");
				if (idx != -1)
				{
					String lh = str.substr(idx + 1);
					if (lh)
					{
						lineHeight = lh;
						s++;
					}
				}
				else
				{
					Array<String>* t = spl->slice(i);
					fontFamily = t->join("");
					delete t;
					i = spl->size();
				}
				s++;
				break;
			}
		}
		break;
		case 5:
		{
			{
				Array<String>* t = spl->slice(i + 1);
				fontFamily = t->join("");
				delete t;
				i = spl->size();
				break;
			}
		}
		break;
		default:
		{
			{
				if (str == "inherit")
				{
					delete spl;
					return false;
				}
				else if (str == "normal")
				{
					switch (s)
					{
					case 0:
					{
						s++;
						break;
					}
					break;
					case 1:
					{
						s++;
						break;
					}
					break;
					case 2:
					{
						s++;
						break;
					}
					break;
					case 4:
					{
						s++;
						break;
					}
					break;
					default:
					{
						delete spl;
						return false;
					}
					break;
					}
				}
				else if (str == "italic" || str == "oblique")
				{
					switch (s)
					{
					case 0:
					{
						fontStyle = str;
						s = 1;
						break;
					}
					break;
					default:
					{
						delete spl;
						return false;
					}
					break;
					}
				}
				else if (str == "small-caps")
				{
					switch (s)
					{
					case 0:
					{
						fontVariant = str;
						s = 2;
						break;
					}
					break;
					case 1:
					{
						fontVariant = str;
						s = 2;
						break;
					}
					break;
					default:
					{
						delete spl;
						return false;
					}
					break;
					}
				}
				else if (str == "bold" || str == "bolder" || str == "lighter" || str == "100" || str == "200" || str == "300" || str == "400" || str == "500" || str == "600" || str == "700" || str == "800" || str == "900")
				{
					switch (s)
					{
					case 1:
					{
						fontWeight = str;
						s = 3;
						break;
					}
					break;
					case 2:
					{
						fontWeight = str;
						s = 3;
						break;
					}
					break;
					default:
					{
						delete spl;
						return false;
					}
					break;
					}
				}
			}
		}
		break;
		}
	}

	fontSizeInPixels = 0;
	if (fontSize == "xx-small")
	{
		fontSizeInPixels = 9;
	}
	else if (fontSize == "x-small")
	{
		fontSizeInPixels = 10;
	}
	else if (fontSize == "small")
	{
		fontSizeInPixels = 13;
	}
	else if (fontSize == "medium")
	{
		fontSizeInPixels = 16;
	}
	else if (fontSize == "large")
	{
		fontSizeInPixels = 18;
	}
	else if (fontSize == "x-large")
	{
		fontSizeInPixels = 24;
	}
	else if (fontSize == "xx-large")
	{
		fontSizeInPixels = 32;
	}
	else if (fontSize == "smaller")
	{
		fontSizeInPixels = 13;
	}
	else if (fontSize == "larger")
	{
		fontSizeInPixels = 18;
	}
	else
	{
		if (fontSize.indexOf("px") != -1)
		{
			fontSizeInPixels = static_cast<int32_t>(atof(fontSize.c_str()));
		}
		else if (fontSize.indexOf("in") != -1)
		{
			fontSizeInPixels = (int32_t) (atof(fontSize.c_str()) * 160.0f);
		}
		else if (fontSize.indexOf("cm") != -1)
		{
			fontSizeInPixels = (int32_t) (atof(fontSize.c_str()) * 160.0f / 2.54f);
		}
		else
		{
			delete spl;
			return false;
		}
	}

	if (spl) delete spl;

	return true;
}
