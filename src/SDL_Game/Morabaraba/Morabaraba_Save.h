#ifndef MORABARABA_SAVE_H
#define MORABARABA_SAVE_H

#include "Morabaraba.h"
#include <SDL2/SDL.h>

Morabaraba* LoadMorabaraba(SDL_Renderer* renderer, char* currentDir);
void SaveMorabaraba(Morabaraba* morabaraba, char* currentDir);

#endif