#==============================================================================
# MinGW Makefile
#==============================================================================

# Link Libraries Binary Paths
LIB_BIN_PATHS = \
$(APP_LDLIBPATHS)

# Include Paths (Libraries, Frameworkds, Sources)
INCLUDE_PATHS = \
$(LOCAL_C_INCLUDES)

# Source files to compile
SRC = src/resource.h \
$(LOCAL_SRC_FILES)

# Resources to embed
RES = \
$(NATIVE_RESOURCES)

#==============================================================================
COMPILER	= $(PATH_3RD_PARTY_MINGW)/bin/gcc.exe
LINKER		= $(PATH_3RD_PARTY_MINGW)/bin/g++.exe
RC 			= $(PATH_3RD_PARTY_MINGW)/bin/windres.exe
OBJ			= obj
OBJS		= $(addsuffix .obj, $(basename $(SRC)))
OBJ_OBJ		= $(addprefix $(OBJ)/, $(addsuffix .obj, $(basename $(notdir $(SRC)))))
OUT			= $(PROJECT_NAME).exe

CPPFLAGS	+= -std=gnu++11 -fexceptions -fpermissive -D__GXX_EXPERIMENTAL_CXX0X__
CPPFLAGS	+= $(APP_CPPFLAGS)

CFLAGS		+= -std=gnu++11 -fexceptions -fpermissive -D__GXX_EXPERIMENTAL_CXX0X__
CFLAGS		+= -m32 -finput-charset=UTF-8 -fexec-charset=UTF-8 -DUNICODE -D_UNICODE
CFLAGS		+= -DWINVER=0x500 -DWIN32 -D_WINDOWS -DWIN32_APPLICATION -DWIN32_LEAN_AND_MEAN -D_WIN32_IE=0x0500
CFLAGS		+= -D_CRT_SECURE_NO_DEPRECATE -D_CRT_NONSTDC_NO_DEPRECATE -DGLEW_STATIC -DCURL_STATICLIB
CFLAGS		+= -DGC_THREADS -DWIN32_THREADS -DHAVE_PTHREADS -DTHREAD_LOCAL_ALLOC -DPARALLEL_MARK
CFLAGS		+= -Wno-return-type -Wno-switch -Wno-unused-but-set-variable -Wno-sign-compare -Wno-delete-non-virtual-dtor -Wno-unused-function -Wno-comment
CFLAGS		+= -Wno-unused-label -Wno-unused-parameter -Wno-unused-variable -Wunused-value -Wempty-body -Wuninitialized -Wmaybe-uninitialized -Wno-write-strings
CFLAGS		+= $(APP_CFLAGS)
CFLAGS		+= $(INCLUDE_PATHS)

LDFLAGS 	+= -Wl,--subsystem,windows -mwindows -static -static-libgcc -static-libstdc++
LDFLAGS 	+= $(APP_LDFLAGS) $(LIB_BIN_PATHS)

LDLIBS 		+= -lcomdlg32 -lcomctl32 -luuid -loleaut32 -lole32 -lgdi32 -lws2_32 -lpthread
LDLIBS 		+= $(APP_LDLIBS)

$(foreach o,$(SRC),$(eval $(addprefix $(OBJ)/, $(addsuffix .obj, $(basename $(notdir $o)))) = $o))

#==============================================================================
all: $(OUT)

$(OBJ):
	mkdir $(OBJ)

$(OBJ_OBJ): | $(OBJ)

#==============================================================================
# Clean/Prepare Compilation
#==============================================================================
clean:
	del $(OUT)
	del obj\*.o

#==============================================================================
# Compile C/C++ files
#==============================================================================
%.obj:
	@echo  + Compiling $($@) ...
	@$(COMPILER) $(CFLAGS) -c $($@) -o $@

#==============================================================================
# Compile Resources
#==============================================================================
$(OBJ)/resource.obj: res/resource.rc res/Application.manifest res/Application.ico src/resource.h
	$(RC) -I.\src -I.\res -i $< -o $@

#==============================================================================
# Link
#==============================================================================
$(OUT): $(OBJ_OBJ)
	$(LINKER) $(LDFLAGS) -g -o $@ $(OBJ_OBJ) $(LDLIBS)

