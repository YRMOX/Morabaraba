#include "Morabaraba_Gui.h"
#include <stdio.h>
#include <string.h>

char* CreateString(char* string){
    int len = strlen(string);
    char* temp = malloc(len+1);
    for(int i=0; i<len; i++){
        temp[i] = string[i];
    }
    temp[len] = '\0';
    return temp;
}

int NumberLen(int number){
    if(number == 0) return 1;
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

int IndexInString(char character, char* string){
    for(int i=0; i<strlen(string); i++){
        if(string[i] == character){
            return i;
        }
    }
    return -1;
}

int StringInString(char* string, char* toFound){
    for(int i=0; i<strlen(string); i++){
        bool temp = true;
        for(int j=0; j<strlen(toFound); j++){
            if(string[i+j]!=toFound[j]){
                temp = false;
            }
        }
        if(temp){
            return i;
        }
    }
    return -1;
}

void ReplaceInString(char** dest, char* thatReplace, char* toReplace){
    int thatReplaceLen = strlen(thatReplace);
    int diff = thatReplaceLen-strlen(toReplace);
    int len = strlen(*dest)+diff;
    char* string = malloc(len+1);
    int position = StringInString(*dest, toReplace);
    int i;
    for(i = 0; i<position; i++) string[i] = (*dest)[i];
    for(int j=0; j<thatReplaceLen; j++) string[i+j] = thatReplace[j];
    i += thatReplaceLen;
    for(i; i<len; i++) string[i] = (*dest)[i-diff];
    string[len] = '\0';
    free(*dest);
    *dest = string;
}

Gui* CreateGui(Morabaraba* morabaraba){
    Gui* gui = malloc(sizeof(Gui));
    TTF_Font* arial = TTF_OpenFont("arial.ttf", 25);
    if(arial==NULL) return NULL;
    SDL_Color white = {255, 255, 255};
    SDL_Color black = {0, 0, 0};
    int x = morabaraba->guiRect.x, y = morabaraba->guiRect.y;
    gui->actualPlayer = SDL_CreateText(morabaraba->renderer, x, y, arial, CreateString(" Tour du Joueur %d"), white);
    gui->cowInHand = malloc(sizeof(SDL_Text*)*morabaraba->playerNumber);
    y = gui->actualPlayer->rect.y+gui->actualPlayer->rect.h;
    for(int i=0; i<morabaraba->playerNumber; i++){
        gui->cowInHand[i] = SDL_CreateText(morabaraba->renderer, x, y, arial, CreateString(" Le joueur %d a %d vache dans sa main"), white);
        y = gui->cowInHand[i]->rect.y+gui->cowInHand[i]->rect.h;

    }
    gui->cowTotalNumber = malloc(sizeof(SDL_Text*)*morabaraba->playerNumber);
    for(int i=0; i<morabaraba->playerNumber; i++){
        gui->cowTotalNumber[i] = SDL_CreateText(morabaraba->renderer, x, y, arial, CreateString(" Le joueur %d a %d vache aux total"), white);
        if(i<=morabaraba->playerNumber){
            y = gui->cowTotalNumber[i]->rect.y+gui->cowTotalNumber[i]->rect.h;
        }
    }
    int renderW, renderH;
    SDL_GetRendererOutputSize(morabaraba->renderer, &renderW, &renderH);
    gui->EndText = SDL_CreateText(morabaraba->renderer, renderW/2, renderH/2, arial, CreateString("Le gagnent est le joueur %d"), black);
    return gui;
}

void SDL_UpdateGui(Morabaraba* morabaraba){
    int x, y;
    if(morabaraba->winner != 0){
        int renderW, renderH;
        SDL_GetRendererOutputSize(morabaraba->renderer, &renderW, &renderH);
        free(morabaraba->gui->EndText->text);
        morabaraba->gui->EndText->text = CreateString("Le gagnent est le joueur %d");
        ReplaceInString(&morabaraba->gui->EndText->text, NumberToString(morabaraba->winner), "%d");
        x = renderW/2-morabaraba->gui->EndText->rect.w/2;
        y = renderH/2-morabaraba->gui->EndText->rect.h/2;
        SDL_UpdateText(morabaraba->renderer, morabaraba->gui->EndText, x, y);
        return;
    }
    SDL_SetRenderDrawColor(morabaraba->renderer, 0, 0, 0, 0);
    SDL_RenderFillRect(morabaraba->renderer, &morabaraba->guiRect);
    x = morabaraba->guiRect.x; y = morabaraba->guiRect.y;
    free(morabaraba->gui->actualPlayer->text);
    morabaraba->gui->actualPlayer->text = CreateString(" Tour du Joueur %d");
    ReplaceInString(&morabaraba->gui->actualPlayer->text,
                    NumberToString(morabaraba->actualPlayer), "%d");
    SDL_UpdateText(morabaraba->renderer, morabaraba->gui->actualPlayer, x, y);
    y = morabaraba->gui->actualPlayer->rect.y+morabaraba->gui->actualPlayer->rect.h;
    for(int i=0; i<morabaraba->playerNumber; i++){
        free(morabaraba->gui->cowInHand[i]->text);
        morabaraba->gui->cowInHand[i]->text = CreateString(" Le joueur %d a %d vache dans sa main");
        ReplaceInString(&morabaraba->gui->cowInHand[i]->text,
                        NumberToString(i+1), "%d");
        ReplaceInString(&morabaraba->gui->cowInHand[i]->text,
                        NumberToString(morabaraba->players[i]->cowInHand), "%d");
        SDL_UpdateText(morabaraba->renderer, morabaraba->gui->cowInHand[i], x, y);
        y = morabaraba->gui->cowInHand[i]->rect.y+morabaraba->gui->cowInHand[i]->rect.h;
    }
    for(int i=0; i<morabaraba->playerNumber; i++){
        free(morabaraba->gui->cowTotalNumber[i]->text);
        morabaraba->gui->cowTotalNumber[i]->text = CreateString(" Le joueur %d a %d vache aux total");
        ReplaceInString(&morabaraba->gui->cowTotalNumber[i]->text,
                        NumberToString(i+1), "%d");
        ReplaceInString(&morabaraba->gui->cowTotalNumber[i]->text,
                        NumberToString(morabaraba->players[i]->cowTotalNumber), "%d");
        SDL_UpdateText(morabaraba->renderer, morabaraba->gui->cowTotalNumber[i], x, y);
        if(i<=morabaraba->playerNumber){
            y = morabaraba->gui->cowTotalNumber[i]->rect.y+morabaraba->gui->cowTotalNumber[i]->rect.h;
        }
    }
}