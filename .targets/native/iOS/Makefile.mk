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
 -I..\..\..\.SDK\Frameworks\org.coconut2d.sdk.html5\native\src \
 -I..\..\..\.SDK\Frameworks\org.coconut2d.sdk.html5\native\gen \
 -I..\..\..\.SDK\Frameworks\org.coconut2d.sdk.anim\native\gen \
 -I..\..\..\.SDK\DeviceWrappers\native\_Includes \
 -I..\..\..\.SDK\DeviceWrappers\native\_Common\Fonts \
 -I..\..\..\.SDK\DeviceWrappers\native\_Common\Events \
 -I..\..\..\.SDK\DeviceWrappers\native\_Common\Audio \
 -I..\..\..\.SDK\DeviceWrappers\native\_Common\Arrays \
 -I..\..\..\.SDK\DeviceWrappers\native\_Common

SRC = D:\mobileFX\Projects\Software\Coconut\Projects\Coco.project\.targets\native\iOS\src\main.m \
D:\mobileFX\Projects\Software\Coconut\Projects\Coco.project\.targets\native\iOS\src\fxKeyWrap.m \
D:\mobileFX\Projects\Software\Coconut\Projects\Coco.project\.targets\native\iOS\src\fxGLWrap.m \
D:\mobileFX\Projects\Software\Coconut\Projects\Coco.project\.targets\native\iOS\src\fxDeviceWrapper.m \
D:\mobileFX\Projects\Software\Coconut\Projects\Coco.project\.targets\native\_Common\animations\NewAnimation.cpp \
D:\mobileFX\Projects\Software\Coconut\Projects\Coco.project\.targets\native\_Common\GameEngine.cpp \
D:\mobileFX\Projects\Software\Coconut\Projects\Coco.project\.SDK\Frameworks\org.coconut2d.sdk.webgl\native\src\WebGLRenderingContext.cpp \
D:\mobileFX\Projects\Software\Coconut\Projects\Coco.project\.SDK\Frameworks\org.coconut2d.sdk.html5\native\src\ImageData.cpp \
D:\mobileFX\Projects\Software\Coconut\Projects\Coco.project\.SDK\Frameworks\org.coconut2d.sdk.html5\native\src\HTMLWindow.cpp \
D:\mobileFX\Projects\Software\Coconut\Projects\Coco.project\.SDK\Frameworks\org.coconut2d.sdk.html5\native\src\HTMLImageElement.cpp \
D:\mobileFX\Projects\Software\Coconut\Projects\Coco.project\.SDK\Frameworks\org.coconut2d.sdk.html5\native\src\HTMLEvent.cpp \
D:\mobileFX\Projects\Software\Coconut\Projects\Coco.project\.SDK\Frameworks\org.coconut2d.sdk.html5\native\src\HTMLAudioElement.cpp \
D:\mobileFX\Projects\Software\Coconut\Projects\Coco.project\.SDK\Frameworks\org.coconut2d.sdk.html5\native\gen\HTMLTextMetrics.cpp \
D:\mobileFX\Projects\Software\Coconut\Projects\Coco.project\.SDK\Frameworks\org.coconut2d.sdk.html5\native\gen\HTMLElement.cpp \
D:\mobileFX\Projects\Software\Coconut\Projects\Coco.project\.SDK\Frameworks\org.coconut2d.sdk.html5\native\gen\HTMLDocument.cpp \
D:\mobileFX\Projects\Software\Coconut\Projects\Coco.project\.SDK\Frameworks\org.coconut2d.sdk.html5\native\gen\HTMLCanvasElement.cpp \
D:\mobileFX\Projects\Software\Coconut\Projects\Coco.project\.SDK\Frameworks\org.coconut2d.sdk.html5\native\gen\HTMLCanvasContext.cpp \
D:\mobileFX\Projects\Software\Coconut\Projects\Coco.project\.SDK\Frameworks\org.coconut2d.sdk.html5\native\gen\CanvasRenderingContext2D.cpp \
D:\mobileFX\Projects\Software\Coconut\Projects\Coco.project\.SDK\Frameworks\org.coconut2d.sdk.anim\native\gen\Constants.cpp \
D:\mobileFX\Projects\Software\Coconut\Projects\Coco.project\.SDK\Frameworks\org.coconut2d.sdk.anim\native\gen\CocoVector.cpp \
D:\mobileFX\Projects\Software\Coconut\Projects\Coco.project\.SDK\Frameworks\org.coconut2d.sdk.anim\native\gen\CocoTimeline.cpp \
D:\mobileFX\Projects\Software\Coconut\Projects\Coco.project\.SDK\Frameworks\org.coconut2d.sdk.anim\native\gen\CocoTimeLabel.cpp \
D:\mobileFX\Projects\Software\Coconut\Projects\Coco.project\.SDK\Frameworks\org.coconut2d.sdk.anim\native\gen\CocoText.cpp \
D:\mobileFX\Projects\Software\Coconut\Projects\Coco.project\.SDK\Frameworks\org.coconut2d.sdk.anim\native\gen\CocoSequence.cpp \
D:\mobileFX\Projects\Software\Coconut\Projects\Coco.project\.SDK\Frameworks\org.coconut2d.sdk.anim\native\gen\CocoScene.cpp \
D:\mobileFX\Projects\Software\Coconut\Projects\Coco.project\.SDK\Frameworks\org.coconut2d.sdk.anim\native\gen\CocoRect.cpp \
D:\mobileFX\Projects\Software\Coconut\Projects\Coco.project\.SDK\Frameworks\org.coconut2d.sdk.anim\native\gen\CocoMatrix.cpp \
D:\mobileFX\Projects\Software\Coconut\Projects\Coco.project\.SDK\Frameworks\org.coconut2d.sdk.anim\native\gen\CocoKeyFrame.cpp \
D:\mobileFX\Projects\Software\Coconut\Projects\Coco.project\.SDK\Frameworks\org.coconut2d.sdk.anim\native\gen\CocoImageSibling.cpp \
D:\mobileFX\Projects\Software\Coconut\Projects\Coco.project\.SDK\Frameworks\org.coconut2d.sdk.anim\native\gen\CocoImage.cpp \
D:\mobileFX\Projects\Software\Coconut\Projects\Coco.project\.SDK\Frameworks\org.coconut2d.sdk.anim\native\gen\CocoEngine.cpp \
D:\mobileFX\Projects\Software\Coconut\Projects\Coco.project\.SDK\Frameworks\org.coconut2d.sdk.anim\native\gen\CocoClip.cpp \
D:\mobileFX\Projects\Software\Coconut\Projects\Coco.project\.SDK\Frameworks\org.coconut2d.sdk.anim\native\gen\CocoAudio.cpp \
D:\mobileFX\Projects\Software\Coconut\Projects\Coco.project\.SDK\DeviceWrappers\native\_Common\Fonts\fxFontFace.cpp \
D:\mobileFX\Projects\Software\Coconut\Projects\Coco.project\.SDK\DeviceWrappers\native\_Common\Fonts\CocoFont.cpp \
D:\mobileFX\Projects\Software\Coconut\Projects\Coco.project\.SDK\DeviceWrappers\native\_Common\Events\TouchList.cpp \
D:\mobileFX\Projects\Software\Coconut\Projects\Coco.project\.SDK\DeviceWrappers\native\_Common\Events\Touch.cpp \
D:\mobileFX\Projects\Software\Coconut\Projects\Coco.project\.SDK\DeviceWrappers\native\_Common\Events\EventTarget.cpp \
D:\mobileFX\Projects\Software\Coconut\Projects\Coco.project\.SDK\DeviceWrappers\native\_Common\Events\DeviceEvent.cpp \
D:\mobileFX\Projects\Software\Coconut\Projects\Coco.project\.SDK\DeviceWrappers\native\_Common\Coconut2D.cpp \
D:\mobileFX\Projects\Software\Coconut\Projects\Coco.project\.SDK\DeviceWrappers\native\_Common\Audio\fxAudioStream.cpp \
D:\mobileFX\Projects\Software\Coconut\Projects\Coco.project\.SDK\DeviceWrappers\native\_Common\Arrays\TypedArray.cpp \
D:\mobileFX\Projects\Software\Coconut\Projects\Coco.project\.SDK\DeviceWrappers\native\_Common\Arrays\ArrayBufferView.cpp \
D:\mobileFX\Projects\Software\Coconut\Projects\Coco.project\.SDK\DeviceWrappers\native\_Common\Arrays\ArrayBuffer.cpp

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
./assets/sounds/Background.ogg \
./assets/sounds/click_001.ogg \
./assets/images/icon.png \
./assets/images/metal_slug_mdpi.png \
./assets/images/metal_slug_xhdpi.png \
./assets/images/Sparrow.png \
./assets

