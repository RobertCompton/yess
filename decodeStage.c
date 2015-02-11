#include "decodeStage.h"
#include "tools.h"

// @file    decodeStage.c
// @author  rhoadskj
// @brief   the decode stage for yess.

// D register holds the input for the decode stage. 
// it is only accessible from this file. (static)
static dregister D;

// @func    getDregister
// @brief   returns a copy of the D register.
// @return  dregister
dregister getDregister()
{
    return D;
}

// @func    clearDregister
// @brief   returns a copy of the D register.
// @mod     D
void clearDregister()
{
    clearBuffer((char *) &D, sizeof(D));
}
