#include "fxFontFace.h"

#ifdef ENABLE_FREETYPE_SUPPORT
extern FT_Library fxFontFace::ftLibrary;
extern std::map<std::string, fxFontFace*> fxFontFace::fonts;
#endif /* ENABLE_FREETYPE_SUPPORT */