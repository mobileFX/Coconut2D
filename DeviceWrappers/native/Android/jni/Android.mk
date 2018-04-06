#==============================================================================
# Android JNI Makefile
#==============================================================================

LOCAL_PATH := $(TARGET_ROOT)/jni

include $(CLEAR_VARS)

# Link Libraries Binary Paths
$(ANDROID_STATIC_LIBRARIES)

include $(CLEAR_VARS)

# Include Paths (Libraries, Frameworkds, Sources)
LOCAL_C_INCLUDES := \
system/core/include/cutils \
$(LOCAL_C_INCLUDES)

# Source files to compile (Libraries, Frameworkds, Sources)
LOCAL_SRC_FILES := \
$(LOCAL_SRC_FILES)

LOCAL_MODULE    					:= Coconut2D
LOCAL_MODULE_TAGS 					:=
LOCAL_SDK_VERSION 					:= 14
LOCAL_ARM_MODE 						:= arm
LOCAL_DISABLE_FORMAT_STRING_CHECKS 	:= false
LOCAL_EXPORT_C_INCLUDE_DIRS 		:= $(LOCAL_PATH)
LOCAL_STATIC_LIBRARIES 				:= stdc++ android_native_app_glue $(APP_LDLIBS)
LOCAL_SHARED_LIBRARIES 				:= libcutils
LOCAL_CFLAGS    					+= $(APP_CFLAGS)
LOCAL_LDFLAGS						+= $(APP_LDFLAGS)

# C library
LOCAL_LDLIBS += -lm -lc -lstdc++ -latomic

# Android-specific log support
LOCAL_LDLIBS += -llog

# ZLib compression library
LOCAL_LDLIBS += -lz

# Dynamic linker library
LOCAL_LDLIBS += -ldl

# OpenGL ES 2.0 library (Android API level 5)
LOCAL_LDLIBS += -lGLESv2

# JNI Graphics (Android API level 8)
LOCAL_LDLIBS += -ljnigraphics

# Native platform interface for allocating and managing OpenGLES surfaces (Android API level 9)
LOCAL_LDLIBS += -lEGL

# Native audio handling is based on the Khronos Group OpenSL ES 1.0.1 API
LOCAL_LDLIBS += -lOpenSLES

# Android native application APIs
LOCAL_LDLIBS += -landroid

# Native multimedia handling is based on Khronos Group OpenMAX AL 1.0.1 API
LOCAL_LDLIBS += -lOpenMAXAL

# Native multimedia handling is based on Khronos Group OpenMAX AL 1.0.1 API
LOCAL_LDLIBS += -lOpenMAXAL

# SQLite
LOCAL_CFLAGS += -DSQLITE_DEFAULT_AUTOMATIC_INDEX=1
LOCAL_CFLAGS += -DSQLITE_DEFAULT_FOREIGN_KEYS=1
LOCAL_CFLAGS += -DSQLITE_ENABLE_COLUMN_METADATA=1
LOCAL_CFLAGS += -DSQLITE_ENABLE_FTS5=1
LOCAL_CFLAGS += -DSQLITE_ENABLE_RTREE=1
LOCAL_CFLAGS += -DSQLITE_ENABLE_STAT4=1
LOCAL_CFLAGS += -DSQLITE_SOUNDEX=1

# Libraries Binaries Paths
LOCAL_LDFLAGS += \
$(APP_LDLIBPATHS)

include $(BUILD_SHARED_LIBRARY)

$(call import-module,android/cpufeatures)
$(call import-module, android/native_app_glue)
