#include "executeStage.h"
#include "tools.h"

// @file    executeStage.c
// @author  rhoadskj
// @brief   the execute stage for yess.

// E register holds the input for the execute stage. 
// it is only accessible from this file. (static)
static eregister E;

// @func    getEregister
// @brief   returns a copy of the E register.
// @return  eregister
eregister getEregister()
{
    return E;
}

// @func    clearEregister
// @brief   returns a copy of the E register.
// @mod     E
void clearEregister()
{
    clearBuffer((char *) &E, sizeof(E));
}
