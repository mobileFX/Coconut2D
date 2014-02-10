#==============================================================================
# iOS Build Makefile
#==============================================================================

CERTIFICATES = ios_development.cer:AppleIncRootCertificate.cer:AppleWWDRCA.cer
PRIVATE_KEY  = EliasPolitakis.key
PASSPHRASE   = puerre
PROVISION    = EliasPolitakisDevelopment.mobileprovision
IOSMINVER    = 5
CPUSET       = armv7
CFLAGS       =  -I../Common/SDK/CRL -I../Common/SDK/CRL/Audio -I../Common/SDK/CRL/Coconut2D/anim -I../Common/SDK/CRL/Coconut2D/game -I../Common/SDK/CRL/Fonts -I../Common/SDK/CRL/HTML5 -I../Common/SDK/Includes -I../Common/SDK/Includes/AL -I../Common/SDK/Includes/freetype -I../Common/SDK/Includes/freetype/config -I../Common/SDK/Includes/freetype/internal -I../Common/SDK/Includes/freetype/internal/services -I../Common/SDK/Includes/JavaScriptCore -I../Common/SDK/Includes/ogg -I../Common/SDK/Includes/tremor -I../Common/usr -I../Common/usr/animations -I../Common/SDK/DeviceWrappers/iOS
LDFLAGS      = -LD:/mobileFX/Projects/Software/Coconut/Projects/Coco.project/native/Common/SDK/Libraries/iOS
SRC          = ../Common/SDK/CRL/Audio/fxAudioStream.cpp ../Common/SDK/CRL/Coconut2D/anim/CocoAudio.cpp ../Common/SDK/CRL/Coconut2D/anim/CocoClip.cpp ../Common/SDK/CRL/Coconut2D/anim/CocoEngine.cpp ../Common/SDK/CRL/Coconut2D/anim/CocoImage.cpp ../Common/SDK/CRL/Coconut2D/anim/CocoImageSibling.cpp ../Common/SDK/CRL/Coconut2D/anim/CocoKeyFrame.cpp ../Common/SDK/CRL/Coconut2D/anim/CocoMatrix.cpp ../Common/SDK/CRL/Coconut2D/anim/CocoRect.cpp ../Common/SDK/CRL/Coconut2D/anim/CocoScene.cpp ../Common/SDK/CRL/Coconut2D/anim/CocoSequence.cpp ../Common/SDK/CRL/Coconut2D/anim/CocoTimeLabel.cpp ../Common/SDK/CRL/Coconut2D/anim/CocoTimeline.cpp ../Common/SDK/CRL/Coconut2D/anim/CocoVector.cpp ../Common/SDK/CRL/Coconut2D/game/CocoSprite.cpp ../Common/SDK/CRL/Coconut2D/game/CocoSpriteActor.cpp ../Common/SDK/CRL/Coconut2D/game/CocoSpriteBonus.cpp ../Common/SDK/CRL/Coconut2D/game/CocoSpriteBullet.cpp ../Common/SDK/CRL/Coconut2D/game/CocoSpriteEnemy.cpp ../Common/SDK/CRL/Coconut2D/game/CocoSpritePlayer.cpp ../Common/SDK/CRL/Coconut2D/game/CocoSpriteVisual.cpp ../Common/SDK/CRL/Coconut2D/game/CocoTiledLayer.cpp ../Common/SDK/CRL/Fonts/CocoFont.cpp ../Common/SDK/CRL/Fonts/fxFontFace.cpp ../Common/SDK/CRL/HTML5/ArrayBuffer.cpp ../Common/SDK/CRL/HTML5/ArrayBufferView.cpp ../Common/SDK/CRL/HTML5/CanvasRenderingContext2D.cpp ../Common/SDK/CRL/HTML5/DeviceEvent.cpp ../Common/SDK/CRL/HTML5/EventTarget.cpp ../Common/SDK/CRL/HTML5/HTMLAudioElement.cpp ../Common/SDK/CRL/HTML5/HTMLCanvasContext.cpp ../Common/SDK/CRL/HTML5/HTMLCanvasElement.cpp ../Common/SDK/CRL/HTML5/HTMLDocument.cpp ../Common/SDK/CRL/HTML5/HTMLElement.cpp ../Common/SDK/CRL/HTML5/HTMLEvent.cpp ../Common/SDK/CRL/HTML5/HTMLImageElement.cpp ../Common/SDK/CRL/HTML5/HTMLWindow.cpp ../Common/SDK/CRL/HTML5/Touch.cpp ../Common/SDK/CRL/HTML5/TouchList.cpp ../Common/SDK/CRL/HTML5/TypedArray.cpp ../Common/SDK/CRL/HTML5/WebGLRenderingContext.cpp ../Common/usr/GameEngine.cpp ../Common/usr/animations/BitmapSymbolsTest.cpp ../Common/usr/animations/SynthesisTest.cpp ../Common/usr/animations/Test.cpp ../Common/usr/animations/TestSequences.cpp ../Common/usr/animations/TestText.cpp ../Common/SDK/DeviceWrappers/iOS/fxDeviceWrapper.m ../Common/SDK/DeviceWrappers/iOS/fxGLWrap.m ../Common/SDK/DeviceWrappers/iOS/fxKeyWrap.m ../Common/SDK/DeviceWrappers/iOS/main.m
RES          = Icon-29.png Icon-29@2x.png Icon-40.png Icon-40@2x.png Icon-60.png Icon-60@2x.png Icon-72.png Icon-72@2x.png Icon-76.png Icon-76@2x.png Icon-Small-50.png Icon-Small-50@2x.png Icon-Small.png Icon-Small@2x.png Icon.png Icon@2x.png Info.plist iTunesArtwork.png iTunesArtwork@2x.png "web"

