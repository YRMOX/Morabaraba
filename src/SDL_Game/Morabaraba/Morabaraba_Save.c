#include "Morabaraba_Save.h"
#include <stdio.h>

Morabaraba* LoadMorabaraba(SDL_Renderer* renderer, char* currentDir){
    char path[40];
    char temp[20] = "save.data";
    strcpy(path, currentDir);
    strcat(path, temp);
    FILE* save = fopen(path, "rb");
    int size = (int)fgetc(save);
    int playerNumber = (int)fgetc(save);
    Morabaraba* morabaraba = CreateMorabaraba(renderer, size, playerNumber);
    for(int i=0; i<size; i++){
        for(int j=0; j<size; j++){
            if(morabaraba->array[i][j] != NULL){
                morabaraba->array[i][j]->value = (int)fgetc(save);
            }
        }
    }
    fclose(save);
    return morabaraba;
}

void SaveMorabaraba(Morabaraba* morabaraba, char* currentDir){
    char path[40];
    char temp[20] = "save.data";
    strcpy(path, currentDir);
    strcat(path, temp);
    FILE* save = fopen(path, "wb+");
    fprintf(save, "%c", (char)morabaraba->size);
    fprintf(save, "%c", (char)2);
    for(int i=0; i<morabaraba->size; i++){
        for(int j=0; j<morabaraba->size; j++){
            if(morabaraba->array[i][j] != NULL){
                fprintf(save, "%c", (char)morabaraba->array[i][j]->value);
            }
        }
    }
    fclose(save);
}