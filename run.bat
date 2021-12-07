@echo off
if "%2"=="on" @echo on

if "%1"=="release" goto release
if "%1"=="debug" goto debug

:release
.\bin\release\Morabaraba.exe
goto fin

:debug
.\bin\debug\Morabaraba.exe
:fin