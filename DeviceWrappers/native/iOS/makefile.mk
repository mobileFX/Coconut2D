#==============================================================================
# iOS Build Makefile
#==============================================================================

CERTIFICATES = $(TARGETS.iOS.CODE_SIGNING.IOS_CERTIFICATES)
PRIVATE_KEY  = $(TARGETS.iOS.CODE_SIGNING.IOS_PRIVATE_KEY)
PASSPHRASE   = $(TARGETS.iOS.CODE_SIGNING.IOS_PRIVATE_KEY_PASSPHRASE)
PROVISION    = $(TARGETS.iOS.CODE_SIGNING.IOS_PROVISION)
IOSMINVER    = $(TARGETS.iOS.APP_SETTINGS.IOSMINVER)
CPUSET       = $(TARGETS.iOS.APP_SETTINGS.CPUSET)

# Link Libraries Binary Paths
LDFLAGS	= $(APP_LDFLAGS)

# Compiler options and Include Paths (Libraries, Frameworkds, Sources)
CFLAGS = $(APP_CFLAGS)

# Source files to compile
SRC = $(NATIVE_CPP_SOURCES)

# Resources to embed
RES = $(NATIVE_RESOURCES)

#==============================================================================
#http://marshall.calepin.co/llvmclang-and-standard-libraries-on-mac-os-x.html
#http://libcxx.llvm.org/
#==============================================================================
VSCOMPILE 	= yes
NAME		= $(shell "$(IOSBUILDENV_PATH)/Toolchain/plconvert" "Info.plist" -query CFBundleExecutable)
PAYLOAD		= Payload
BIN			= bin
OUTDIR		= $(PAYLOAD)\$(NAME).app
CFLAGS		+= -DIOS_APPLICATION
CFLAGS		+= -g -O0 -DDEBUG=1
CFLAGS		+= -x objective-c++ -std=c++11 -stdlib=libc++ -I $(IOSBUILDENV_PATH)/SDK/lib/c++/v1
CFLAGS      += -frtti -fmessage-length=0 -fdiagnostics-show-note-include-stack -fpascal-strings -fexceptions -fasm-blocks -fstrict-aliasing -fvisibility-inlines-hidden -fobjc-abi-version=2 -fmacro-backtrace-limit=0
CFLAGS		+= -target $(CPUSET)-apple-ios$(IOSMINVER).0.0 --sysroot "$(IOSBUILDENV_PATH)/SDK" -integrated-as -fdiagnostics-format=msvc -fconstant-cfstrings -miphoneos-version-min=$(IOSMINVER).0.0 -DIPHONE -D__IPHONE_OS_VERSION_MIN_REQUIRED=$(IOSMINVER)0000
LDFLAGS 	+= -lc++ -lc++abi -lm -lc -lbz2 $(APP_LDLIBS)
LDFLAGS 	+= -ios_version_min $(IOSMINVER).0 -syslibroot "$(IOSBUILDENV_PATH)/SDK" -lSystem -lcrt1.o -lgcc_s.1 -lstdc++ -F"$(IOSBUILDENV_PATH)/SDK/System/Library/Frameworks" $(shell "$(IOSBUILDENV_PATH)/Toolchain/cat" "$(IOSBUILDENV_PATH)/Frameworks.iOS$(IOSMINVER)")
OBJ			= obj
OBJS		= $(addsuffix .obj, $(basename $(SRC)))
OBJ_OBJ		= $(addprefix $(OBJ)/, $(addsuffix .obj, $(basename $(notdir $(SRC)))))

$(foreach o,$(SRC),$(eval $(addprefix $(OBJ)/, $(addsuffix .obj, $(basename $(notdir $o)))) = $o))

#==============================================================================
compile:	$(OBJ_OBJ)

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
	@"$(IOSBUILDENV_PATH)/Toolchain/mkdir" "$(OBJ)"
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
%.obj:
	@"$(IOSBUILDENV_PATH)/Toolchain/echo" " + Compiling $($@) ..."
	@"$(IOSBUILDENV_PATH)/Toolchain/clang" $(CFLAGS) -o "$@" -c "$($@)"

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

