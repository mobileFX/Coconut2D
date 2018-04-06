
# Available toolchains are located in android-ndk/toolchains

# use this to select gcc
NDK_TOOLCHAIN_VERSION := $(TARGETS.Android.APP_SETTINGS.NDK_TOOLCHAIN_VERSION)
NDK_DEBUG := 1

# use this to select the latest clang version:
#NDK_TOOLCHAIN_VERSION := clang

# armeabi code can run on armeabi-v7a devices, but not the other way around.
# So you don't need armeabi-v7a if you have armeabi, but it will allow you
# take advantage of hardware floating point operations on some devices.
APP_ABI := $(TARGETS.Android.APP_SETTINGS.APP_ABI)

# STL implementation.
APP_STL := $(TARGETS.Android.APP_SETTINGS.APP_STL)

# NDK does not come with support for all platforms.
# As of r9d, it only has:
# * android-3
# * android-4
# * android-5
# * android-8
# * android-9
# * android-12
# * android-13
# * android-14
# * android-15
# * android-16
# * android-17
# * android-18
# * android-19

APP_PLATFORM := $(TARGETS.Android.APP_SETTINGS.ANDROID_PLATFORM)

# debug flags
#Don't optimize code and don't include debug information
#for some reason the application doesn't launch/crashes at launch with -O2/s but works with -O0/1/3

APP_OPTIM := $(LCONFIGURATION)
APP_CFLAGS := $(APP_CFLAGS)

# Enable c++11 extentions in source code.
# Features supported are:
# * atomic
# * chrono
# * condition_variable
# * memory (shared_ptr, unique_ptr)
# * mutex (lock_guard,mutex,unique_lock)
# * thread (see comments)
# * lamdas and auto keyword

APP_CPPFLAGS := -DANDROID_APPLICATION $(APP_CPPFLAGS)
