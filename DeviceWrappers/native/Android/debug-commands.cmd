
REM Install the APK on the Device
adb -e shell pm set-install-location 1
adb -e install -r $(TARGETS.Android.TARGET_OUTPUT)
adb -e shell setprop debug.checkjni 1

REM Start application on Device
adb -e shell am start -n $(ANDROID_PACKAGE)/$(ANDROID_PACKAGE).MainActivity

REM Get running APK process ID from the Device
adb -e shell "ps | grep $(ANDROID_PACKAGE)"

REM Start the GDBServer on the Device
adb -e shell run-as $(ANDROID_PACKAGE) lib/gdbserver +debug-socket --attach [PROCESSID_HERE]

REM Setup debug socket forwarding
adb -e forward tcp:5039 localfilesystem:/data/data/$(ANDROID_PACKAGE)/debug-socket

REM Pull APK app process, linker and C library from the Device
REM (you must call those from an Android Shell on the Target Folder)
adb -e pull /system/bin/app_process ./obj/local/armeabi-v7a/app_process
adb -e pull /system/bin/linker ./obj/local/armeabi-v7a/linker
adb -e pull /system/lib/libc.so ./obj/local/armeabi-v7a/libc.so

REM Start GDB and connect to GDB Server on the Device
REM (you must run this in a separate console because it blocks)
"$(PATH_3RD_PARTY_ANDROID_NDK)/toolchains/arm-linux-androideabi-4.8/prebuilt/windows-x86_64/bin/arm-linux-androideabi-gdb.exe" -x debugger-config.gdb

REM All-in-one Debugging with Python Script
ndk-gdb-py --verbose --force --launch $(ANDROID_PACKAGE).MainActivity -e -t --nowait


Send the ASCII ETX character (Ctrl-c) to the remote target to interrupt the execution of the program.
