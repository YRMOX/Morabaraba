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
    int renderW, renderH;
    SDL_GetRendererOutputSize(morabaraba->renderer, &renderW, &renderH);
    int k = 0;
    while((morabaraba->array[x][y]->neighbor[k] != NULL)&&(k<MAX_NEIGHBOR)){
        SDL_RenderDrawLine(morabaraba->renderer,
                            renderW/7*morabaraba->array[x][y]->x+renderW/14,
                            renderH/7*morabaraba->array[x][y]->y+renderH/14,
                            renderW/7*morabaraba->array[x][y]->neighbor[k]->x+renderW/14,
                            renderH/7*morabaraba->array[x][y]->neighbor[k]->y+renderH/14);
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
    Morabaraba* temp = malloc(sizeof(Morabaraba));
    temp->size = size;
    temp->renderer = renderer;
    temp->array = malloc(sizeof(Frame**)*size);
    for(int i=0; i<size; i++){
        temp->array[i] = malloc(sizeof(Frame*)*size);
        for(int j=0; j<size; j++){
            temp->array[i][j] = NULL;
        }
    }
    for(int i=0; i<size; i++){
        if(i != (size-1)/2){
            temp->array[i][i] = CreateFrame(temp, i, i);
            temp->array[i][(size-1)-i] = CreateFrame(temp, i, (size-1)-i);
            temp->array[i][(size-1)/2] = CreateFrame(temp, i, (size-1)/2);
            temp->array[(size-1)/2][i] = CreateFrame(temp, (size-1)/2, i);
        }
    }
    SetAllNeighbor(temp);
    temp->mills = malloc(sizeof(Mill*)*MAX_MILL);
    for(int i=0; i<MAX_MILL; i++){
        temp->mills[i] = CreateMill();
    }
    temp->players = malloc(sizeof(Player*)*playerNumber);
    for(int i=0; i<playerNumber; i++) temp->players[i] = CreatePlayer(i+1);
    temp->actualPlayer = 1;
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
    int renderW, renderH;
    SDL_GetRendererOutputSize(morabaraba->renderer, &renderW, &renderH);
    for(int j=0; j<morabaraba->size; j++){
        for(int i=0; i<morabaraba->size; i++){
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
                        SDL_RenderFillCircle(morabaraba->renderer, x, y, 0.25);
                    }else{
                        x = renderW/morabaraba->size*i+renderW/(2*morabaraba->size);
                        y = renderH/morabaraba->size*j+renderH/(2*morabaraba->size);
                        SDL_RenderFillCircle(morabaraba->renderer, x, y, 0.2);
                    }
                }
            }
        }
    }
}

void SwitchPlayer(Morabaraba* morabaraba){
    if(morabaraba->actualPlayer == 1){
        morabaraba->actualPlayer = 2;
    }else if(morabaraba->actualPlayer == 2){
        morabaraba->actualPlayer = 1;
    }
}

bool PlayerIsOwner(Frame* frame, int player){
    return (frame->value == player)?true:false;
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
    int renderW, renderH;
    SDL_GetRendererOutputSize(morabaraba->renderer, &renderW, &renderH);
    for(int i=0; i<MILLSIZE; i++){
        if(mill->frames[i] != NULL){
            int x = renderW/morabaraba->size*mill->frames[i]->x+renderW/(2*morabaraba->size);
            int y = renderH/morabaraba->size*mill->frames[i]->y+renderH/(2*morabaraba->size);
            SDL_SetRenderDrawColor(morabaraba->renderer, 255, 0, 0, 255);
            SDL_RenderFillCircle(morabaraba->renderer, x, y, 0.25);
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

int IndexFrameInMills(Frame* frame, Mill** mills){
    int temp = -1;
    for(int i=0; i<MAX_MILL; i++){
        if(IndexInFrames(frame, mills[i]->frames)!=-1){
            temp = i;
        }
    }
    return temp;
}

void SDL_UpdateMorabaraba(Morabaraba* morabaraba, SDL_Mouse* mouse, bool clicked){
    int renderW, renderH;
    SDL_GetRendererOutputSize(morabaraba->renderer, &renderW, &renderH);
    SDL_UpdateAllFrame(morabaraba, mouse);
    for(int j=0; j<morabaraba->size; j++){
        for(int i=0; i<morabaraba->size; i++){
            if(morabaraba->array[i][j] != NULL){
                if(!clicked){
                    if(morabaraba->array[i][j]->isSelected){
                        if(morabaraba->players[morabaraba->actualPlayer-1]->isKiller){
                            if(!PlayerIsOwner(morabaraba->array[i][j], morabaraba->actualPlayer)){
                                if(morabaraba->array[i][j]->value != 0){
                                    KillCow(morabaraba, i, j);
                                    SwitchPlayer(morabaraba);
                                }
                            }
                        }else{
                            if(morabaraba->array[i][j]->value == 0){
                                if(SetCow(morabaraba, i, j)){
                                    morabaraba->players[morabaraba->actualPlayer-1]->cowInHand--;
                                    SwitchPlayer(morabaraba);
                                }
                            }else{
                                if(morabaraba->players[morabaraba->actualPlayer-1]->cowInHand==0){
                                    if(PlayerIsOwner(morabaraba->array[i][j], morabaraba->actualPlayer)){
                                        morabaraba->array[i][j]->isMoving = true;
                                    }
                                }
                            }
                        }
                    }
                }
                if(morabaraba->array[i][j]->isMoving){
                    if(mouse->click != SDL_BUTTON_LMASK){
                        int x = mouse->x/(renderW/7), y = mouse->y/(renderH/7);
                        morabaraba->array[i][j]->isMoving = false;
                        if(morabaraba->array[x][y] != NULL){
                            if(morabaraba->array[x][y]->value == 0){
                                bool flying = morabaraba->players[morabaraba->actualPlayer-1]->cowTotalNumber<=3;
                                printf("%i", morabaraba->players[morabaraba->actualPlayer-1]->cowTotalNumber);
                                if(MoveCow(morabaraba, i, j, x, y, flying)){
                                    SwitchPlayer(morabaraba);
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
    //printf("%i\n", morabaraba->players[morabaraba->actualPlayer-1]->cowInHand);
    SDL_DrawAllNeighbor(morabaraba);
    SDL_DrawAllMill(morabaraba);
    SDL_DrawAllCow(morabaraba, mouse);
}

void FreeMorabaraba(Morabaraba* morabaraba){
    int size = morabaraba->size;
    for(int i=0; i<size; i++){
        if(i != (size-1)/2){
            FreeFrame(morabaraba->array[i][i]);
            FreeFrame(morabaraba->array[i][(size-1)-i]);
            FreeFrame(morabaraba->array[i][(size-1)/2]);
            FreeFrame(morabaraba->array[(size-1)/2][i]);
        }
    }
    for(int i=0; i<size; i++){
        free(morabaraba->array[i]);
    }
    free(morabaraba->array);
    
    free(morabaraba);
}