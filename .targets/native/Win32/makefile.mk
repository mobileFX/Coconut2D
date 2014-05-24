#==============================================================================
# MinGW Makefile
#==============================================================================

LDFLAGS = -LD:/mobileFX/Projects/Software/Coconut/Projects/Coco.project/.SDK/DeviceWrappers/native/_Libraries/Win32

CFLAGS =  -I.\src\GL \
 -I.\src \
 -I..\_Common\animations \
 -I..\_Common \
 -I..\..\..\.SDK\Frameworks\org.coconut2d.sdk.webgl\native\src \
 -I..\..\..\.SDK\Frameworks\org.coconut2d.sdk.ui\native\gen\views \
 -I..\..\..\.SDK\Frameworks\org.coconut2d.sdk.ui\native\gen\controls \
 -I..\..\..\.SDK\Frameworks\org.coconut2d.sdk.net\native\src \
 -I..\..\..\.SDK\Frameworks\org.coconut2d.sdk.html5\native\src \
 -I..\..\..\.SDK\Frameworks\org.coconut2d.sdk.html5\native\gen \
 -I..\..\..\.SDK\Frameworks\org.coconut2d.sdk.anim\native\src \
 -I..\..\..\.SDK\Frameworks\org.coconut2d.sdk.anim\native\gen\interfaces \
 -I..\..\..\.SDK\Frameworks\org.coconut2d.sdk.anim\native\gen\graphics \
 -I..\..\..\.SDK\Frameworks\org.coconut2d.sdk.anim\native\gen\engine \
 -I..\..\..\.SDK\Frameworks\org.coconut2d.sdk.anim\native\gen\audio \
 -I..\..\..\.SDK\Frameworks\org.coconut2d.sdk.anim\native\gen \
 -I..\..\..\.SDK\DeviceWrappers\native\_Includes \
 -I..\..\..\.SDK\DeviceWrappers\native\_Common\Fonts \
 -I..\..\..\.SDK\DeviceWrappers\native\_Common\Events \
 -I..\..\..\.SDK\DeviceWrappers\native\_Common\Audio \
 -I..\..\..\.SDK\DeviceWrappers\native\_Common\Arrays \
 -I..\..\..\.SDK\DeviceWrappers\native\_Common

