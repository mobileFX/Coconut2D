#==============================================================================
# iOS Build Makefile
#==============================================================================

CERTIFICATES = EliasPolitakis.cer:AppleIncRootCertificate.cer:AppleWWDRCA.cer
PRIVATE_KEY  = EliasPolitakis.key
PASSPHRASE   = puerre
PROVISION    = EliasPolitakis.mobileprovision
IOSMINVER    = 5
CPUSET       = armv7
CFLAGS       = -O2 -W -Wall -Wdelete-non-virtual-dtor -Wno-unused-function -Wno-unused-label -Wno-unused-parameter -Wno-unused-variable -Wunused-value -Wempty-body -Wuninitialized -x objective-c++ -std=gnu++11 -DIOS_APPLICATION -DENABLE_OPENGL_SUPPORT -DENABLE_PNG_SUPPORT -DENABLE_JPG_SUPPORT -DENABLE_OGG_SUPPORT -DENABLE_OPENAL_SUPPORT -DENABLE_FREETYPE_SUPPORT -DENABLE_CURL_SUPPORT -I"src" -I"../Common" -I"../Common/Audio_API" -I"../Common/Coconut2D" -I"../Common/Coconut2D/anim" -I"../Common/Coconut2D/game" -I"../Common/Fonts_API" -I"../Common/HTML5" -I"../Common/usr" -I"../Common/usr/animations" -I"../Include" -I"../Include/AL" -I"../Include/freetype" -I"../Include/freetype/config" -I"../Include/freetype/internal" -I"../Include/freetype/internal/services" -I"../Include/JavaScriptCore" -I"../Include/ogg" -I"../Include/tremor"
LDFLAGS      = -LD:/mobileFX/Projects/Software/Coconut/Projects/Coco.project/native/Libraries/iOS -lbz2 -lfreetype -lTremolo -lcurl -ljpeg -lz -lpng
SRC          = src/fxDeviceWrapper.m src/fxGLWrap.m src/fxKeyWrap.m src/main.m ../Common/Audio_API/fxAudioStream.cpp ../Common/Coconut2D/anim/CocoAudio.cpp ../Common/Coconut2D/anim/CocoClip.cpp ../Common/Coconut2D/anim/CocoEngine.cpp ../Common/Coconut2D/anim/CocoImage.cpp ../Common/Coconut2D/anim/CocoImageSibling.cpp ../Common/Coconut2D/anim/CocoKeyFrame.cpp ../Common/Coconut2D/anim/CocoMatrix.cpp ../Common/Coconut2D/anim/CocoRect.cpp ../Common/Coconut2D/anim/CocoScene.cpp ../Common/Coconut2D/anim/CocoSequence.cpp ../Common/Coconut2D/anim/CocoSound.cpp ../Common/Coconut2D/anim/CocoTimeLabel.cpp ../Common/Coconut2D/anim/CocoTimeline.cpp ../Common/Coconut2D/anim/CocoVector.cpp ../Common/Coconut2D/game/CocoSprite.cpp ../Common/Coconut2D/game/CocoSpriteActor.cpp ../Common/Coconut2D/game/CocoSpriteBonus.cpp ../Common/Coconut2D/game/CocoSpriteBullet.cpp ../Common/Coconut2D/game/CocoSpriteEnemy.cpp ../Common/Coconut2D/game/CocoSpritePlayer.cpp ../Common/Coconut2D/game/CocoSpriteVisual.cpp ../Common/Coconut2D/game/CocoTiledLayer.cpp ../Common/Fonts_API/CocoFont.cpp ../Common/Fonts_API/fxFontFace.cpp ../Common/HTML5/ArrayBuffer.cpp ../Common/HTML5/ArrayBufferView.cpp ../Common/HTML5/CanvasRenderingContext2D.cpp ../Common/HTML5/DeviceEvent.cpp ../Common/HTML5/EventTarget.cpp ../Common/HTML5/HTMLAudioElement.cpp ../Common/HTML5/HTMLCanvasContext.cpp ../Common/HTML5/HTMLCanvasElement.cpp ../Common/HTML5/HTMLDocument.cpp ../Common/HTML5/HTMLElement.cpp ../Common/HTML5/HTMLEvent.cpp ../Common/HTML5/HTMLImageElement.cpp ../Common/HTML5/HTMLWindow.cpp ../Common/HTML5/Touch.cpp ../Common/HTML5/TouchList.cpp ../Common/HTML5/TypedArray.cpp ../Common/HTML5/WebGLRenderingContext.cpp ../Common/usr/GameEngine.cpp ../Common/usr/animations/BitmapSymbolsTest.cpp ../Common/usr/animations/SynthesisTest.cpp ../Common/usr/animations/Test.cpp ../Common/usr/animations/TestSequences.cpp
RES          = "web"

