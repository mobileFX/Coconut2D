TARGET = CocoEngine
TEMPLATE = app
QT += core gui opengl
CONFIG += c++11

SOURCES += \
        main.cpp \
        fxDeviceWrapper.cpp \
        ../../Common/fxCRL.cpp \
        ../../Common/fxFontFace.cpp \
        ../../Common/fxAudioStream.cpp \
        ../../Common/fxJS/ArrayBuffer.cpp \
        ../../Common/fxJS/ArrayBufferView.cpp \
        ../../Common/fxJS/Audio.cpp \
        ../../Common/fxJS/DataView.cpp \
        ../../Common/fxJS/fxFont.cpp \
        ../../Common/fxJS/TypedArray.cpp \
        ../../Common/fxJS/WebGLRenderingContext.cpp \
        ../../Common/fxJS/XMLHttpRequest.cpp

HEADERS += fxDeviceWrapper.h \
        fxFile.h \
        ../../Common/Common.h

INCLUDEPATH += \
        ../../Include \
        ../../Common \
        ../../Common/fxJS

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
