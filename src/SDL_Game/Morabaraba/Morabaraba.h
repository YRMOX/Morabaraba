#ifndef MORABARABA_H
#define MORABARABA_H

/**
 * @brief structure du jeu Morabaraba
 */
typedef struct Morabaraba Morabaraba;
#include "Morabaraba_Player.h"
#include "Morabaraba_Frame.h"
#include "Morabaraba_Mill.h"
#include "Morabaraba_SDL.h"
#include "Morabaraba_Gui.h"
#include <stdbool.h>

#define MAX_MILL 20

struct Morabaraba{
    int size;
    int playerNumber;
    int actualPlayer;
    int countDown;
    int winner;
    Frame*** array;
    Mill** mills;
    Player** players;
    #ifdef MORABARABA_SDL_H
    SDL_Rect gridRect;
    SDL_Rect guiRect;
    Gui* gui;
    SDL_Renderer* renderer;
    #endif
};

/**
 * @brief Création d'une structure Morabaraba
 * 
 * @param renderer renderer de la fenetre utilisant la SDL
 * @param size taille du Morabaraba nombre impaire
 * @param playerNumber nombre de joueur
 * @return Adresse de la structure Morabaraba
 */
Morabaraba* CreateMorabaraba(SDL_Renderer* renderer, int size, int playerNumber);
void SDL_UpdateMorabaraba(Morabaraba* morabaraba, SDL_Mouse* mouse, bool clicked);

bool MoveCow(Morabaraba* morabaraba, int x1, int y1, int x2, int y2, bool flying);
bool SetCow(Morabaraba* morabaraba,int x, int y);
void PrintMorabaraba(Morabaraba* morabaraba);
void FreeMorabaraba(Morabaraba* morabaraba);


#endif