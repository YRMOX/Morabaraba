#include "Morabaraba_Mill.h"
#include <stdlib.h>

Mill* CreateMill(){
    Mill* temp = malloc(sizeof(Mill));
    temp->frames = malloc(sizeof(Frame*)*MILLSIZE);
    for(int i=0; i<MILLSIZE; i++) temp->frames = NULL;
    return temp;
}

Mill* SearchMill(Frame* middle){
    int player = -1;
    if(middle->value != 0){
        player = middle->value;
    }
    for(int i=0; (middle->neighbor[i]!=NULL)&&(i<MAX_NEIGHBOR); i++){
        if(middle->neighbor[i]->value == player){
            int x = middle->neighbor[i]->x-middle->x;
            int y = middle->neighbor[i]->y-middle->y;
            for(int j=0; (middle->neighbor[j]!=NULL)&&(j<MAX_NEIGHBOR); j++){
                if(middle->neighbor[j]->value == player){
                    if((middle->neighbor[j]->x == middle->x-x)&&(middle->neighbor[j]->y == middle->y-y)){
                        Mill* temp = CreateMill();
                        temp->frames[0] = middle;
                        temp->frames[1] = middle->neighbor[i];
                        temp->frames[2] = middle->neighbor[j];
                        return temp;
                    }
                }
            }
        }
    }
    return NULL;
}

void CopyMill(Mill* millA, Mill* millB){
    for(int i=0; i<MILLSIZE; i++){
        millA->frames[i] = millB->frames[i];
    }
}

bool CmpMill(Mill* millA, Mill* millB){
    bool temp = true;
    for(int i=0; i<MILLSIZE; i++){
        if(millA->frames[i] != millB->frames[i]){
            temp = false;
        }
    }
    return temp;
}

void FreeMill(Mill* mill){
    free(mill->frames);
    free(mill);
}