#==============================================================================
VSCOMPILE 	= yes
NAME		= $(shell "$(IOSBUILDENV_PATH)/Toolchain/plconvert" "Info.plist" -query CFBundleExecutable)
OUTDIR		= $(NAME).app
CFLAGS		+= -target $(CPUSET)-apple-ios$(IOSMINVER).0.0 --sysroot "$(IOSBUILDENV_PATH)/SDK" -integrated-as -fdiagnostics-format=msvc -fconstant-cfstrings -miphoneos-version-min=$(IOSMINVER).0.0 -DIPHONE -D__IPHONE_OS_VERSION_MIN_REQUIRED=$(IOSMINVER)0000
LDFLAGS 	+= -ios_version_min $(IOSMINVER).0 -syslibroot "$(IOSBUILDENV_PATH)/SDK" -lSystem -lcrt1.o -lgcc_s.1 -lstdc++ -F"$(IOSBUILDENV_PATH)/SDK/System/Library/Frameworks" $(shell "$(IOSBUILDENV_PATH)/Toolchain/cat" "$(IOSBUILDENV_PATH)/Frameworks.iOS$(IOSMINVER)")
OBJ			= $(addsuffix .obj, $(basename $(SRC)))

#==============================================================================
all:	prune $(OBJ) link ddb resources codesign ipa end

#==============================================================================
# Clean
#==============================================================================
prune:
	@"$(IOSBUILDENV_PATH)/Toolchain/echo" "Pruning compilation results ..."
	@"$(IOSBUILDENV_PATH)/Toolchain/unlink" "$(OUTDIR)"

#==============================================================================
# Compile C/C++ and Objective-C files
#==============================================================================
%.obj:	%.c
	@"$(IOSBUILDENV_PATH)/Toolchain/echo" " + Compiling $< ..."
	@"$(IOSBUILDENV_PATH)/Toolchain/clang" $(CFLAGS) -o "$@" -c "$<"
%.obj:	%.cc
	@"$(IOSBUILDENV_PATH)/Toolchain/echo" " + Compiling $< ..."
	@"$(IOSBUILDENV_PATH)/Toolchain/clang" $(CFLAGS) -o "$@" -c "$<"
%.obj:	%.cpp
	@"$(IOSBUILDENV_PATH)/Toolchain/echo" " + Compiling $< ..."
	@"$(IOSBUILDENV_PATH)/Toolchain/clang" $(CFLAGS) -o "$@" -c "$<"
%.obj:	%.cxx
	@"$(IOSBUILDENV_PATH)/Toolchain/echo" " + Compiling $< ..."
	@"$(IOSBUILDENV_PATH)/Toolchain/clang" $(CFLAGS) -o "$@" -c "$<"
%.obj:	%.m
	@"$(IOSBUILDENV_PATH)/Toolchain/echo" " + Compiling $< ..."
	@"$(IOSBUILDENV_PATH)/Toolchain/clang" $(CFLAGS) -o "$@" -c "$<"
%.obj:	%.mm
	@"$(IOSBUILDENV_PATH)/Toolchain/echo" " + Compiling $< ..."
	@"$(IOSBUILDENV_PATH)/Toolchain/clang" $(CFLAGS) -o "$@" -c "$<"
%.obj:	%.mx
	@"$(IOSBUILDENV_PATH)/Toolchain/echo" " + Compiling $< ..."
	@"$(IOSBUILDENV_PATH)/Toolchain/clang" $(CFLAGS) -o "$@" -c "$<"
%.obj:	%.mxx
	@"$(IOSBUILDENV_PATH)/Toolchain/echo" " + Compiling $< ..."
	@"$(IOSBUILDENV_PATH)/Toolchain/clang" $(CFLAGS) -o "$@" -c "$<"
