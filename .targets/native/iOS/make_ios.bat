@echo off
SET IOSBUILDENV_PATH=D:\mobileFX\Projects\Software\Coconut\IDE\Studio\etc\3rd_party\iOS
SET IOS_PROJECT_PATH=D:\mobileFX\Projects\Software\Coconut\Projects\Coco.project\.targets\native\iOS
SET IOS_MAKEFILE=%IOS_PROJECT_PATH%\Makefile.mk
"%IOSBUILDENV_PATH%\Toolchain\make.exe" --directory="%IOS_PROJECT_PATH%" --makefile="%IOS_MAKEFILE%" --jobs --warn-undefined-variables SHELL=%ComSpec% compile
"%IOSBUILDENV_PATH%\Toolchain\make.exe" --directory="%IOS_PROJECT_PATH%" --makefile="%IOS_MAKEFILE%" --warn-undefined-variables SHELL=%ComSpec% link codesign ipa end