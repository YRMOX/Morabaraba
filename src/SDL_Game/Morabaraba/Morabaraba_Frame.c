#include "Morabaraba_Frame.h"
#include <stdio.h>
#include <stdlib.h>

Frame* CreateFrame(Morabaraba* morabaraba, int x, int y){
    int renderW, renderH;
    SDL_GetRendererOutputSize(morabaraba->renderer, &renderW, &renderH);
    Frame* temp_frame = malloc(sizeof(Frame));
    temp_frame->x = x;
    temp_frame->y = y;
    temp_frame->value = 0;
    temp_frame->neighbor = malloc(sizeof(Frame*)*MAX_NEIGHBOR);
    for(int i=0; i<MAX_NEIGHBOR; i++) temp_frame->neighbor[i] = NULL;
    temp_frame->rect.x = renderW/morabaraba->size*x;
    temp_frame->rect.y = renderH/morabaraba->size*y;
    temp_frame->rect.w = renderW/morabaraba->size;
    temp_frame->rect.h = renderH/morabaraba->size;
    temp_frame->isSelected = false;
    temp_frame->isMoving = false;
    temp_frame->renderer = morabaraba->renderer;
    return temp_frame;
}

void FreeFrame(Frame* frame){
    free(frame->neighbor);
    free(frame);
}

Frame** CreateFrames(int size){
    Frame** frames = malloc(sizeof(Frame*)*size);
    for(int i=0; i<size; i++) frames[i] = NULL;
    return frames;
}

void FreeFrames(Frame** frames, int size){
    for(int i=0; i<size; i++) FreeFrame(frames[i]);
    free(frames);
}

Frame*** CreateFrameArray(Morabaraba* morabaraba, int size){
    Frame*** array = malloc(sizeof(Frame**)*size);
    for(int i=0; i<size; i++){
        array[i] = malloc(sizeof(Frame*)*size);
        for(int j=0; j<size; j++){
            array[i][j] = NULL;
        }
    }
    return array;
}

void FreeFrameArray(Frame*** array, int size){
    for(int i=0; i<size; i++) FreeFrames(array[i], size);
    free(array);
}

int IndexInFrames(Frame* frame, Frame** frames){
    int temp = -1;
    for(int i=0; i<MILLSIZE; i++){
        if(frames[i]==frame){
            temp = i;
        }
    }
    return temp;
}

void PrintNeighbor(Frame* frame){
    for(int i=0; i<4; i++){
        if(frame->neighbor[i] != NULL){
            if((frame->neighbor[i+1] == NULL)||(i > 4)){
                printf("%i %i", frame->neighbor[i]->x, frame->neighbor[i]->y);
            }else{
                printf("%i %i, ", frame->neighbor[i]->x, frame->neighbor[i]->y);
            }
        }
    }
    printf("\n");
}

void AppendNeighbor(Frame* frame, Frame* frameToAppend){
    int k=0;
    while((frame->neighbor[k] != 0)&&(k<4-1)){
        k++;
    }
    frame->neighbor[k] = frameToAppend;
}

bool IsInNeighbor(int x, int y, Frame* frame){
    int k=0;
    while((frame->neighbor[k] != 0)&&(k<4)){
        if((frame->neighbor[k]->x == x)&&(frame->neighbor[k]->y == y))
            return true;
        k++;
    }
    return false;
}

void SDL_UpdateFrame(Morabaraba* morabaraba, Frame *frame, SDL_Mouse* mouse){
    int renderW, renderH;
    SDL_GetRendererOutputSize(frame->renderer, &renderW, &renderH);
    frame->rect.x = renderW/morabaraba->size*frame->x;
    frame->rect.y = renderH/morabaraba->size*frame->y;
    frame->rect.w = renderW/morabaraba->size;
    frame->rect.h = renderH/morabaraba->size;
    frame->isSelected = false;
    if((mouse->x >= frame->rect.x) && (mouse->x <= frame->rect.x+frame->rect.w) && (mouse->y >= frame->rect.y) && (mouse->y <= frame->rect.y+frame->rect.h)){
            if(mouse->click == SDL_BUTTON_LMASK) {
                frame->isSelected = true;
            }
    }
    SDL_SetRenderDrawColor(frame->renderer, 0, 0, 0, 0);
    SDL_RenderFillCircle(frame->renderer, renderW/7*frame->x+renderW/14, renderH/7*frame->y+renderH/14, 0.25);
}

void SDL_UpdateAllFrame(Morabaraba* morabaraba, SDL_Mouse* mouse){
    for(int j=0; j<morabaraba->size; j++){
        for(int i=0; i<morabaraba->size; i++){
            if(morabaraba->array[i][j] != NULL){
                SDL_UpdateFrame(morabaraba, morabaraba->array[i][j], mouse);
            }
        }
    }
}