%.obj:	%.s
	@"$(IOSBUILDENV_PATH)/Toolchain/echo" " + Assembling $< ..."
	@"$(IOSBUILDENV_PATH)/Toolchain/clang" $(CFLAGS) -o "$@" -c "$<"

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
	@"$(IOSBUILDENV_PATH)/Toolchain/ld" $(LDFLAGS) -o "$(OUTDIR)/$(NAME)" $(OBJ)

#==============================================================================
# The following rule creates a debug database out of the source & object files
# if a -g (debug) flag is present in the compiler's command line arguments
#==============================================================================
ddb:
ifeq (-g,$(findstring -g,$(CFLAGS)))
	@"$(IOSBUILDENV_PATH)/Toolchain/echo" "Creating debug database ..."
	@"$(IOSBUILDENV_PATH)/Toolchain/mkdir" "$(OUTDIR)/$(NAME).DEBUG"
ifeq (cmd.exe,$(findstring cmd.exe,$(ComSpec)))
	@for %%I in ($(dir $(SRC))) do ("$(IOSBUILDENV_PATH)/Toolchain/mkdir" "$(OUTDIR)/$(NAME).DEBUG/src/%%I")
	@for %%I in ($(dir $(OBJ))) do ("$(IOSBUILDENV_PATH)/Toolchain/mkdir" "$(OUTDIR)/$(NAME).DEBUG/obj/%%I")
	@for %%I in ($(SRC)) do ("$(IOSBUILDENV_PATH)/Toolchain/copy" "%%I" "$(OUTDIR)/$(NAME).DEBUG/src/%%I")
	@for %%I in ($(OBJ)) do ("$(IOSBUILDENV_PATH)/Toolchain/copy" "%%I" "$(OUTDIR)/$(NAME).DEBUG/obj/%%I")
else
	@for item in $(dir $(SRC)); do "$(IOSBUILDENV_PATH)/Toolchain/mkdir" "$(OUTDIR)/$(NAME).DEBUG/src/$$item"; done
	@for item in $(dir $(OBJ)); do "$(IOSBUILDENV_PATH)/Toolchain/mkdir" "$(OUTDIR)/$(NAME).DEBUG/obj/$$item"; done
	@for item in $(SRC); do "$(IOSBUILDENV_PATH)/Toolchain/copy" "$$item" "$(OUTDIR)/$(NAME).DEBUG/src/$$item"; done
	@for item in $(OBJ); do "$(IOSBUILDENV_PATH)/Toolchain/copy" "$$item" "$(OUTDIR)/$(NAME).DEBUG/obj/$$item"; done
endif
	@"$(IOSBUILDENV_PATH)/Toolchain/otool" -l "$(OUTDIR)/$(NAME)" > "$(OUTDIR)/$(NAME).DEBUG/loadcmds"
ifeq (armv7s,$(CPUSET))
	@"$(IOSBUILDENV_PATH)/Toolchain/echo" -n "DarwinV7S" > "$(OUTDIR)/$(NAME).DEBUG/abi"
else ifeq (armv7f,$(CPUSET))
	@"$(IOSBUILDENV_PATH)/Toolchain/echo" -n "DarwinV7F" > "$(OUTDIR)/$(NAME).DEBUG/abi"
else ifeq (armv7,$(CPUSET))
	@"$(IOSBUILDENV_PATH)/Toolchain/echo" -n "DarwinV7" > "$(OUTDIR)/$(NAME).DEBUG/abi"
else
	@"$(IOSBUILDENV_PATH)/Toolchain/echo" -n "DarwinV6" > "$(OUTDIR)/$(NAME).DEBUG/abi"
endif
endif

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
	@"$(IOSBUILDENV_PATH)/Toolchain/echo" "Cleaning intermediate files ..."
	@"$(IOSBUILDENV_PATH)/Toolchain/unlink" $(OBJ) *.log *.lastbuildstate *.successfulbuild *.unsuccessfulbuild

#==============================================================================
# This rule removes all generated output from any previous builds so as to
# leave an intact source tree (useful for generating source tree releases).
#==============================================================================
distclean: clean
	@"$(IOSBUILDENV_PATH)/Toolchain/echo" "Cleaning project output files ..."
	@"$(IOSBUILDENV_PATH)/Toolchain/unlink" "$(OUTDIR)" "Packages" *.ncb *.suo *.pdb *.sdf *.sln *.user "BuildLog.htm"