#==============================================================================
VSCOMPILE 	= yes
NAME		= $(shell "$(IOSBUILDENV_PATH)/Toolchain/plconvert" "Info.plist" -query CFBundleExecutable)
PAYLOAD		= Payload
BIN			= bin
OUTDIR		= $(PAYLOAD)\$(NAME).app
CFLAGS		+= -DIOS_APPLICATION -DENABLE_OPENGL_SUPPORT -DENABLE_PNG_SUPPORT -DENABLE_JPG_SUPPORT -DENABLE_OGG_SUPPORT -DENABLE_OPENAL_SUPPORT -DENABLE_FREETYPE_SUPPORT -DENABLE_CURL_SUPPORT
CFLAGS		+= -O2 -W -Wall -Wno-sign-compare -Wno-delete-non-virtual-dtor -Wno-unused-function -Wno-unused-label -Wno-unused-parameter -Wno-unused-variable -Wunused-value -Wempty-body -Wuninitialized -x objective-c++ -std=gnu++11
CFLAGS		+= -target $(CPUSET)-apple-ios$(IOSMINVER).0.0 --sysroot "$(IOSBUILDENV_PATH)/SDK" -integrated-as -fdiagnostics-format=msvc -fconstant-cfstrings -miphoneos-version-min=$(IOSMINVER).0.0 -DIPHONE -D__IPHONE_OS_VERSION_MIN_REQUIRED=$(IOSMINVER)0000
LDFLAGS 	+= -lbz2 -lfreetype -lTremolo -lcurl -ljpeg -lz -lpng
LDFLAGS 	+= -ios_version_min $(IOSMINVER).0 -syslibroot "$(IOSBUILDENV_PATH)/SDK" -lSystem -lcrt1.o -lgcc_s.1 -lstdc++ -F"$(IOSBUILDENV_PATH)/SDK/System/Library/Frameworks" $(shell "$(IOSBUILDENV_PATH)/Toolchain/cat" "$(IOSBUILDENV_PATH)/Frameworks.iOS$(IOSMINVER)")
OBJDIR		= obj
OBJ			= $(addsuffix .obj, $(basename $(SRC)))
OBJ_OBJ		= $(addprefix $(OBJDIR)/, $(addsuffix .obj, $(basename $(notdir $(SRC)))))

#==============================================================================
compile:	prepare resources $(OBJ)

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