#==============================================================================
VSCOMPILE 	= yes
NAME		= $(shell "$(IOSBUILDENV_PATH)/Toolchain/plconvert" "Info.plist" -query CFBundleExecutable)
OUTDIR		= $(NAME).app
CFLAGS		+= -DIOS_APPLICATION -DENABLE_OPENGL_SUPPORT -DENABLE_PNG_SUPPORT -DENABLE_JPG_SUPPORT -DENABLE_OGG_SUPPORT -DENABLE_OPENAL_SUPPORT -DENABLE_FREETYPE_SUPPORT -DENABLE_CURL_SUPPORT
CFLAGS		+= -O2 -W -Wall -Wno-delete-non-virtual-dtor -Wno-unused-function -Wno-unused-label -Wno-unused-parameter -Wno-unused-variable -Wunused-value -Wempty-body -Wuninitialized -x objective-c++ -std=gnu++11
CFLAGS		+= -target $(CPUSET)-apple-ios$(IOSMINVER).0.0 --sysroot "$(IOSBUILDENV_PATH)/SDK" -integrated-as -fdiagnostics-format=msvc -fconstant-cfstrings -miphoneos-version-min=$(IOSMINVER).0.0 -DIPHONE -D__IPHONE_OS_VERSION_MIN_REQUIRED=$(IOSMINVER)0000
LDFLAGS 	+= -lbz2 -lfreetype -lTremolo -lcurl -ljpeg -lz -lpng
LDFLAGS 	+= -ios_version_min $(IOSMINVER).0 -syslibroot "$(IOSBUILDENV_PATH)/SDK" -lSystem -lcrt1.o -lgcc_s.1 -lstdc++ -F"$(IOSBUILDENV_PATH)/SDK/System/Library/Frameworks" $(shell "$(IOSBUILDENV_PATH)/Toolchain/cat" "$(IOSBUILDENV_PATH)/Frameworks.iOS$(IOSMINVER)")
OBJDIR		= obj
OBJ			= $(addsuffix .obj, $(basename $(SRC)))
OBJ_OBJ		= $(addprefix $(OBJDIR)/, $(addsuffix .obj, $(basename $(notdir $(SRC)))))

#==============================================================================
all:	clean compile $(OBJ) link resources codesign ipa end

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
	@"$(IOSBUILDENV_PATH)/Toolchain/mkdir" "$(OUTDIR)"
	@"$(IOSBUILDENV_PATH)/Toolchain/ld" $(LDFLAGS) -o "$(OUTDIR)/$(NAME)" $(OBJ_OBJ)

#==============================================================================
# The following rule takes all the specified resource items one after the
# other (whether they are files or directories) ; files are copied in place
# and directories are recursively copied only if their content changed.
# During this process, all property lists are converted in binary format.
#==============================================================================
resources:
	@"$(IOSBUILDENV_PATH)/Toolchain/echo" "Copying resources ..."
	@"$(IOSBUILDENV_PATH)/Toolchain/mkdir" "$(OUTDIR)"
ifeq (cmd.exe,$(findstring cmd.exe,$(ComSpec)))
	@for %%I in ($(RES)) do ( \
	   if "%%I"=="Info.plist" ( \
	      "$(IOSBUILDENV_PATH)/Toolchain/plconvert" "%%I" "$(OUTDIR)/%%I" -binary -LSRequiresIPhoneOS=bool:true -CFBundleSupportedPlatforms=array:{string}iPhoneOS{/string} -MinimumOSVersion=string:$(IOSMINVER).0 \
	   ) else ( \
	      "$(IOSBUILDENV_PATH)/Toolchain/copy" "%%I" "$(OUTDIR)/%%I" \
	   ) \
	)
