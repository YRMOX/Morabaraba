#ifndef MORABARABA_SAVE_H
#define MORABARABA_SAVE_H

#include "Morabaraba.h"
#include <SDL2/SDL.h>


/**
 * @brief Crée une structure Morobaraba avec les valeurs stocké dans le fichier save.data
 * 
 * @return une structure Morabaraba
 * 
 * @param currentDir Emplacement du fichier où se situe le fichier save.data
 */
Morabaraba* LoadMorabaraba(SDL_Renderer* renderer, char* currentDir);

/**
 * @brief Sauvegarde les valeurs contenue dans la structure Morabaraba dans le
 * fichier save.data
 * 
 * @param morabaraba Structure Morabaraba à sauvegardé
 * @param currentDir Emplacement du fichier où se situe le fichier save.data
 */
void SaveMorabaraba(Morabaraba* morabaraba, char* currentDir);

#endif