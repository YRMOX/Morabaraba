#ifndef MORABARABA_H
#define MORABARABA_H

typedef struct Morabaraba Morabaraba;
#include "Morabaraba_Player.h"
#include "Morabaraba_Frame.h"
#include "Morabaraba_Mill.h"
#include "Morabaraba_SDL.h"
#include <stdbool.h>

#define MAX_MILL 20

struct Morabaraba{
    int size;
    Frame*** array;
    Mill** mills;
    int actualPlayer;
    Player** players;
    #ifdef MORABARABA_SDL_H
    SDL_Renderer* renderer;
    #endif
};

#ifdef MORABARABA_SDL_H
Morabaraba* CreateMorabaraba(SDL_Renderer* renderer, int size, int playerNumber);
void SDL_UpdateMorabaraba(Morabaraba* morabaraba, SDL_Mouse* mouse, bool clicked);
#else
Morabaraba* CreateMorabaraba(int size, int playerNumber); // à faire
#endif

bool MoveCow(Morabaraba* morabaraba, int x1, int y1, int x2, int y2, bool flying);
bool SetCow(Morabaraba* morabaraba,int x, int y);
void PrintMorabaraba(Morabaraba* morabaraba);
void FreeMorabaraba(Morabaraba* morabaraba);


#endif