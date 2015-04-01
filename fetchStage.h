#include "tools.h"
#ifndef FETCHSTAGE_H
#define FETCHSTAGE_H
typedef struct
{
    unsigned int predPC;
} fregister;

//prototypes for functions called from files other than fetchStage
fregister getFregister();
void clearFregister();
void fetchStage();
unsigned int getStatus(bool *, unsigned int);
bool isValidInstr(int);
bool needRegids(int);
bool needValC(int);
unsigned int predictPC(unsigned int, unsigned int);
#endif
