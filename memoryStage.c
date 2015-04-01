#include "forwarding.h"
#include "memoryStage.h"
#include "tools.h"
#include "instructions.h"
#include "writebackStage.h"

// @file    memoryStage.c
// @author  rhoadskj
// @brief   the memory stage for yess.

// M register holds the input for the memory stage.
// it is only accessible from this file. (static)
static mregister M;

// @func    memoryStage
// @brief   The driver function
void memoryStage()
{
  updateWregister(M.stat, M.icode, M.Cnd, M.valE, M.valA, M.dstE, M.dstM);
}

// @func    updateMRegister
// @brief   Updates the values stored in dregisterD
int updateMregister(int stat, int icode, int Cnd, int valE, int valA, int dstE, int dstM)
{
    M.stat = stat;
    M.icode = icode;
    M.Cnd = Cnd;
    M.valE = valE;
    M.valA = valA;
    M.dstE = dstE;
    M.dstM = dstM;
}

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
