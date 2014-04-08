@echo off
SET NDK_ROOT=D:\mobileFX\Projects\Software\Coconut\IDE\Studio\etc\3rd_party\android-ndk\
SET NDK_PROJECT_PATH=D:/mobileFX/Projects/Software/Coconut/Projects/Coco.project/.targets/native/Android
call "%NDK_ROOT%find-win-host.cmd" NDK_WIN_HOST
if ERRORLEVEL 1 (exit /b 1)
SET NDK_MAKE=%NDK_ROOT%prebuilt/%NDK_WIN_HOST%/bin/make.exe
"%NDK_MAKE%" -f "%NDK_ROOT%build/core/build-local.mk" SHELL=cmd clean
"%NDK_MAKE%" -f "%NDK_ROOT%build/core/build-local.mk" SHELL=cmd -j 8 %*