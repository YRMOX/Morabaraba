#include "Morabaraba_Save.h"
#include <stdio.h>

int LoadInt(char* currentDir){
    char path[40];
    char temp[20] = "save.data";
    char file[20];
    strcpy(path, currentDir);
    strcat(path, temp);
    FILE* save = fopen(path, "rb");
    fread(file, 20, 1, save);
    fclose(save);
    int var = (int)file[0];
    return var;
}

void SaveInt(int var, char* currentDir){
    char path[40];
    char temp[20] = "save.data";
    strcpy(path, currentDir);
    strcat(path, temp);
    FILE* save = fopen(path, "wb");
    fwrite(&var, 1, 1, save);
    fclose(save);
}

int* LoadIntTab(char* currentDir){
    char path[40];
    char temp[20] = "save.data";
    char file[100] = {0};
    strcpy(path, currentDir);
    strcat(path, temp);
    FILE* save = fopen(path, "rb");
    fread(file, 100, 1, save);
    fclose(save);
    int* var = malloc(sizeof(int)*100);
    for(int i=0; i<100; i++){
        var[i] = file[i];
    }
    return var;
}

void SaveIntTab(int* var, int size, char* currentDir){
    char path[40];
    char temp[20] = "save.data";
    strcpy(path, currentDir);
    strcat(path, temp);
    FILE* save = fopen(path, "wb");
    for(int i=0; i<20; i++){
        fwrite(&var[0], 1, 1, save);
    }
    fclose(save);
}

Morabaraba* LoadMorabaraba(SDL_Renderer* renderer, char* currentDir){
    char path[40];
    char temp[20] = "save.data";
    strcpy(path, currentDir);
    strcat(path, temp);
    FILE* save = fopen(path, "rb");
    int size = (int)fgetc(save);
    Morabaraba* morabaraba = CreateMorabaraba(renderer, size, 2);
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
    for(int i=0; i<morabaraba->size; i++){
        for(int j=0; j<morabaraba->size; j++){
            if(morabaraba->array[i][j] != NULL){
                fprintf(save, "%c", (char)morabaraba->array[i][j]->value);
            }
        }
    }
    fclose(save);
}