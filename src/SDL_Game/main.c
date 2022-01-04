#include "Morabaraba/Morabaraba_SDL.h"
#include "Morabaraba/Morabaraba.h"
#include "Morabaraba/Morabaraba_Save.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main(int argc, char *argv[]){
    char currentDir[20];
    strcpy(currentDir, argv[0]);
    int i=0;
    while(currentDir[i]!='S') i++;
    currentDir[i] = '\0';

    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();
    SDL_Window *window = SDL_CreateWindow("Morabaraba", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1000, 500, SDL_WINDOW_RESIZABLE);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    Morabaraba* morabaraba;
    if((argc > 1)&&strcmp(argv[1], "lastSave"))
        morabaraba = LoadMorabaraba(renderer, currentDir);
    else 
        morabaraba = CreateMorabaraba(renderer, 7, 2);
    SDL_Event event;
    SDL_Mouse mouse;
    bool clicked = false;
    bool launched = true;
    while(launched){
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);
        SDL_WaitEvent(&event);
        SDL_UpdateMouse(&mouse);
        if(event.type == SDL_QUIT){
            SaveMorabaraba(morabaraba, currentDir);
            launched = false;
        }
        SDL_UpdateMorabaraba(morabaraba, &mouse);
        SDL_UpdateMouseBuffer(&mouse);
        SDL_RenderPresent(renderer);
    }
    FreeMorabaraba(morabaraba);
    return EXIT_SUCCESS;
}