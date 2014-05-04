#==============================================================================
# iOS Build Makefile
#==============================================================================

CERTIFICATES = ios_development.cer:AppleIncRootCertificate.cer:AppleWWDRCA.cer
PRIVATE_KEY  = ios_development.key
PASSPHRASE   = puerre
PROVISION    = Coconut2D.mobileprovision
IOSMINVER    = 5
CPUSET       = armv7
LDFLAGS		 = -LD:/mobileFX/Projects/Software/Coconut/Projects/Coco.project/.SDK/DeviceWrappers/native/_Libraries/iOS

CFLAGS =  -I.\src \
 -I..\_Common\animations \
 -I..\_Common \
 -I..\..\..\.SDK\Frameworks\org.coconut2d.sdk.webgl\native\src \
 -I..\..\..\.SDK\Frameworks\org.coconut2d.sdk.ui\native\gen\views \
 -I..\..\..\.SDK\Frameworks\org.coconut2d.sdk.ui\native\gen\controls \
 -I..\..\..\.SDK\Frameworks\org.coconut2d.sdk.html5\native\src \
 -I..\..\..\.SDK\Frameworks\org.coconut2d.sdk.html5\native\gen \
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

SRC = src\main.m \
src\fxKeyWrap.m \
src\fxGLWrap.m \
src\fxDeviceWrapper.m \
..\_Common\animations\Page1.cpp \
..\_Common\animations\NewAnimation.cpp \
..\_Common\TestInterfaces.cpp \
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
..\..\..\.SDK\Frameworks\org.coconut2d.sdk.html5\native\src\ImageData.cpp \
..\..\..\.SDK\Frameworks\org.coconut2d.sdk.html5\native\src\HTMLWindow.cpp \
..\..\..\.SDK\Frameworks\org.coconut2d.sdk.html5\native\src\HTMLImageElement.cpp \
..\..\..\.SDK\Frameworks\org.coconut2d.sdk.html5\native\src\HTMLEvent.cpp \
..\..\..\.SDK\Frameworks\org.coconut2d.sdk.html5\native\src\HTMLAudioElement.cpp \
..\..\..\.SDK\Frameworks\org.coconut2d.sdk.html5\native\gen\HTMLTextMetrics.cpp \
..\..\..\.SDK\Frameworks\org.coconut2d.sdk.html5\native\gen\HTMLElement.cpp \
..\..\..\.SDK\Frameworks\org.coconut2d.sdk.html5\native\gen\HTMLDocument.cpp \
..\..\..\.SDK\Frameworks\org.coconut2d.sdk.html5\native\gen\HTMLCanvasPattern.cpp \
..\..\..\.SDK\Frameworks\org.coconut2d.sdk.html5\native\gen\HTMLCanvasGradient.cpp \
..\..\..\.SDK\Frameworks\org.coconut2d.sdk.html5\native\gen\HTMLCanvasElement.cpp \
..\..\..\.SDK\Frameworks\org.coconut2d.sdk.html5\native\gen\CanvasRenderingContext2D.cpp \
..\..\..\.SDK\Frameworks\org.coconut2d.sdk.anim\native\gen\interfaces\ITickable.cpp \
..\..\..\.SDK\Frameworks\org.coconut2d.sdk.anim\native\gen\interfaces\IEventTarget.cpp \
..\..\..\.SDK\Frameworks\org.coconut2d.sdk.anim\native\gen\interfaces\IEventListener.cpp \
..\..\..\.SDK\Frameworks\org.coconut2d.sdk.anim\native\gen\graphics\CocoText.cpp \
..\..\..\.SDK\Frameworks\org.coconut2d.sdk.anim\native\gen\graphics\CocoImage.cpp \
..\..\..\.SDK\Frameworks\org.coconut2d.sdk.anim\native\gen\engine\DeviceTouches.cpp \
..\..\..\.SDK\Frameworks\org.coconut2d.sdk.anim\native\gen\engine\DeviceMessage.cpp \
..\..\..\.SDK\Frameworks\org.coconut2d.sdk.anim\native\gen\engine\CocoTickable.cpp \
..\..\..\.SDK\Frameworks\org.coconut2d.sdk.anim\native\gen\engine\CocoEvents.cpp \
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

