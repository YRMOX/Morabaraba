#ifndef MORABARABA_GUI_H
#define MORABARABA_GUI_H

/**
 * @brief structure Gui qui contient tous les textes à affiché
 */
typedef struct Gui Gui;
#include "Morabaraba.h"
#include "Morabaraba_SDL.h"

struct Gui{
    SDL_Text* actualPlayer;
    SDL_Text** cowInHand;
    SDL_Text** cowTotalNumber;
    SDL_Text* EndText;
};

/**
 * @brief Création de la structure Gui
 * 
 * @param morabaraba Morabaraba qui contient toutes les donnés pour la création 
 * de la structure
 * @return Adresse de la structure alloué
 */
Gui* CreateGui(Morabaraba* morabaraba);

/**
 * @brief Mise à jour du texte du Gui avec les valeurs contenu dans le Morabaraba 
 * 
 * @param morabaraba Morabaraba qui contient les valeurs à affiché et les
 * paramètres d'affichage
 */
void SDL_UpdateGui(Morabaraba* morabaraba);

/**
 * @brief Désallocation de la structure Gui
 * 
 * @param gui structure a Désalloué
 */
void FreeGui(Gui* gui);

#endif