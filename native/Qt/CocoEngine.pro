TARGET = CocoEngine
TEMPLATE = app
QT += core gui opengl
CONFIG += c++11

HEADERS += \
*.h* \
../Common/*.h* \
../Common/Arrays_API/*.h* \
../Common/Assets_API/*.h* \
../Common/Audio_API/*.h* \
../Common/CocoScript_API/*.h* \
../Common/CocoScript_API/anim/*.h*        
../Common/CocoScript_API/game/*.h*        
../Common/CocoScript_API/ui/*.h*        
../Common/Fonts_API/*.h* \
../Common/HTML5_API/*.h* \
../Common/HTTP_API/*.h* \
../Common/Physics_API/*.h* \
../Common/Video_API/*.h* \
../Common/WebGL_API/*.h* \
../Common/WebSocket_API/*.h*

SOURCES += \
*.cpp \
../Common/*.cpp \
../Common/Arrays_API/*.cpp \
../Common/Assets_API/*.cpp \
../Common/Audio_API/*.cpp \
../Common/CocoScript_API/*.cpp \
../Common/CocoScript_API/anim/*.cpp \
../Common/CocoScript_API/game/*.cpp \
../Common/CocoScript_API/ui/*.cpp \
../Common/Fonts_API/*.cpp \
../Common/HTML5_API/*.cpp \
../Common/HTTP_API/*.cpp \
../Common/Physics_API/*.cpp \
../Common/Video_API/*.cpp \
../Common/WebGL_API/*.cpp \
../Common/WebSocket_API/*.cpp

INCLUDEPATH += \
../Include \
../Common

LIBS += -L$$_PRO_FILE_PWD_/../../Libraries/MacOSX/x86_64 -lv8_base -lv8_nosnapshot -lv8_snapshot -lpreparser_lib -lpng -lz

QMAKE_CXXFLAGS += -DJAVASCRIPT_ENGINE_V8 -DENABLE_FX_DEBUG

QMAKE_CXXFLAGS += -DENABLE_OPENGL_SUPPORT
QMAKE_CXXFLAGS += -DDISABLE_OPENAL_SUPPORT
QMAKE_CXXFLAGS += -DDISABLE_FREETYPE_SUPPORT
QMAKE_CXXFLAGS += -DENABLE_PNG_SUPPORT
QMAKE_CXXFLAGS += -DDISABLE_JPEG_SUPPORT
QMAKE_CXXFLAGS += -DDISABLE_OGG_SUPPORT
QMAKE_CXXFLAGS += -DDISABLE_CURL_SUPPORT

QMAKE_CXXFLAGS_WARN_ON += -Wno-unused-parameter -Wno-unused-variable
