#ifndef MORABARABA_PLAYER_H
#define MORABARABA_PLAYER_H

#include <stdbool.h>
typedef struct Player Player;
struct Player{
    bool isKiller;
    int id;
    int cowInHand;
    int cowTotalNumber;
};

Player* CreatePlayer(int id);
bool PlayerIsOwner(int value, Player* player);
void FreePlayer(Player* player);

Player** CreatePlayers(int playerNumber);
void SwitchPlayer(int* actualPlayer, int playerNumber);
void FreePlayers(Player** players, int playerNumber);

#endif