@echo off
if "%2"=="on" @echo on

if "%1"=="release" goto release
if "%1"=="debug" goto debug

:release
gcc .\src\Morabaraba\*.c -o bin\release\Morabaraba
gcc .\src\Game\*.c -o bin\release\Game
gcc .\src\SDL_Game\*.c .\src\SDL_Game\Morabaraba\*.c -o bin\release\SDL_Game -mwindows -L lib -lmingw32 -lSDL2main -lSDL2_ttf -lSDL2
goto fin

:debug
gcc .\src\Morabaraba\*.c -o bin\debug\Morabaraba
gcc .\src\Game\*.c -o bin\debug\Game
gcc .\src\SDL_Game\*.c .\src\SDL_Game\Morabaraba\*.c -o bin\debug\SDL_Game -L lib -lmingw32 -lSDL2main -lSDL2_ttf -lSDL2
:fin