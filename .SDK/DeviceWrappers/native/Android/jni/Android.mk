LOCAL_PATH := $(TARGET_ROOT)/jni

# Link Libraries Binary Paths
$(ANDROID_STATIC_LIBRARIES)

include $(CLEAR_VARS)

LOCAL_MODULE := Coconut2D
LOCAL_LDLIBS := -lm -lc -landroid -llog -lEGL -lGLESv2 -lOpenSLES -lz -llog
LOCAL_SHARED_LIBRARIES := libcutils
LOCAL_STATIC_LIBRARIES := stdc++ android_native_app_glue $(APP_LDLIBS)

# Include Paths (Libraries, Frameworkds, Sources)
LOCAL_C_INCLUDES := \
system/core/include/cutils \
$(APP_CFLAGS)

# Source files to compile
LOCAL_SRC_FILES := \
$(NATIVE_CPP_SOURCES)

include $(BUILD_SHARED_LIBRARY)

$(call import-module, android/native_app_glue)
