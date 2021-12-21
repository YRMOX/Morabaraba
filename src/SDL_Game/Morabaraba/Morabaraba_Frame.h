#ifndef MORABARABA_FRAME_H
#define MORABARABA_FRAME_H

/**
 * @brief structure de chaque case du Morabaraba
 */
typedef struct Frame Frame;
#include "Morabaraba.h"
#include "Morabaraba_SDL.h"
#include "stdbool.h"

#define MAX_NEIGHBOR 4

struct Frame{
    int x, y;
    int value;
    Frame** neighbor;
    bool isSelected;
    bool isMoving;
    bool isProtected;
    SDL_Rect rect;
    SDL_Renderer* renderer;
};

/**
 * @brief Crée une case et initialise les valeurs et la position de la case dans
 * la grille
 * 
 * @param morabaraba structure morabaraba pour l'affichage
 * @param x position x de la case dans la grille
 * @param y position y de la case dans la grille
 * @return Adresse de la case après allocation et initialisation
 */
Frame* CreateFrame(Morabaraba* morabaraba, int x, int y);

/**
 * @brief Recherche une Case dans un tableau de Case et renvoie sa position
 * 
 * @param frame Case à recherché
 * @param frames tableau de case dans lequel chercher
 * @return position de la case dans le tableau
 */
int IndexInFrames(Frame* frame, Frame** frames);
void FreeFrame(Frame* frame);

Frame** CreateFrames(int size);
void FreeFrames(Frame** frames, int size);

Frame*** CreateFrameArray(Morabaraba* morabaraba, int size);
void FreeFrameArray(Frame*** array, int size);

//Neighbor
void PrintNeighbor(Frame* frame);
void AppendNeighbor(Frame* frame, Frame* frameToAppend);
bool IsInNeighbor(int x, int y, Frame* frame);

//SDL
void SDL_UpdateFrame(Morabaraba* morabaraba, Frame *frame, SDL_Mouse* mouse);
void SDL_UpdateAllFrame(Morabaraba* morabaraba, SDL_Mouse* mouse);

#endif