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

#endif