#include "executeStage.h"
#include "tools.h"
#include "instructions.h"
#include "memoryStage.h"

// @file    executeStage.c
// @author  rhoadskj
// @brief   the execute stage for yess.

// E register holds the input for the execute stage.
// it is only accessible from this file. (static)
static eregister E;
int (*e[16])();

// @func    executeStage
// @brief   The driver function
void executeStage(){
  unsigned int valE, valM;
  //temp assignment
  valE = valM = 0;
  valE = (*e[E.ifun])();
  //needs to calculate CND
    updateMregister(E.stat, E.icode, 0, valE, E.valA, E.dstE, E.dstM);
  }

  void initializeFuncPtrArray(){
  int i = 0;
  for(; i < 16; i++){
    e[i] = temp;
  }
  e[DUMP] = dump;
}

int dump(){
  return E.valC;
}

int temp(){
  return 0;
}

// @func    updateERegister
// @brief   Updates the values stored in dregisterD
int updateEregister(int stat, int icode, int ifun, int rA, int rB, int valC,
                    int valA, int valB, int dstE, int dstM, int srcA, int srcB)
{
  E.stat = stat;
  E.icode = icode;
  E.ifun = ifun;
  E.rA = rA;
  E.rB = rB;
  E.valC = valC;
  E.valA = valA;
  E.valB = valB;
  E.dstE = dstE;
  E.dstM = dstM;
  E.srcA = srcA;
  E.srcB = srcB;
}

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
