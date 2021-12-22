@echo off
if "%2"=="on" @echo on

if "%1"=="release" goto release
if "%1"=="debug" goto debug

:release
windres .\src\Morabaraba\resource.rc -O coff -o .\src\Morabaraba\resource.res
windres .\src\SDL_Game\resource.rc -O coff -o .\src\SDL_Game\resource.res
gcc .\src\Morabaraba\*.c .\src\Morabaraba\*.res -o bin\release\Morabaraba
gcc .\src\SDL_Game\*.c .\src\SDL_Game\Morabaraba\*.c .\src\SDL_Game\*.res -o bin\release\SDL_Game -mwindows -L lib -lmingw32 -lSDL2main -lSDL2_ttf -lSDL2
goto fin

:debug
windres .\src\Morabaraba\resource.rc -O coff -o .\src\Morabaraba\resource.res
windres .\src\SDL_Game\resource.rc -O coff -o .\src\SDL_Game\resource.res
gcc .\src\Morabaraba\*.c .\src\Morabaraba\*.res -o bin\debug\Morabaraba
gcc .\src\SDL_Game\*.c .\src\SDL_Game\Morabaraba\*.c .\src\SDL_Game\*.res -o bin\debug\SDL_Game -L lib -lmingw32 -lSDL2main -lSDL2_ttf -lSDL2
:fin