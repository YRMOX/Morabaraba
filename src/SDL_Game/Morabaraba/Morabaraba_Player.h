#ifndef MORABARABA_PLAYER_H
#define MORABARABA_PLAYER_H

typedef struct Player Player;
struct Player{
    int id;
    int cowInHand;
    int cowTotalNumber;
};

Player* CreatePlayer(int id);

#endif