RES = ./Icon-100.png \
./Icon-114.png \
./Icon-120.png \
./Icon-144.png \
./Icon-152.png \
./Icon-29.png \
./Icon-29@2x.png \
./Icon-40.png \
./Icon-40@2x.png \
./Icon-48.png \
./Icon-48@2x.png \
./Icon-50.png \
./Icon-57.png \
./Icon-57@2x.png \
./Icon-58.png \
./Icon-60.png \
./Icon-60@2x.png \
./Icon-72.png \
./Icon-72@2x.png \
./Icon-76.png \
./Icon-76@2x.png \
./Icon-80.png \
./Icon-96.png \
./Icon-Small-50.png \
./Icon-Small-50@2x.png \
./Icon.png \
./Icon@2x.png \
./Info.plist \
./iTunesArtwork.png \
./iTunesArtwork@2x.png \
./assets

#==============================================================================
VSCOMPILE 	= yes
NAME		= $(shell "$(IOSBUILDENV_PATH)/Toolchain/plconvert" "Info.plist" -query CFBundleExecutable)
PAYLOAD		= Payload
BIN			= bin
OUTDIR		= $(PAYLOAD)\$(NAME).app
CFLAGS		+= -DIOS_APPLICATION -DENABLE_OPENGL_SUPPORT -DENABLE_PNG_SUPPORT -DENABLE_JPG_SUPPORT -DENABLE_OGG_SUPPORT -DENABLE_OPENAL_SUPPORT -DENABLE_FREETYPE_SUPPORT -DENABLE_CURL_SUPPORT
CFLAGS		+= -O2 -W -Wall -Wno-unused-private-field -Wno-sign-compare -Wno-delete-non-virtual-dtor -Wno-unused-function -Wno-unused-label -Wno-unused-parameter -Wno-unused-variable -Wunused-value -Wempty-body -Wuninitialized -x objective-c++ -std=gnu++11
CFLAGS		+= -target $(CPUSET)-apple-ios$(IOSMINVER).0.0 --sysroot "$(IOSBUILDENV_PATH)/SDK" -integrated-as -fdiagnostics-format=msvc -fconstant-cfstrings -miphoneos-version-min=$(IOSMINVER).0.0 -DIPHONE -D__IPHONE_OS_VERSION_MIN_REQUIRED=$(IOSMINVER)0000
LDFLAGS 	+= -lbz2 -lfreetype -lTremolo -lcurl -ljpeg -lz -lpng
LDFLAGS 	+= -ios_version_min $(IOSMINVER).0 -syslibroot "$(IOSBUILDENV_PATH)/SDK" -lSystem -lcrt1.o -lgcc_s.1 -lstdc++ -F"$(IOSBUILDENV_PATH)/SDK/System/Library/Frameworks" $(shell "$(IOSBUILDENV_PATH)/Toolchain/cat" "$(IOSBUILDENV_PATH)/Frameworks.iOS$(IOSMINVER)")
OBJDIR		= obj
OBJ			= $(addsuffix .obj, $(basename $(SRC)))
OBJ_OBJ		= $(addprefix $(OBJDIR)/, $(addsuffix .obj, $(basename $(notdir $(SRC)))))

#==============================================================================
compile:	$(OBJ)

#link codesign ipa end

