#include "Morabaraba.h"
#include <stdio.h>
#include <stdlib.h>

void IncOrDec(int* i, int* j, int axis){
    switch (axis)
    {
    case 0:
        (*i)--;
        break;
    case 1:
        (*i)++;
        break;
    case 2:
        (*j)--;
        break;
    case 3:
        (*j)++;
        break;
    }
}

bool InMorabaraba(Morabaraba* morabaraba, int i, int j, int axis){
    switch (axis)
    {
    case 0:
        return i>0;
        break;
    case 1:
        return i<morabaraba->size-1;
        break;
    case 2:
        return j>0;
        break;
    case 3:
        return j<morabaraba->size-1;
        break;
    }
}

void AxisNeighbor(Morabaraba* morabaraba, int x, int y, int axis){
    Frame* temp = morabaraba->array[x][y];
    int i = temp->x;
    int j = temp->y;
    do{
        if(InMorabaraba(morabaraba, i, j, axis)){
            IncOrDec(&i, &j, axis);
        }else break;
        if((i==morabaraba->size/2)&&(j==morabaraba->size/2)) break;
    }while(!morabaraba->array[i][j]);
    if((temp != morabaraba->array[i][j])&&(morabaraba->array[i][j]!=NULL)){
        AppendNeighbor(temp, morabaraba->array[i][j]);
    }
}

void SetNeighbor(Morabaraba* morabaraba, int x, int y){
    for(int i=0; i<4; i++){
        AxisNeighbor(morabaraba, x, y, i);
    }
    Frame* temp = morabaraba->array[x][y];
    if(temp->x == temp->y){
        if((temp->x>0)&&(temp->y>0)){
            if(morabaraba->array[temp->x-1][temp->y-1]!=0){
                AppendNeighbor(temp, morabaraba->array[temp->x-1][temp->y-1]);
            }
        }
        if((temp->x<morabaraba->size-1)&&(temp->y<morabaraba->size-1)){
            if(morabaraba->array[temp->x+1][temp->y+1]){
                AppendNeighbor(temp, morabaraba->array[temp->x+1][temp->y+1]);
            }
        }
    }
    if(temp->x == morabaraba->size-1-temp->y){
        if((temp->x<morabaraba->size-1)&&(temp->y>0)){
        
            if(morabaraba->array[temp->x+1][temp->y-1]!=0){
                AppendNeighbor(temp, morabaraba->array[temp->x+1][temp->y-1]);
            }
        }
        if((temp->x>0)&&(temp->y<morabaraba->size-1)){
            if(morabaraba->array[temp->x-1][temp->y+1]!=0){
                AppendNeighbor(temp, morabaraba->array[temp->x-1][temp->y+1]);
            }
        }
    }
}

void SetAllNeighbor(Morabaraba* morabaraba){
    for(int i=0; i<morabaraba->size; i++){
        for(int j=0; j<morabaraba->size; j++){
            if(morabaraba->array[i][j] != NULL){
                SetNeighbor(morabaraba, i, j);
            }
        }
    }
}

void SDL_DrawNeighbor(Morabaraba* morabaraba, int x, int y){
    int gridSize = morabaraba->size;
    SDL_Rect gridRect = morabaraba->gridRect;
    int k = 0;
    while((morabaraba->array[x][y]->neighbor[k] != NULL)&&(k<MAX_NEIGHBOR)){
        SDL_RenderDrawLine(morabaraba->renderer,
                            gridRect.w/gridSize*morabaraba->array[x][y]->x+gridRect.w/gridSize/2,
                            gridRect.h/gridSize*morabaraba->array[x][y]->y+gridRect.h/gridSize/2,
                            gridRect.w/gridSize*morabaraba->array[x][y]->neighbor[k]->x+gridRect.w/gridSize/2,
                            gridRect.h/gridSize*morabaraba->array[x][y]->neighbor[k]->y+gridRect.h/gridSize/2);
        k++;
    }
}

void SDL_DrawAllNeighbor(Morabaraba* morabaraba){
    for(int j=0; j<morabaraba->size; j++){
        for(int i=0; i<morabaraba->size; i++){
            if(morabaraba->array[i][j] != NULL){
                SDL_DrawNeighbor(morabaraba, i, j);
            }
        }
    }
}

