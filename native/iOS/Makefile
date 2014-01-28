#############################################################################
# Makefile for iPhone application
#############################################################################
# Required variables:                                                         #
# $CERTIFICATES - Colon-separated list of certs to embed in the app signature #
# $PRIVATE_KEY - Signer's private key filename                                #
# $PASSPHRASE - Optional signer's private key passphrase                      #
# $PROVISION - Filename of the provisioning profile to embed in the bundle    #
# $IOSMINVER - Major version of the SDK against which this program was built  #
# $CPUSET - CPU instruction set to use                                        #
# $RES - Application bundle's resource files                                  #
# $CFLAGS - Compiler flags                                                    #
# $LDFLAGS - Linker flags                                                     #
###############################################################################

# Define here which certificates to embed in the app's digital signature, and
# the private key (and optionally its passphrase) to use to sign it. Those
# files may be either in the Keychain directory or in the project directory.
# The certificates should typically include your own developer certificate,
# then the certificate of the organization which granted it to you, then the
# certificate of the organization which issued it, and so on, until the root
# certificate of the top-level authority, on top of the trust chain.
# You can also specify a provisioning profile to embed in the app's bundle.
# Separate each certificate filename with a colon (:).

CERTIFICATES = EliasPolitakis.cer:AppleIncRootCertificate.cer:AppleWWDRCA.cer
PRIVATE_KEY  = EliasPolitakis.key
PASSPHRASE   = puerre
PROVISION    = EliasPolitakis.mobileprovision

# Define here the minimal iOS version's MAJOR number (iOS3, iOS4 or iOS5)
IOSMINVER = 3

# Define here the CPU instruction set to use (armv6, armv7, armv7f or armv7s)
# The armv6 instruction set is used in old devices, prior to the iPhone 3GS.
# The armv7 set extends the armv6 and is used in all modern iOS devices.
# The armv7f set adds dual-core instructions to armv7 for Apple A5 devices.
# The armv7s set adds integer division optimizations for Apple A6 devices.
CPUSET = armv6

# List here your project's resource files. They can be files or directories.
# Typical iOS apps needs at least an Info.plist, and an icon.
RES     = Info.plist icon.png

# Define here the compile options and the linker options for your project.
# These flags are compatible with GCC, see the GCC documentation for details.
# If you want debug symbols to use with gdb, replace "-O2" with "-O0 -g".
CFLAGS  = -W -Wall -O2
LDFLAGS = 

# Define here the name of the project's main executable, and the name of the
# build directory where the generated binaries and resources will go. Here,
# we extract the executable name from the Info.plist.
NAME	= $(shell "$(IOSBUILDENV_PATH)/Toolchain/plconvert" "Info.plist" -query CFBundleExecutable)
OUTDIR	= bin/$(NAME).app

# Define what are the necessary common compiler and linker options to build
# for the iOS platform. Here, tell the ARM cross-compiler to target the
# specified arm-apple-ios platform triplet, specify the location of the header
# files, use the compiler's integrated assembler, and set up the required
# preprocessor definitions. Tell the linker about the minimal supported iOS
# version, specify the location of the libraries and frameworks, and include
# explicitly libSystem.dylib, crt1.o, libgcc_s.1.dylib and the standard C++
# library in the linkage. Also include all available frameworks.
CFLAGS	+= -target $(CPUSET)-apple-ios$(IOSMINVER).0.0 --sysroot "$(IOSBUILDENV_PATH)/SDK" -integrated-as -fdiagnostics-format=msvc -fconstant-cfstrings -miphoneos-version-min=$(IOSMINVER).0.0 -DIPHONE -D__IPHONE_OS_VERSION_MIN_REQUIRED=$(IOSMINVER)0000
LDFLAGS += -ios_version_min $(IOSMINVER).0 -syslibroot "$(IOSBUILDENV_PATH)/SDK" -lSystem -lcrt1.o -lgcc_s.1 -lstdc++ -F"$(IOSBUILDENV_PATH)/SDK/System/Library/Frameworks" $(shell "$(IOSBUILDENV_PATH)/Toolchain/cat" "$(IOSBUILDENV_PATH)/Frameworks.iOS$(IOSMINVER)")

# Define what are the source files. The current rule relies on an external
# program to build that list for us. This program detects if we're running
# from Visual Studio; if so, we extract the list of the source files from the
# Visual Studio project file, else it builds a one-liner list of all C files
# in the project directory.
SRC	= $(shell "$(IOSBUILDENV_PATH)/Toolchain/list-source-files" "$(NAME)" "Source Files")

# Define where the object files should go - currently, just aside the source
# files themselves. We take the source file's basename and just append .obj.
OBJ	= $(addsuffix .obj, $(basename $(SRC)))

###################
# Rules definitions

# This rule is the default rule that is called when you type "make". It runs
# the specified other rules in that order: removing generated output from
# previous builds, compiling all source files into object files, linking them
# all together, copying resources in place, codesigning the resulting bundle,
# packaging it in two fashions, and then displaying a success message.
all:	prune $(OBJ) link ddb resources codesign ipa deb end

