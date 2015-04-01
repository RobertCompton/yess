#include "forwarding.h"
#include "tools.h"
#include "instructions.h"
#include "dump.h"
#include "writebackStage.h"

// @file    writebackStage.c
// @author  rhoadskj
// @brief   the writeback stage for yess.

// W register holds the input for the writeback stage.
// it is only accessible from this file. (static)
static wregister W;

// @func    writebackStage
// @brief   The driver function
bool writebackStage(forwardType *fwd){
  //set values for forwarding
  fwd->W_dstE = W.dstE;
  fwd->W_valE = W.valE;

  switch(W.icode){
    case(DUMP):
      if(W.valE & 0x00000001) dumpProgramRegisters();
      if(W.valE & 0x00000002) dumpProcessorRegisters();
      if(W.valE & 0x00000004) dumpMemory();
      break;
    default:
      return;
      break;
  }
}

// @func    updateWRegister
// @brief   Updates the values stored in dregisterD
int updateWregister(int stat, int icode, int Cnd, int valE, int valM, int dstE, int dstM){
    W.stat = stat;
    W.icode = icode;
    W.valE = valE;
    W.valM = valM;
    W.dstE = dstE;
    W.dstM = dstM;
}

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