SRC = src/resource.h src\main.cpp \
src\fxDeviceWrapper.cpp \
src\AssetFile.cpp \
..\_Common\animations\Page1.cpp \
..\_Common\animations\NewAnimation.cpp \
..\_Common\TestInterfaces.cpp \
..\_Common\TestEvents.cpp \
..\_Common\GameEngine.cpp \
..\..\..\.SDK\Frameworks\org.coconut2d.sdk.webgl\native\src\WebGLRenderingContext.cpp \
..\..\..\.SDK\Frameworks\org.coconut2d.sdk.ui\native\gen\views\CocoUIView.cpp \
..\..\..\.SDK\Frameworks\org.coconut2d.sdk.ui\native\gen\views\CocoUIPage.cpp \
..\..\..\.SDK\Frameworks\org.coconut2d.sdk.ui\native\gen\controls\CocoUITextBox.cpp \
..\..\..\.SDK\Frameworks\org.coconut2d.sdk.ui\native\gen\controls\CocoUILabel.cpp \
..\..\..\.SDK\Frameworks\org.coconut2d.sdk.ui\native\gen\controls\CocoUIControl.cpp \
..\..\..\.SDK\Frameworks\org.coconut2d.sdk.ui\native\gen\controls\CocoUIComboBox.cpp \
..\..\..\.SDK\Frameworks\org.coconut2d.sdk.ui\native\gen\controls\CocoUICheckBox.cpp \
..\..\..\.SDK\Frameworks\org.coconut2d.sdk.ui\native\gen\controls\CocoUIButton.cpp \
..\..\..\.SDK\Frameworks\org.coconut2d.sdk.net\native\src\XMLHttpRequest.cpp \
..\..\..\.SDK\Frameworks\org.coconut2d.sdk.html5\native\src\ImageData.cpp \
..\..\..\.SDK\Frameworks\org.coconut2d.sdk.html5\native\src\HTMLWindow.cpp \
..\..\..\.SDK\Frameworks\org.coconut2d.sdk.html5\native\src\HTMLEvent.cpp \
..\..\..\.SDK\Frameworks\org.coconut2d.sdk.html5\native\src\HTMLAudioElement.cpp \
..\..\..\.SDK\Frameworks\org.coconut2d.sdk.html5\native\gen\HTMLTextMetrics.cpp \
..\..\..\.SDK\Frameworks\org.coconut2d.sdk.html5\native\gen\HTMLImageElement.cpp \
..\..\..\.SDK\Frameworks\org.coconut2d.sdk.html5\native\gen\HTMLElement.cpp \
..\..\..\.SDK\Frameworks\org.coconut2d.sdk.html5\native\gen\HTMLDocument.cpp \
..\..\..\.SDK\Frameworks\org.coconut2d.sdk.html5\native\gen\HTMLCanvasPattern.cpp \
..\..\..\.SDK\Frameworks\org.coconut2d.sdk.html5\native\gen\HTMLCanvasGradient.cpp \
..\..\..\.SDK\Frameworks\org.coconut2d.sdk.html5\native\gen\HTMLCanvasElement.cpp \
..\..\..\.SDK\Frameworks\org.coconut2d.sdk.html5\native\gen\CanvasRenderingContext2D.cpp \
..\..\..\.SDK\Frameworks\org.coconut2d.sdk.anim\native\src\CocoEventSource.cpp \
..\..\..\.SDK\Frameworks\org.coconut2d.sdk.anim\native\src\CocoEventConnectionPoint.cpp \
..\..\..\.SDK\Frameworks\org.coconut2d.sdk.anim\native\gen\interfaces\ITickable.cpp \
..\..\..\.SDK\Frameworks\org.coconut2d.sdk.anim\native\gen\interfaces\IEventTarget.cpp \
..\..\..\.SDK\Frameworks\org.coconut2d.sdk.anim\native\gen\interfaces\ICocoRenderContext.cpp \
..\..\..\.SDK\Frameworks\org.coconut2d.sdk.anim\native\gen\interfaces\ICocoImageRenderData.cpp \
..\..\..\.SDK\Frameworks\org.coconut2d.sdk.anim\native\gen\graphics\CocoText.cpp \
..\..\..\.SDK\Frameworks\org.coconut2d.sdk.anim\native\gen\graphics\CocoRenderContextGL.cpp \
..\..\..\.SDK\Frameworks\org.coconut2d.sdk.anim\native\gen\graphics\CocoRenderContext2D.cpp \
..\..\..\.SDK\Frameworks\org.coconut2d.sdk.anim\native\gen\graphics\CocoRenderContext.cpp \
..\..\..\.SDK\Frameworks\org.coconut2d.sdk.anim\native\gen\graphics\CocoImage.cpp \
..\..\..\.SDK\Frameworks\org.coconut2d.sdk.anim\native\gen\graphics\CocoGraphics.cpp \
..\..\..\.SDK\Frameworks\org.coconut2d.sdk.anim\native\gen\engine\DeviceTouches.cpp \
..\..\..\.SDK\Frameworks\org.coconut2d.sdk.anim\native\gen\engine\DeviceMessage.cpp \
..\..\..\.SDK\Frameworks\org.coconut2d.sdk.anim\native\gen\engine\CocoTickable.cpp \
..\..\..\.SDK\Frameworks\org.coconut2d.sdk.anim\native\gen\engine\CocoEvent.cpp \
..\..\..\.SDK\Frameworks\org.coconut2d.sdk.anim\native\gen\engine\CocoEngine.cpp \
..\..\..\.SDK\Frameworks\org.coconut2d.sdk.anim\native\gen\audio\CocoAudio.cpp \
..\..\..\.SDK\Frameworks\org.coconut2d.sdk.anim\native\gen\Constants.cpp \
..\..\..\.SDK\Frameworks\org.coconut2d.sdk.anim\native\gen\CocoTimeline.cpp \
..\..\..\.SDK\Frameworks\org.coconut2d.sdk.anim\native\gen\CocoScene.cpp \
..\..\..\.SDK\Frameworks\org.coconut2d.sdk.anim\native\gen\CocoMatrix.cpp \
..\..\..\.SDK\Frameworks\org.coconut2d.sdk.anim\native\gen\CocoClip.cpp \
..\..\..\.SDK\DeviceWrappers\native\_Common\Fonts\fxFontFace.cpp \
..\..\..\.SDK\DeviceWrappers\native\_Common\Fonts\CocoFont.cpp \
..\..\..\.SDK\DeviceWrappers\native\_Common\Events\EventTarget.cpp \
..\..\..\.SDK\DeviceWrappers\native\_Common\Coconut2D.cpp \
..\..\..\.SDK\DeviceWrappers\native\_Common\Audio\fxAudioStream.cpp \
..\..\..\.SDK\DeviceWrappers\native\_Common\Arrays\TypedArray.cpp \
..\..\..\.SDK\DeviceWrappers\native\_Common\Arrays\ArrayBufferView.cpp \
..\..\..\.SDK\DeviceWrappers\native\_Common\Arrays\ArrayBuffer.cpp

