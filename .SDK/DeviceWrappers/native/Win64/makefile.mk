#==============================================================================
# MinGW Makefile
#==============================================================================

# Link Libraries Binary Paths
LDFLAGS = $(APP_LDFLAGS)

# Compiler options and Include Paths (Libraries, Frameworkds, Sources)
CFLAGS = $(APP_CFLAGS)

# Source files to compile
SRC = src/resource.h \
$(NATIVE_CPP_SOURCES)

# Resources to embed
RES = $(NATIVE_RESOURCES)

#==============================================================================
CC 			= $(PATH_3RD_PARTY_MINGW)/bin/g++.exe
RC 			= $(PATH_3RD_PARTY_MINGW)/bin/windres.exe
OBJ			= obj
OBJS		= $(addsuffix .obj, $(basename $(SRC)))
OBJ_OBJ		= $(addprefix $(OBJ)/, $(addsuffix .obj, $(basename $(notdir $(SRC)))))
OUT			= $(PROJECT_NAME).exe

CFLAGS		+= -std=c++14 -fpermissive
CFLAGS		+= -D _WIN32_IE=0x0500 -D WINVER=0x500 -D WIN32 -D _WINDOWS -D WIN32_APPLICATION -D WIN32_LEAN_AND_MEAN -DENABLE_BOOST
CFLAGS		+= -D UNICODE -D _UNICODE
CFLAGS		+= -D _CRT_SECURE_NO_DEPRECATE -D _CRT_NONSTDC_NO_DEPRECATE -D GLEW_STATIC -D CURL_STATICLIB
CFLAGS		+= -D GC_THREADS -D WIN32_THREADS -D THREAD_LOCAL_ALLOC -D PARALLEL_MARK
CFLAGS		+= -Wno-return-type -Wno-switch -Wno-unused-but-set-variable -Wno-sign-compare -Wno-delete-non-virtual-dtor -Wno-unused-function -Wno-unused-label -Wno-unused-parameter -Wno-unused-variable -Wunused-value -Wempty-body -Wuninitialized -Wmaybe-uninitialized -Wno-comment
LDFLAGS 	+= -mwindows -static -static-libgcc -static-libstdc++ -Wl,--subsystem,windows
LDLIBS 		+= -lglew32 -lopengl32 -lcomdlg32 -lcomctl32 -luuid -loleaut32 -lole32 -lgdi32 -lws2_32 $(APP_LDLIBS)

# LDLIBS += -lpthread -lglew32 -lopengl32 -lcomdlg32 -lcomctl32 -luuid -loleaut32 -lole32 -lgdi32 -lws2_32 $(APP_LDLIBS)

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
	@$(CC) $(CFLAGS) -c $($@) -o $@

#==============================================================================
# Compile Resources
#==============================================================================
$(OBJ)/resource.obj: res/resource.rc res/Application.manifest res/Application.ico src/resource.h
	$(RC) -I.\src -I.\res -i $< -o $@

#==============================================================================
# Link
#==============================================================================
$(OUT): $(OBJ_OBJ)
	$(CC) $(LDFLAGS) -g -o $@ $(OBJ_OBJ) $(LDLIBS)

