#include "Morabaraba_Player.h"
#include <stdlib.h>

Player* CreatePlayer(int id){
    Player* temp = malloc(sizeof(Player));
    temp->isKiller = false;
    temp->id = id;
    temp->cowInHand = 12;
    temp->cowTotalNumber = temp->cowInHand;
    return temp;
}

bool PlayerIsOwner(int value, Player* player){
    return value == player->id;
}

void FreePlayer(Player* player){
    free(player);
}

Player** CreatePlayers(int playerNumber){
    Player** players = malloc(sizeof(Player*)*playerNumber);
    for(int i=0; i<playerNumber; i++) players[i] = CreatePlayer(i+1);
    return players;
}

void SwitchPlayer(int* actualPlayer, int playerNumber){
    if(*actualPlayer >= playerNumber){
        *actualPlayer = 1;
    }else{
        (*actualPlayer)++;
    }
}

void FreePlayers(Player** players, int playerNumber){
    for(int i=0; i<playerNumber; i++) FreePlayer(players[i]);
    free(players);
}