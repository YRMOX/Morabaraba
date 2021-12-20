#include "Morabaraba_Gui.h"
#include <stdio.h>
#include <string.h>

char* CreateString(char* string){
    int len = strlen(string);
    printf("%c", string[len]);
    char* temp = malloc(len+1);
    for(int i=0; i<len; i++){
        temp[i] = string[i];
    }
    temp[len] = '\0';
    return temp;
}

int NumberLen(int number){
    int len = 0;
    while(number != 0){
        number /= 10;
        len++;
    }
    return len;
}


char* NumberToString(int number){
    int len = NumberLen(number);
    char* string = malloc(len+1);
    for(int i=len-1; i>=0; i--){
        string[i] = number % 10 + '0';
        number /= 10;
    }
    string[len] = '\0';
    return string;
}

void ReplaceInString(char** dest, char* toAppend, int position){
    int len = strlen(*dest)+strlen(toAppend)-1;
    char* string = malloc(len+1);
    int i = 0;
    int j = 0;
    int k = 0;
    while(j < position){ string[i] = (*dest)[j]; i++; j++;}
    while(k < strlen(toAppend)){ string[i] = toAppend[k]; i++; k++;}
    while((*dest)[j]!=' ') j++;
    while(i < len){ string[i] = (*dest)[j]; i++; j++;}
    string[len] = '\0';
    free(*dest);
    *dest = string;
}

int IndexInString(char character, char* string){
    for(int i=0; i<strlen(string); i++){
        if(string[i] == character){
            return i;
        }
    }
    return -1;
}

Gui* CreateGui(Morabaraba* morabaraba){
    Gui* gui = malloc(sizeof(Gui));
    TTF_Font* arial = TTF_OpenFont("arial.ttf", 25);
    if(arial==NULL) return NULL;
    SDL_Color white = {255, 255, 255};
    int x = morabaraba->guiRect.x, y = morabaraba->guiRect.y;
    gui->actualPlayer = SDL_CreateText(morabaraba->renderer, x, y, arial, CreateString(" Tour du Joueur 0"), white);
    gui->cowInHand = malloc(sizeof(SDL_Text*)*morabaraba->playerNumber);
    y = gui->actualPlayer->rect.y+gui->actualPlayer->rect.h;
    for(int i=0; i<morabaraba->playerNumber; i++){
        gui->cowInHand[i] = SDL_CreateText(morabaraba->renderer, x, y, arial, CreateString(" Le joueur 0 a 0 vache dans sa main"), white);
        y = gui->cowInHand[i]->rect.y+gui->cowInHand[i]->rect.h;

    }
    gui->cowTotalNumber = malloc(sizeof(SDL_Text*)*morabaraba->playerNumber);
    for(int i=0; i<morabaraba->playerNumber; i++){
        gui->cowTotalNumber[i] = SDL_CreateText(morabaraba->renderer, x, y, arial, CreateString(" Le joueur 0 a 0 vache aux total"), white);
        if(i<=morabaraba->playerNumber){
            y = gui->cowTotalNumber[i]->rect.y+gui->cowTotalNumber[i]->rect.h;
        }
    }
    return gui;
}

void SDL_UpdateGui(Morabaraba* morabaraba){
    SDL_SetRenderDrawColor(morabaraba->renderer, 0, 0, 0, 0);
    SDL_RenderFillRect(morabaraba->renderer, &morabaraba->guiRect);
    int x = morabaraba->guiRect.x, y = morabaraba->guiRect.y;
    morabaraba->gui->actualPlayer->text[16] = morabaraba->actualPlayer+'0';
    SDL_UpdateText(morabaraba->renderer, morabaraba->gui->actualPlayer, x, y);
    y = morabaraba->gui->actualPlayer->rect.y+morabaraba->gui->actualPlayer->rect.h;
    for(int i=0; i<morabaraba->playerNumber; i++){
        morabaraba->gui->cowInHand[i]->text[11] = i + 1 + '0';
        ReplaceInString(&morabaraba->gui->cowInHand[i]->text,
                        NumberToString(morabaraba->players[i]->cowInHand), 15);
        SDL_UpdateText(morabaraba->renderer, morabaraba->gui->cowInHand[i], x, y);
        y = morabaraba->gui->cowInHand[i]->rect.y+morabaraba->gui->cowInHand[i]->rect.h;
    }
    for(int i=0; i<morabaraba->playerNumber; i++){
        morabaraba->gui->cowTotalNumber[i]->text[11] = i + 1 + '0';
        ReplaceInString(&morabaraba->gui->cowTotalNumber[i]->text,
                        NumberToString(morabaraba->players[i]->cowTotalNumber), 15);
        SDL_UpdateText(morabaraba->renderer, morabaraba->gui->cowTotalNumber[i], x, y);
        if(i<=morabaraba->playerNumber){
            y = morabaraba->gui->cowTotalNumber[i]->rect.y+morabaraba->gui->cowTotalNumber[i]->rect.h;
        }
    }
}