#==============================================================================
# Prepare Compilation
#==============================================================================
prepare:
	@"$(IOSBUILDENV_PATH)/Toolchain/echo" "Compiling iOS Project ..."
	@"$(IOSBUILDENV_PATH)/Toolchain/unlink" "$(OUTDIR)"
	@"$(IOSBUILDENV_PATH)/Toolchain/unlink" "$(PAYLOAD)"
	@"$(IOSBUILDENV_PATH)/Toolchain/unlink" *.log
	@"$(IOSBUILDENV_PATH)/Toolchain/unlink" *.lastbuildstate
	@"$(IOSBUILDENV_PATH)/Toolchain/unlink" *.successfulbuild
	@"$(IOSBUILDENV_PATH)/Toolchain/unlink" *.unsuccessfulbuild
	@"$(IOSBUILDENV_PATH)/Toolchain/unlink" "$(BIN)\$(NAME).ipa"
	@"$(IOSBUILDENV_PATH)/Toolchain/mkdir" "$(OBJDIR)"
	@"$(IOSBUILDENV_PATH)/Toolchain/mkdir" "$(OUTDIR)"
	@"$(IOSBUILDENV_PATH)/Toolchain/mkdir" "$(BIN)"

#==============================================================================
# The following rule takes all the specified resource items one after the
# other (whether they are files or directories) ; files are copied in place
# and directories are recursively copied only if their content changed.
# During this process, all property lists are converted in binary format.
#==============================================================================
resources:
	@"$(IOSBUILDENV_PATH)/Toolchain/echo" "Copying resources ..."
	@for %%I in ($(RES)) do ( \
	   if "%%I"=="Info.plist" ( \
	      "$(IOSBUILDENV_PATH)/Toolchain/plconvert" "%%I" "$(OUTDIR)/%%I" -binary -MinimumOSVersion=string:$(IOSMINVER).0 \
	   ) else ( \
	      "$(IOSBUILDENV_PATH)/Toolchain/copy" "%%I" "$(OUTDIR)/%%I" \
	   ) \
	)
	@"$(IOSBUILDENV_PATH)/Toolchain/plconvert" "Info.plist" -query CFBundlePackageType > "$(OUTDIR)/PkgInfo"
	@"$(IOSBUILDENV_PATH)/Toolchain/plconvert" "Info.plist" -query CFBundleSignature >> "$(OUTDIR)/PkgInfo"
	@"$(IOSBUILDENV_PATH)/Toolchain/copy" "iTunesArtwork.*" "$(OUTDIR)/iTunesArtwork"

#==============================================================================
# Compile C/C++ and Objective-C files
#==============================================================================
%.obj:	%.c
	@"$(IOSBUILDENV_PATH)/Toolchain/echo" " + Compiling $< ..."
	@"$(IOSBUILDENV_PATH)/Toolchain/clang" $(CFLAGS) -o "$(addprefix $(OBJDIR)/, $(addsuffix .obj, $(basename $(notdir $@))))" -c "$<"
%.obj:	%.cc
	@"$(IOSBUILDENV_PATH)/Toolchain/echo" " + Compiling $< ..."
	@"$(IOSBUILDENV_PATH)/Toolchain/clang" $(CFLAGS) -o "$(addprefix $(OBJDIR)/, $(addsuffix .obj, $(basename $(notdir $@))))" -c "$<"
%.obj: %.cpp
	@"$(IOSBUILDENV_PATH)/Toolchain/echo" " + Compiling $< ..."
	@"$(IOSBUILDENV_PATH)/Toolchain/clang" $(CFLAGS) -o "$(addprefix $(OBJDIR)/, $(addsuffix .obj, $(basename $(notdir $@))))" -c "$<"
%.obj:	%.cxx
	@"$(IOSBUILDENV_PATH)/Toolchain/echo" " + Compiling $< ..."
	@"$(IOSBUILDENV_PATH)/Toolchain/clang" $(CFLAGS) -o "$(addprefix $(OBJDIR)/, $(addsuffix .obj, $(basename $(notdir $@))))" -c "$<"
%.obj:	%.m
	@"$(IOSBUILDENV_PATH)/Toolchain/echo" " + Compiling $< ..."
	@"$(IOSBUILDENV_PATH)/Toolchain/clang" $(CFLAGS) -o "$(addprefix $(OBJDIR)/, $(addsuffix .obj, $(basename $(notdir $@))))" -c "$<"
