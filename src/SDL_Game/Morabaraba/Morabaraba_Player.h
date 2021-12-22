#ifndef MORABARABA_PLAYER_H
#define MORABARABA_PLAYER_H

#include <stdbool.h>

/**
 * @brief Structure qui contient toutes les valeurs associé au joueur
 */
typedef struct Player Player;
struct Player{
    bool isKiller;
    int id;
    int cowInHand;
    int cowTotalNumber;
};

/**
 * @brief Création d'une structure joueur
 * 
 * @param id identifiant du Joueur
 * @return Adresse de la structure joueur
 */
Player* CreatePlayer(int id);

/**
 * @brief Vérifie si la valeur donné est bien l'identifiant du joueur
 * 
 * @param value valeur à tester
 * @param player structure du joueur à comparé
 * @return vrai si la valeur est égal à l'identifiant du joueur
 * @return faux si la valeur n'est égal pas à l'identifiant du joueur
 */
bool PlayerIsOwner(int value, Player* player);
void FreePlayer(Player* player);

Player** CreatePlayers(int playerNumber);
void SwitchPlayer(int* actualPlayer, int playerNumber);
void FreePlayers(Player** players, int playerNumber);

#endif