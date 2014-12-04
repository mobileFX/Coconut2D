@echo off
cd /D %~dp0

@echo Starting node.js ...
start "node.js" "$(PATH_3RD_PARTY_NODEJS)/node.exe" --debug-brk=9999 main.js

rem @echo Starting Chrome ...
rem start "Chrome" %1 http://localhost
