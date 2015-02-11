#include "memoryStage.h"
#include "tools.h"

// @file    memoryStage.c
// @author  rhoadskj
// @brief   the memory stage for yess.

// M register holds the input for the memory stage.
// it is only accessible from this file. (static)
static mregister M;

// @func    getMregister
// @brief   returns a copy of the M register.
// @return  mregister
mregister getMregister()
{
    return M;
}

// @func    clearMregister
// @brief   returns a copy of the M register.
// @mod     M
void clearMregister()
{
    clearBuffer((char *) &M, sizeof(M));
}