Morabaraba* CreateMorabaraba(SDL_Renderer* renderer, int size, int playerNumber){
    int renderW, renderH;
    SDL_GetRendererOutputSize(renderer, &renderW, &renderH);
    Morabaraba* temp = malloc(sizeof(Morabaraba));
    temp->size = size;
    temp->playerNumber = playerNumber;
    temp->renderer = renderer;
    temp->array = CreateFrameArray(temp, size);
    for(int i=0; i<size; i++){
        if(i != (size-1)/2){
            temp->array[i][i] = CreateFrame(temp, i, i);
            temp->array[i][(size-1)-i] = CreateFrame(temp, i, (size-1)-i);
            temp->array[i][(size-1)/2] = CreateFrame(temp, i, (size-1)/2);
            temp->array[(size-1)/2][i] = CreateFrame(temp, (size-1)/2, i);
        }
    }
    SetAllNeighbor(temp);
    temp->mills = CreateMills(MAX_MILL);
    temp->players = CreatePlayers(playerNumber);
    temp->actualPlayer = 1;
    temp->countDown = 10;
    temp->winner = 0;
    SDL_SetRect(&temp->gridRect, 0, 0, renderH, renderH);
    SDL_SetRect(&temp->guiRect, renderH, 0, renderW-renderH, renderH);
    temp->gui = CreateGui(temp);
    return temp;
}

bool MoveCow(Morabaraba* morabaraba, int x1, int y1, int x2, int y2, bool flying){
    if((x1 == x2) && (y1 == y2)){
        return false;
    }
    if(IsInNeighbor(x2, y2, morabaraba->array[x1][y1])||flying){
        morabaraba->array[x2][y2]->value = morabaraba->array[x1][y1]->value;
        morabaraba->array[x1][y1]->value = 0;
        return true;
    }else
        return false;
}

bool SetCow(Morabaraba* morabaraba,int x, int y){
    if(morabaraba->array[x][y]!=NULL){
        if(morabaraba->players[morabaraba->actualPlayer-1]->cowInHand > 0){
            morabaraba->array[x][y]->value = morabaraba->actualPlayer;
            return true;
        }
    }
    return false;
}

void SDL_DrawAllCow(Morabaraba* morabaraba, SDL_Mouse* mouse){
    int gridSize = morabaraba->size;
    SDL_Rect gridRect = morabaraba->gridRect;
    for(int j=0; j<gridSize; j++){
        for(int i=0; i<gridSize; i++){
            if(morabaraba->array[i][j] != NULL){
                int x, y;
                if(morabaraba->array[i][j]->value == 1){
                    SDL_SetRenderDrawColor(morabaraba->renderer, 66, 33, 0, 255);
                }else if(morabaraba->array[i][j]->value == 2){
                    SDL_SetRenderDrawColor(morabaraba->renderer, 200, 100, 0, 255);
                }
                if(morabaraba->array[i][j]->value != 0){
                    if(morabaraba->array[i][j]->isMoving){
                        x = mouse->x;
                        y = mouse->y;
                        SDL_RenderFillCircle(morabaraba->renderer, x, y, gridRect.w/gridSize*0.25);
                    }else{
                        x = gridRect.w/gridSize*i+gridRect.w/gridSize/2;
                        y = gridRect.h/gridSize*j+gridRect.h/gridSize/2;
                        SDL_RenderFillCircle(morabaraba->renderer, x, y, gridRect.w/gridSize*0.2);
                    }
                }
            }
        }
    }
}

void PrintMorabaraba(Morabaraba* morabaraba){
    for(int j=0; j<morabaraba->size; j++){
        for(int i=0; i<morabaraba->size; i++){
            if(morabaraba->array[i][j] != NULL){
                printf(" %i ", morabaraba->array[i][j]->value);
            }else{
                printf("   ");
            }
        }
        printf("\n");
    }
}

void SDL_DrawMill(Morabaraba* morabaraba, Mill* mill){
    int gridSize = morabaraba->size;
    SDL_Rect gridRect = morabaraba->gridRect;
    for(int i=0; i<MILLSIZE; i++){
        if(mill->frames[i] != NULL){
            int x = gridRect.w/gridSize*mill->frames[i]->x+gridRect.w/gridSize/2;
            int y = gridRect.h/gridSize*mill->frames[i]->y+gridRect.h/gridSize/2;
            SDL_SetRenderDrawColor(morabaraba->renderer, 255, 0, 0, 255);
            SDL_RenderFillCircle(morabaraba->renderer, x, y, gridRect.w/gridSize*0.25);
        }
    }
}

void SDL_DrawAllMill(Morabaraba* morabaraba){
    for(int i=0; i<MAX_MILL; i++){
        if(morabaraba->mills[i] != NULL){
            SDL_DrawMill(morabaraba, morabaraba->mills[i]);
        }
    }
}