%.obj:	%.mm
	@"$(IOSBUILDENV_PATH)/Toolchain/echo" " + Compiling $< ..."
	@"$(IOSBUILDENV_PATH)/Toolchain/clang" $(CFLAGS) -o "$(addprefix $(OBJDIR)/, $(addsuffix .obj, $(basename $(notdir $@))))" -c "$<"
%.obj:	%.mx
	@"$(IOSBUILDENV_PATH)/Toolchain/echo" " + Compiling $< ..."
	@"$(IOSBUILDENV_PATH)/Toolchain/clang" $(CFLAGS) -o "$(addprefix $(OBJDIR)/, $(addsuffix .obj, $(basename $(notdir $@))))" -c "$<"
%.obj:	%.mxx
	@"$(IOSBUILDENV_PATH)/Toolchain/echo" " + Compiling $< ..."
	@"$(IOSBUILDENV_PATH)/Toolchain/clang" $(CFLAGS) -o "$(addprefix $(OBJDIR)/, $(addsuffix .obj, $(basename $(notdir $@))))" -c "$<"
%.obj:	%.s
	@"$(IOSBUILDENV_PATH)/Toolchain/echo" " + Assembling $< ..."
	@"$(IOSBUILDENV_PATH)/Toolchain/clang" $(CFLAGS) -o "$(addprefix $(OBJDIR)/, $(addsuffix .obj, $(basename $(notdir $@))))" -c "$<"

#==============================================================================
# Hack: static libs are treated like source files, except that they aren't
# compiled but just copied to .obj. The linker will figure out what to do.
#==============================================================================
%.obj:	%.a
	@"$(IOSBUILDENV_PATH)/Toolchain/echo" " + Using static library or framework: $< ..."
	@"$(IOSBUILDENV_PATH)/Toolchain/copy" "$<" "$@"

#==============================================================================
# The following rule first ensures the output directory exists, creates it if
# necessary, then links the compiled .obj files together in that directory
#==============================================================================
link:
	@"$(IOSBUILDENV_PATH)/Toolchain/echo" "Linking project files ..."
	@"$(IOSBUILDENV_PATH)/Toolchain/ld" $(LDFLAGS) -o "$(OUTDIR)/$(NAME)" $(OBJ_OBJ)

#==============================================================================
# The following rule generates the SHA1 checksums for the resource files, then
# insert a code signature blob in the binary, seals the binary code, resources
# and Info.plist and sign it with the specified application identifier.
#==============================================================================
codesign:
	@"$(IOSBUILDENV_PATH)/Toolchain/echo" "Signing code ..."
	@"$(IOSBUILDENV_PATH)/Toolchain/copy" "$(IOSBUILDENV_PATH)\Keychain\$(PROVISION)" "$(OUTDIR)\embedded.mobileprovision"
	@"$(IOSBUILDENV_PATH)/Toolchain/ldid" -k"$(IOSBUILDENV_PATH)/Keychain" -S$(CERTIFICATES):$(PRIVATE_KEY):$(PASSPHRASE) -C -E -I "$(OUTDIR)/$(NAME)"

#==============================================================================
# The following rule builds an IPA bundle out of the compiled app directory.
#==============================================================================
ipa:
	@"$(IOSBUILDENV_PATH)/Toolchain/echo" "Building iTunes package ..."
	@"$(IOSBUILDENV_PATH)/Toolchain/zip" -q -r "$(BIN)/$(NAME).ipa" "$(PAYLOAD)" "iTunesArtwork" -x \*.log \*.lastbuildstate \*successfulbuild

#==============================================================================
# This simple rule displays the success message after a successful build
#==============================================================================
end:
	@"$(IOSBUILDENV_PATH)/Toolchain/unlink" "$(OUTDIR)"
	@"$(IOSBUILDENV_PATH)/Toolchain/unlink" "$(PAYLOAD)"
	@"$(IOSBUILDENV_PATH)/Toolchain/unlink" "$(OBJDIR)"