# The following rule removes the generated output from any previous builds
prune:
	@"$(IOSBUILDENV_PATH)/Toolchain/echo" " + Pruning compilation results..."
	@"$(IOSBUILDENV_PATH)/Toolchain/unlink" "$(OUTDIR)"

# The following rules compile any .c/.cc/.cpp/.cxx/.m/.mm/.mx/.mxx file it
# finds in object files (.obj). This is to handle source files in different
# languages: C/C++ (with .c* extension), and Objective-C (.m*).
%.obj:	%.c
	@"$(IOSBUILDENV_PATH)/Toolchain/echo" " + Compiling $<..."
	@"$(IOSBUILDENV_PATH)/Toolchain/clang" $(CFLAGS) -o "$@" -c "$<"
%.obj:	%.cc
	@"$(IOSBUILDENV_PATH)/Toolchain/echo" " + Compiling $<..."
	@"$(IOSBUILDENV_PATH)/Toolchain/clang" $(CFLAGS) -o "$@" -c "$<"
%.obj:	%.cpp
	@"$(IOSBUILDENV_PATH)/Toolchain/echo" " + Compiling $<..."
	@"$(IOSBUILDENV_PATH)/Toolchain/clang" $(CFLAGS) -o "$@" -c "$<"
%.obj:	%.cxx
	@"$(IOSBUILDENV_PATH)/Toolchain/echo" " + Compiling $<..."
	@"$(IOSBUILDENV_PATH)/Toolchain/clang" $(CFLAGS) -o "$@" -c "$<"
%.obj:	%.m
	@"$(IOSBUILDENV_PATH)/Toolchain/echo" " + Compiling $<..."
	@"$(IOSBUILDENV_PATH)/Toolchain/clang" $(CFLAGS) -o "$@" -c "$<"
%.obj:	%.mm
	@"$(IOSBUILDENV_PATH)/Toolchain/echo" " + Compiling $<..."
	@"$(IOSBUILDENV_PATH)/Toolchain/clang" $(CFLAGS) -o "$@" -c "$<"
%.obj:	%.mx
	@"$(IOSBUILDENV_PATH)/Toolchain/echo" " + Compiling $<..."
	@"$(IOSBUILDENV_PATH)/Toolchain/clang" $(CFLAGS) -o "$@" -c "$<"
%.obj:	%.mxx
	@"$(IOSBUILDENV_PATH)/Toolchain/echo" " + Compiling $<..."
	@"$(IOSBUILDENV_PATH)/Toolchain/clang" $(CFLAGS) -o "$@" -c "$<"
%.obj:	%.s
	@"$(IOSBUILDENV_PATH)/Toolchain/echo" " + Assembling $<..."
	@"$(IOSBUILDENV_PATH)/Toolchain/clang" $(CFLAGS) -o "$@" -c "$<"

# Hack: static libs are treated like source files, except that they aren't
# compiled but just copied to .obj. The linker will figure out what to do.
%.obj:	%.a
	@"$(IOSBUILDENV_PATH)/Toolchain/echo" " + Using static library or framework: $<..."
	@"$(IOSBUILDENV_PATH)/Toolchain/copy" "$<" "$@"

# The following rule first ensures the output directory exists, creates it if
# necessary, then links the compiled .obj files together in that directory
link:
	@"$(IOSBUILDENV_PATH)/Toolchain/echo" " + Linking project files..."
	@"$(IOSBUILDENV_PATH)/Toolchain/mkdir" "$(OUTDIR)"
	@"$(IOSBUILDENV_PATH)/Toolchain/ld" $(LDFLAGS) -o "$(OUTDIR)/$(NAME)" $(OBJ)

# The following rule creates a debug database out of the source & object files
# if a -g (debug) flag is present in the compiler's command line arguments
ddb:
ifeq (-g,$(findstring -g,$(CFLAGS)))
	@"$(IOSBUILDENV_PATH)/Toolchain/echo" " + Creating debug database..."
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

# The following rule takes all the specified resource items one after the
# other (whether they are files or directories) ; files are copied in place
# and directories are recursively copied only if their content changed.
# During this process, all property lists are converted in binary format.
resources:
	@"$(IOSBUILDENV_PATH)/Toolchain/echo" " + Copying resources..."
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

# The following rule generates the SHA1 checksums for the resource files, then
# insert a code signature blob in the binary, seals the binary code, resources
# and Info.plist and sign it with the specified application identifier.
codesign:
	@"$(IOSBUILDENV_PATH)/Toolchain/echo" " + Signing code..."
	@"$(IOSBUILDENV_PATH)/Toolchain/mkdir" "$(OUTDIR)"
	@"$(IOSBUILDENV_PATH)/Toolchain/copy" "$(PROVISION)" "$(OUTDIR)/embedded.mobileprovision"
	@"$(IOSBUILDENV_PATH)/Toolchain/ldid" -k"$(IOSBUILDENV_PATH)/Keychain" -S$(CERTIFICATES):$(PRIVATE_KEY):$(PASSPHRASE) -C -E -I "$(OUTDIR)/$(NAME)"

