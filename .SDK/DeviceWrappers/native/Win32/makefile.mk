#==============================================================================
# MinGW Makefile
#==============================================================================

LDFLAGS = -L$(PATH_SDK_LIBRARIES)/$(TARGET)

CFLAGS = $(NATIVE_CPP_INCLUDES)

SRC = src/resource.h $(NATIVE_CPP_SOURCES)

RES = $(NATIVE_RESOURCES)

#==============================================================================
CC 			= $(PATH_3RD_PARTY_MINGW)/bin/g++.exe
RC 			= $(PATH_3RD_PARTY_MINGW)/bin/windres.exe
OBJ			= obj
OBJS		= $(addsuffix .obj, $(basename $(SRC)))
OBJ_OBJ		= $(addprefix $(OBJ)/, $(addsuffix .obj, $(basename $(notdir $(SRC)))))
OUT			= $(PROJECT_NAME).exe
CFLAGS		+= -fpermissive -gdwarf-2 -g3 -m32 -std=c++11 -std=gnu++11
CFLAGS		+= -D GC_THREADS -D WIN32_THREADS -D GC_THREADS -D THREAD_LOCAL_ALLOC -D PARALLEL_MARK -D UNICODE -D _UNICODE -D _WIN32_IE=0x0500 -D WINVER=0x500 -D WIN32 -D _WINDOWS -D _CRT_SECURE_NO_DEPRECATE -D _CRT_NONSTDC_NO_DEPRECATE -D GLEW_STATIC -D CURL_STATICLIB
CFLAGS		+= -D WIN32_APPLICATION -D ENABLE_OPENGL_SUPPORT -D ENABLE_PNG_SUPPORT -D ENABLE_JPG_SUPPORT -D ENABLE_OGG_SUPPORT -D ENABLE_OPENAL_SUPPORT -D ENABLE_FREETYPE_SUPPORT -D ENABLE_CURL_SUPPORT
CFLAGS		+= -Wall -Wno-switch -Wno-unused-but-set-variable -Wno-sign-compare -Wno-delete-non-virtual-dtor -Wno-unused-function -Wno-unused-label -Wno-unused-parameter -Wno-unused-variable -Wunused-value -Wempty-body -Wuninitialized -Wno-comment
LDFLAGS 	+= -static -static-libgcc -static-libstdc++ -Wl,--subsystem,windows
LDLIBS 		= -lglew32 -lopengl32 -lcomdlg32 -lcomctl32 -luuid -loleaut32 -lole32 -lgdi32 -lfreetype -ljpeg -lpng -lz -lvorbisidec -logg -lOpenAL32 -lcurldll -lpthread

$(foreach o,$(SRC),$(eval $(addprefix $(OBJ)/, $(addsuffix .obj, $(basename $(notdir $o)))) = $o))

#-lpthread -L libwinpthread-1.dll

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

