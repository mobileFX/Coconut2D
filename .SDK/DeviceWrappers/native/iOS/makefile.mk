#==============================================================================
# iOS Build Makefile
#==============================================================================

CERTIFICATES = $(TARGETS.iOS.CODE_SIGNING.IOS_CERTIFICATES)
PRIVATE_KEY  = $(TARGETS.iOS.CODE_SIGNING.IOS_PRIVATE_KEY)
PASSPHRASE   = $(TARGETS.iOS.CODE_SIGNING.IOS_PRIVATE_KEY_PASSPHRASE)
PROVISION    = $(TARGETS.iOS.CODE_SIGNING.IOS_PROVISION)
IOSMINVER    = $(TARGETS.iOS.APP_SETTINGS.IOSMINVER)
CPUSET       = $(TARGETS.iOS.APP_SETTINGS.CPUSET)
LDFLAGS		 = -L$(PATH_SDK_LIBRARIES)/$(TARGET)

CFLAGS = $(NATIVE_CPP_INCLUDES)

SRC = $(NATIVE_CPP_SOURCES)

RES = $(NATIVE_RESOURCES)

#==============================================================================
VSCOMPILE 	= yes
NAME		= $(shell "$(IOSBUILDENV_PATH)/Toolchain/plconvert" "Info.plist" -query CFBundleExecutable)
PAYLOAD		= Payload
BIN			= bin
OUTDIR		= $(PAYLOAD)\$(NAME).app
CFLAGS		+= -DIOS_APPLICATION -DENABLE_OPENGL_SUPPORT -DENABLE_PNG_SUPPORT -DENABLE_JPG_SUPPORT -DENABLE_OGG_SUPPORT -DENABLE_OPENAL_SUPPORT -DENABLE_FREETYPE_SUPPORT -DENABLE_CURL_SUPPORT -DNGLDEBUG
CFLAGS		+= -O2 -w -x objective-c++ -std=c++11 -std=gnu++11
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
