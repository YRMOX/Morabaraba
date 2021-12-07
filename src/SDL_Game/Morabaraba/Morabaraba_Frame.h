#ifndef MORABARABA_FRAME_H
#define MORABARABA_FRAME_H

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

Frame* CreateFrame(Morabaraba* morabaraba, int x, int y);
void FreeFrame(Frame* frame);

//Neighbor
void PrintNeighbor(Frame* frame);
void AppendNeighbor(Frame* frame, Frame* frameToAppend);
bool IsInNeighbor(int x, int y, Frame* frame);

//SDL
void SDL_UpdateFrame(Frame *frame, SDL_Mouse* mouse);
void SDL_UpdateAllFrame(Morabaraba* morabaraba, SDL_Mouse* mouse);

#endif