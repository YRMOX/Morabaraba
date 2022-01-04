#include "Morabaraba_Mill.h"
#include <stdlib.h>

Mill* CreateMill(){
    Mill* temp = malloc(sizeof(Mill));
    temp->frames = CreateFrames(MILLSIZE);
    return temp;
}

Mill* SearchMill(Frame* middle){
    int player = -1;
    if(middle->value != 0){
        player = middle->value;
    }
    for(int i=0; (middle->neighbor[i]!=NULL)&&(i<MAX_NEIGHBOR); i++){
        if(middle->neighbor[i]->value == player){
            int x = middle->neighbor[i]->x - middle->x;
            int y = middle->neighbor[i]->y - middle->y;
            for(int j=0; (middle->neighbor[j]!=NULL)&&(j<MAX_NEIGHBOR); j++){
                if(middle->neighbor[j]->value == player){
                    if((middle->neighbor[j]->x == middle->x-x)&&(middle->neighbor[j]->y == middle->y-y)){
                        Mill* temp = CreateMill();
                        temp->frames[0] = middle;
                        temp->frames[1] = middle->neighbor[i];
                        temp->frames[2] = middle->neighbor[j];
                        for(int i=0; i<MILLSIZE; i++)
                            temp->frames[i]->isProtected = true;
                        return temp;
                    }
                }
            }
        }
    }
    return NULL;
}

bool CheckMill(Mill* mill){
    bool temp = true;
    for(int i=1; i<MILLSIZE; i++){
        if((mill->frames[i-1]!=NULL)||(mill->frames[i]!=NULL)){
            if(mill->frames[i-1]->value!=mill->frames[i]->value){
                temp = false;
            }
        }
    }
    return temp;
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

void DestructMill(Mill* mill){
    for(int i=0; i<MILLSIZE; i++){
        mill->frames[i]->isProtected = false;
        mill->frames[i]=NULL;
    }
}

void FreeMill(Mill* mill){
    free(mill->frames);
    free(mill);
}

Mill** CreateMills(int size){
    Mill** mills = malloc(sizeof(Mill*)*size);
    for(int i=0; i<size; i++) mills[i] = CreateMill();
    return mills;
}

int IndexInMills(Mill* mill, Mill** mills){
    int temp = -1;
    for(int i=0; i<MAX_MILL; i++){
        if(CmpMill(mills[i], mill)){
            temp = i;
        }
    }
    return temp;
}

void FreeMills(Mill** mills, int size){
    for(int i=0; i<size; i++) FreeMill(mills[i]);
    free(mills);
}