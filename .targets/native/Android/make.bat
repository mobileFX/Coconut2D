@echo off
SET ANT_HOME=D:\mobileFX\Projects\Software\Coconut\IDE\Studio\etc\3rd_party\ant
SET JAVA_HOME=D:\mobileFX\Projects\Software\Coconut\IDE\Studio\etc\3rd_party\java
SET ANDROID_SDK_HOME=D:\mobileFX\Projects\Software\Coconut\IDE\Studio\etc\3rd_party\android-sdk\
SET PATH=%ANT_HOME%;%ANT_HOME%\bin;%JAVA_HOME%;%JAVA_HOME%\bin;%PATH%
"%ANT_HOME%\bin\ant" debug