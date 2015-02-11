#include "fetchStage.h"
#include "tools.h"

// @file    fetchStage.c
// @author  given
// @brief   the fetch stage of yess. given.

// F register holds the input for the fetch stage. 
// it is only accessible from this file. (static)
static fregister F;

// @func    getFregister
// @brief   returns a copy of the F register.
// @return  fregister
fregister getFregister()
{
    return F;
}

// @func    clearFregister
// @brief   returns a copy of the F register.
// @mod     F 
void clearFregister()
{
    clearBuffer((char *) &F, sizeof(F));
}