RES = ./assets

#==============================================================================
CC 			= D:/mobileFX/Projects/Software/Coconut/IDE/Studio/etc/3rd_party/MinGW/bin/g++.exe
RC 			= D:/mobileFX/Projects/Software/Coconut/IDE/Studio/etc/3rd_party/MinGW/bin/windres.exe
OBJ			= obj
OBJS		= $(addsuffix .obj, $(basename $(SRC)))
OBJ_OBJ		= $(addprefix $(OBJ)/, $(addsuffix .obj, $(basename $(notdir $(SRC)))))
OUT			= Coconut2D.exe
CFLAGS		+= -gdwarf-2 -g3 -m32 -std=gnu++11
CFLAGS		+= -D GC_THREADS -D WIN32_THREADS -D GC_THREADS -D THREAD_LOCAL_ALLOC -D PARALLEL_MARK -D UNICODE -D _UNICODE -D _WIN32_IE=0x0500 -D WINVER=0x500 -D WIN32 -D _WINDOWS -D _CRT_SECURE_NO_DEPRECATE -D _CRT_NONSTDC_NO_DEPRECATE -D GLEW_STATIC -D CURL_STATICLIB
CFLAGS		+= -D WIN32_APPLICATION -D ENABLE_OPENGL_SUPPORT -D ENABLE_PNG_SUPPORT -D ENABLE_JPG_SUPPORT -D ENABLE_OGG_SUPPORT -D ENABLE_OPENAL_SUPPORT -D ENABLE_FREETYPE_SUPPORT -D ENABLE_CURL_SUPPORT
CFLAGS		+= -Wall -Wno-unused-but-set-variable -Wno-sign-compare -Wno-delete-non-virtual-dtor -Wno-unused-function -Wno-unused-label -Wno-unused-parameter -Wno-unused-variable -Wunused-value -Wempty-body -Wuninitialized -Wno-comment
LDFLAGS 	+= -static -static-libgcc -static-libstdc++ -Wl,--subsystem,windows
LDLIBS 		= -lglew32 -lopengl32 -lcomdlg32 -lcomctl32 -luuid -loleaut32 -lole32 -lgdi32 -lfreetype -ljpeg -lpng -lz -lvorbisidec -logg -lOpenAL32 -lcurldll -lpthread

#-lpthread -L libwinpthread-1.dll

#==============================================================================
all: $(OUT)

$(OBJ):
	mkdir $(OBJ)

$(OBJS): | $(OBJ)

#==============================================================================
# Clean/Prepare Compilation
#==============================================================================
clean:
	del $(OUT)
	del obj\*.o

#==============================================================================
# Compile C/C++ files
#==============================================================================
%.obj: %.cpp
	@echo  + Compiling $< ...
	@$(CC) $(CFLAGS) -c $< -o "$(addprefix $(OBJ)/, $(addsuffix .obj, $(basename $(notdir $@))))"

#==============================================================================
# Compile Resources
#==============================================================================
src/resource.obj: res/resource.rc res/Application.manifest res/Application.ico src/resource.h
	$(RC) -I.\src -I.\res -i $< -o $(OBJ)/resource.obj

#==============================================================================
# Link
#==============================================================================
$(OUT): $(OBJS)
	$(CC) $(LDFLAGS) -g -o $(OUT) $(OBJ_OBJ) $(LDLIBS)