# The following rule builds an IPA bundle out of the compiled app directory.
ipa:
	@"$(IOSBUILDENV_PATH)/Toolchain/echo" " + Building iTunes package..."
	@"$(IOSBUILDENV_PATH)/Toolchain/mkdir" "Packages" "Payload"
	@"$(IOSBUILDENV_PATH)/Toolchain/unlink" "Packages/$(NAME).ipa"
	@"$(IOSBUILDENV_PATH)/Toolchain/move" "$(OUTDIR)" "Payload"
	@"$(IOSBUILDENV_PATH)/Toolchain/copy" "iTunesArtwork.jpg" "iTunesArtwork"
	@"$(IOSBUILDENV_PATH)/Toolchain/zip" -q -r "Packages/$(NAME).ipa" "Payload" "iTunesArtwork" -x \*.log \*.lastbuildstate \*successfulbuild
	@"$(IOSBUILDENV_PATH)/Toolchain/unlink" "iTunesArtwork"
	@"$(IOSBUILDENV_PATH)/Toolchain/move" "Payload/$(OUTDIR)" "."
	@"$(IOSBUILDENV_PATH)/Toolchain/unlink" "Payload"

# The following rule builds a Cydia package out of the compiled app directory.
deb:
	@"$(IOSBUILDENV_PATH)/Toolchain/echo" " + Building Cydia package..."
	@"$(IOSBUILDENV_PATH)/Toolchain/mkdir" "Packages" "$(NAME)/DEBIAN" "$(NAME)/Applications"
	@"$(IOSBUILDENV_PATH)/Toolchain/unlink" "Packages/$(NAME).deb" "$(NAME)/Applications/$(OUTDIR)"
	@"$(IOSBUILDENV_PATH)/Toolchain/move" "$(OUTDIR)" "$(NAME)/Applications"
	@"$(IOSBUILDENV_PATH)/Toolchain/echo" -n "Package: " > "$(NAME)/DEBIAN/control"
	@"$(IOSBUILDENV_PATH)/Toolchain/plconvert" "Info.plist" -query CFBundleIdentifier >> "$(NAME)/DEBIAN/control"
	@"$(IOSBUILDENV_PATH)/Toolchain/echo" "" >> "$(NAME)/DEBIAN/control"
	@"$(IOSBUILDENV_PATH)/Toolchain/echo" -n "Name: " >> "$(NAME)/DEBIAN/control"
	@"$(IOSBUILDENV_PATH)/Toolchain/plconvert" "Info.plist" -query CFBundleDisplayName >> "$(NAME)/DEBIAN/control"
	@"$(IOSBUILDENV_PATH)/Toolchain/echo" "" >> "$(NAME)/DEBIAN/control"
	@"$(IOSBUILDENV_PATH)/Toolchain/echo" "Priority: optional" >> "$(NAME)/DEBIAN/control"
	@"$(IOSBUILDENV_PATH)/Toolchain/echo" "Architecture: iphoneos-arm" >> "$(NAME)/DEBIAN/control"
	@"$(IOSBUILDENV_PATH)/Toolchain/cat" "cydia-package.cfg" >> "$(NAME)/DEBIAN/control"
	@"$(IOSBUILDENV_PATH)/Toolchain/makedeb" "$(NAME)"
	@"$(IOSBUILDENV_PATH)/Toolchain/move" "$(NAME).deb" "Packages"
	@"$(IOSBUILDENV_PATH)/Toolchain/move" "$(NAME)/Applications/$(OUTDIR)" "."
	@"$(IOSBUILDENV_PATH)/Toolchain/unlink" "$(NAME)"

# This simple rule displays the success message after a successful build
end:
	@"$(IOSBUILDENV_PATH)/Toolchain/echo" " + Done."
	@"$(IOSBUILDENV_PATH)/Toolchain/echo" "Output directory: $(OUTDIR)"
	@"$(IOSBUILDENV_PATH)/Toolchain/echo" "iTunes package:   Packages/$(NAME).ipa"
	@"$(IOSBUILDENV_PATH)/Toolchain/echo" "Cydia package:    Packages/$(NAME).deb"

# This rule removes generated object files from the project and also temporary
# files left over by Visual Studio.
clean:
	@"$(IOSBUILDENV_PATH)/Toolchain/echo" " + Cleaning project intermediate files..."
	@"$(IOSBUILDENV_PATH)/Toolchain/unlink" $(OBJ) *.log *.lastbuildstate *.successfulbuild *.unsuccessfulbuild
	@"$(IOSBUILDENV_PATH)/Toolchain/echo" " + Done."

# This rule removes all generated output from any previous builds so as to
# leave an intact source tree (useful for generating source tree releases).
distclean: clean
	@"$(IOSBUILDENV_PATH)/Toolchain/echo" " + Cleaning project output files..."
	@"$(IOSBUILDENV_PATH)/Toolchain/unlink" "$(OUTDIR)" "Packages" *.ncb *.suo *.pdb *.sdf *.sln *.user "BuildLog.htm"
	@"$(IOSBUILDENV_PATH)/Toolchain/echo" " + Done."
