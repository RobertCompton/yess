#include "writebackStage.h"
#include "tools.h"

// @file    writebackStage.c
// @author  rhoadskj
// @brief   the writeback stage for yess.

// W register holds the input for the writeback stage.
// it is only accessible from this file. (static)
static wregister W;

// @func    getWregister
// @brief   returns a copy of the W register.
// @return  wregister
wregister getWregister()
{
    return W;
}

// @func    clearWregister
// @brief   returns a copy of the W register.
// @mod     W
void clearWregister()
{
    clearBuffer((char *) &W, sizeof(W));
}
