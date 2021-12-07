#ifndef MORABARABA_MILL_H
#define MORABARABA_MILL_H

#define MILLSIZE 3

typedef struct Mill Mill;
#include "Morabaraba_Frame.h"
#include <stdbool.h>

struct Mill{
    Frame** frames;
};

Mill* CreateMill();
Mill* SearchMill(Frame* middle);
void CopyMill(Mill* millA, Mill* millB);
bool CmpMill(Mill* millA, Mill* millB);
void FreeMill(Mill* mill);

bool isInMills(Mill* mill, Mill** mills);

#endif