else
	@for item in $(RES); do \
	   if [ "$$item" = "Info.plist" ]; then \
	      "$(IOSBUILDENV_PATH)/Toolchain/plconvert" "$$item" "$(OUTDIR)/$$item" -binary -LSRequiresIPhoneOS=bool:true -CFBundleSupportedPlatforms=array:{string}iPhoneOS{/string} -MinimumOSVersion=string:$(IOSMINVER).0 ; \
	   else \
	      "$(IOSBUILDENV_PATH)/Toolchain/copy" "$$item" "$(OUTDIR)"; \
	   fi; \
	done
endif
	@"$(IOSBUILDENV_PATH)/Toolchain/plconvert" "Info.plist" -query CFBundlePackageType > "$(OUTDIR)/PkgInfo"
	@"$(IOSBUILDENV_PATH)/Toolchain/plconvert" "Info.plist" -query CFBundleSignature >> "$(OUTDIR)/PkgInfo"

#==============================================================================
# The following rule generates the SHA1 checksums for the resource files, then
# insert a code signature blob in the binary, seals the binary code, resources
# and Info.plist and sign it with the specified application identifier.
#==============================================================================
codesign:
	@"$(IOSBUILDENV_PATH)/Toolchain/echo" "Signing code ..."
	@"$(IOSBUILDENV_PATH)/Toolchain/mkdir" "$(OUTDIR)"
	@"$(IOSBUILDENV_PATH)/Toolchain/copy" "$(PROVISION)" "$(OUTDIR)/embedded.mobileprovision"
	@"$(IOSBUILDENV_PATH)/Toolchain/ldid" -k"$(IOSBUILDENV_PATH)/Keychain" -S$(CERTIFICATES):$(PRIVATE_KEY):$(PASSPHRASE) -C -E -I "$(OUTDIR)/$(NAME)"

#==============================================================================
# The following rule builds an IPA bundle out of the compiled app directory.
#==============================================================================
ipa:
	@"$(IOSBUILDENV_PATH)/Toolchain/echo" "Building iTunes package ..."
	@"$(IOSBUILDENV_PATH)/Toolchain/mkdir" "Packages" "Payload"
	@"$(IOSBUILDENV_PATH)/Toolchain/unlink" "Packages/$(NAME).ipa"
	@"$(IOSBUILDENV_PATH)/Toolchain/move" "$(OUTDIR)" "Payload"
	@"$(IOSBUILDENV_PATH)/Toolchain/copy" "iTunesArtwork.jpg" "iTunesArtwork"
	@"$(IOSBUILDENV_PATH)/Toolchain/zip" -q -r "Packages/$(NAME).ipa" "Payload" "iTunesArtwork" -x \*.log \*.lastbuildstate \*successfulbuild
	@"$(IOSBUILDENV_PATH)/Toolchain/unlink" "iTunesArtwork"
	@"$(IOSBUILDENV_PATH)/Toolchain/move" "Payload/$(OUTDIR)" "."
	@"$(IOSBUILDENV_PATH)/Toolchain/unlink" "Payload"

#==============================================================================
# This simple rule displays the success message after a successful build
#==============================================================================
end:

#==============================================================================
# This rule removes generated object files from the project
#==============================================================================
clean:
	@"$(IOSBUILDENV_PATH)/Toolchain/echo" "Cleaning iOS Project ..."
	@"$(IOSBUILDENV_PATH)/Toolchain/unlink" *.log *.lastbuildstate *.successfulbuild *.unsuccessfulbuild
	@"$(IOSBUILDENV_PATH)/Toolchain/unlink" "$(OUTDIR)"
	@"$(IOSBUILDENV_PATH)/Toolchain/mkdir" "$(OBJDIR)"

compile:
	@"$(IOSBUILDENV_PATH)/Toolchain/echo" "Compiling iOS Project ..."

#==============================================================================
# This rule removes all generated output from any previous builds so as to
# leave an intact source tree (useful for generating source tree releases).
#==============================================================================
distclean: clean
	@"$(IOSBUILDENV_PATH)/Toolchain/echo" "Cleaning project output files ..."
	@"$(IOSBUILDENV_PATH)/Toolchain/unlink" "$(OUTDIR)" "Packages" *.ncb *.suo *.pdb *.sdf *.sln *.user "BuildLog.htm"