void KillCow(Morabaraba* morabaraba, int x, int y){
    morabaraba->players[morabaraba->array[x][y]->value-1]->cowTotalNumber--;
    morabaraba->array[x][y]->value = 0;
    morabaraba->players[morabaraba->actualPlayer-1]->isKiller = false;
}

void SDL_UpdateMorabaraba(Morabaraba* morabaraba, SDL_Mouse* mouse, bool clicked){
    int renderW, renderH;
    SDL_GetRendererOutputSize(morabaraba->renderer, &renderW, &renderH);
    SDL_SetRect(&morabaraba->gridRect, 0, 0, renderH, renderH);
    SDL_SetRect(&morabaraba->guiRect, renderH, 0, renderW-renderH, renderH);
    SDL_UpdateAllFrame(morabaraba, mouse);
    for(int j=0; j<morabaraba->size; j++){
        for(int i=0; i<morabaraba->size; i++){
            if(morabaraba->array[i][j] != NULL){
                if(!clicked){
                    if(morabaraba->array[i][j]->isSelected){
                        if(morabaraba->players[morabaraba->actualPlayer-1]->isKiller){
                            if(!PlayerIsOwner(morabaraba->array[i][j]->value, morabaraba->players[morabaraba->actualPlayer-1])){
                                if(morabaraba->array[i][j]->value != 0){
                                    KillCow(morabaraba, i, j);
                                    SwitchPlayer(&morabaraba->actualPlayer, morabaraba->playerNumber);
                                }
                            }
                        }else{
                            if(morabaraba->array[i][j]->value == 0){
                                if(SetCow(morabaraba, i, j)){
                                    morabaraba->players[morabaraba->actualPlayer-1]->cowInHand--;
                                    SwitchPlayer(&morabaraba->actualPlayer, morabaraba->playerNumber);
                                }
                            }else{
                                if(morabaraba->players[morabaraba->actualPlayer-1]->cowInHand==0){
                                    if(PlayerIsOwner(morabaraba->array[i][j]->value, morabaraba->players[morabaraba->actualPlayer-1])){
                                        morabaraba->array[i][j]->isMoving = true;
                                    }
                                }
                            }
                        }
                    }
                }
                if(morabaraba->array[i][j]->isMoving){
                    if(mouse->click != SDL_BUTTON_LMASK){
                        int x, y;
                        x = mouse->x/(morabaraba->gridRect.w/morabaraba->size);
                        y = mouse->y/(morabaraba->gridRect.h/morabaraba->size);
                        morabaraba->array[i][j]->isMoving = false;
                        if(morabaraba->array[x][y] != NULL){
                            if(morabaraba->array[x][y]->value == 0){
                                bool flying = morabaraba->players[morabaraba->actualPlayer-1]->cowTotalNumber<=3;
                                if(MoveCow(morabaraba, i, j, x, y, flying)){
                                    SwitchPlayer(&morabaraba->actualPlayer, morabaraba->playerNumber);
                                }
                            }
                        }
                    }
                }
                Mill* mill = SearchMill(morabaraba->array[i][j]);
                if(mill != NULL){
                    int k = IndexInMills(mill, morabaraba->mills);
                    if(k != -1){
                        CopyMill(morabaraba->mills[k], mill);
                    }else{
                        int l = 0;
                        while((l<MAX_MILL)&&(morabaraba->mills[l]->frames[0] != NULL)) l++;
                        CopyMill(morabaraba->mills[l], mill);
                        morabaraba->actualPlayer = morabaraba->array[i][j]->value;
                        morabaraba->players[morabaraba->actualPlayer-1]->isKiller = true;
                    }
                    FreeMill(mill);
                }else{
                    for(int k=0; k<MAX_MILL; k++){
                        if(!CheckMill(morabaraba->mills[k])){
                            for(int l=0; l<MILLSIZE; l++){
                                morabaraba->mills[k]->frames[l]=NULL;
                            }
                        }
                    }
                }
            }
        }
    }
    SDL_DrawAllNeighbor(morabaraba);
    SDL_DrawAllMill(morabaraba);
    SDL_DrawAllCow(morabaraba, mouse);
    SDL_UpdateGui(morabaraba);
}

void FreeMorabaraba(Morabaraba* morabaraba){
    FreeFrameArray(morabaraba->array, morabaraba->size);
    FreePlayers(morabaraba->players, morabaraba->playerNumber);
    FreeMills(morabaraba->mills, MAX_MILL);
    SDL_DestroyRenderer(morabaraba->renderer);
    free(morabaraba);
}