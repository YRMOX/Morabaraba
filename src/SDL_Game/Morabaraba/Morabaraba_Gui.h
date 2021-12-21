#ifndef MORABARABA_GUI_H
#define MORABARABA_GUI_H

typedef struct Gui Gui;
#include "Morabaraba.h"
#include "Morabaraba_SDL.h"

struct Gui{
    SDL_Text* actualPlayer;
    SDL_Text** cowInHand;
    SDL_Text** cowTotalNumber;
    SDL_Text* EndText;
};

Gui* CreateGui(Morabaraba* morabaraba);
void SDL_UpdateGui(Morabaraba* morabaraba);
void FreeGui(Gui* gui);

#endif