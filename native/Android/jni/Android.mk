LOCAL_PATH := $(call my-dir)
FXCORE_PATH := /Users/mobileFX/Dropbox/Share/Coconut/fxCore
FXLIBS_PATH := ../../../Libs
FXINCL_PATH := $(FXCORE_PATH)/Include

include $(CLEAR_VARS)
	LOCAL_MODULE := Tremolo
	LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/$(FXLIBS_PATH)/Tremolo008
	LOCAL_SRC_FILES := $(FXLIBS_PATH)/Tremolo008/bitwise.c $(FXLIBS_PATH)/Tremolo008/codebook.c $(FXLIBS_PATH)/Tremolo008/dsp.c $(FXLIBS_PATH)/Tremolo008/floor0.c $(FXLIBS_PATH)/Tremolo008/floor1.c $(FXLIBS_PATH)/Tremolo008/floor_lookup.c $(FXLIBS_PATH)/Tremolo008/framing.c $(FXLIBS_PATH)/Tremolo008/mapping0.c $(FXLIBS_PATH)/Tremolo008/mdct.c $(FXLIBS_PATH)/Tremolo008/misc.c $(FXLIBS_PATH)/Tremolo008/res012.c $(FXLIBS_PATH)/Tremolo008/info.c $(FXLIBS_PATH)/Tremolo008/vorbisfile.c
	ifeq ($(TARGET_ARCH),arm)
		LOCAL_SRC_FILES += $(FXLIBS_PATH)/Tremolo008/bitwiseARM.s $(FXLIBS_PATH)/Tremolo008/dpen.s $(FXLIBS_PATH)/Tremolo008/floor1ARM.s $(FXLIBS_PATH)/Tremolo008/mdctARM.s
		LOCAL_CFLAGS := -D_ARM_ASSEM_
	else
		LOCAL_CFLAGS := -DONLY_C
	endif
include $(BUILD_STATIC_LIBRARY)

include $(CLEAR_VARS)
	LOCAL_LDLIBS := -L$(LOCAL_PATH)/$(TARGET_ARCH_ABI) -lv8_base -lpreparser_lib -lv8_nosnapshot -lv8_nosnapshot -landroid -llog -lEGL -lGLESv2 -lOpenSLES -lz -lpng -ljpeg -lfreetype -lopenal -lcurl
	LOCAL_STATIC_LIBRARIES := stdc++ android_native_app_glue Tremolo
	LOCAL_C_INCLUDES := $(FXCORE_PATH)/CRL $(FXINCL_PATH)/v8 $(FXINCL_PATH)/png $(FXINCL_PATH)/jpeg-9 $(FXINCL_PATH)/freetype $(FXINCL_PATH)/openal-soft-1.15.1 $(FXINCL_PATH)/curl
	LOCAL_MODULE := fxCore
	LOCAL_CPPFLAGS := -B$(FXCORE_PATH)/CRL
	LOCAL_SRC_FILES := main.cpp fxDeviceWrapper.cpp ../../CRL/fxCRL.cpp ../../CRL/fxAudio.cpp 
include $(BUILD_SHARED_LIBRARY)

$(call import-module, android/native_app_glue)