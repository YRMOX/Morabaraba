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