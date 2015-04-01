#include "tools.h"
#include "forwarding.h"
#include "instructions.h"
#include "registers.h"
#include "executeStage.h"
#include "decodeStage.h"

// @file    decodeStage.c
// @author  rhoadskj
// @brief   the decode stage for yess.

// D register holds the input for the decode stage.
// it is only accessible from this file. (static)
static dregister D;

// @func    decodeStage
// @brief   The driver function
void decodeStage(forwardType fwd){
    updateEregister(D.stat, D.icode, D.ifun, D.rA, D.rB, D.valC, 0, 0, 0xf, 0xf, 0xf, 0xf);
}

// @func    updateDRegister
// @brief   Updates the values stored in dregisterD
int updateDregister(int stat, int icode, int ifun, int rA, int rB, int valC, int valP){
  D.stat = stat;
  D.icode = icode;
  D.ifun = ifun;
  D.rA = rA;
  D.rB = rB;
  D.valC = valC;
  D.valP = valP;
}

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

int getSrcA(){
  switch(D.icode){
    case OPL:
    case RMMOVL:
    case MRMOVL:
    case PUSHL:
      return D.rA;
      break;
    case POPL:
    case RET:
      return ESP;
      break;
    default:
      return RNONE;
      break;
  }
}

int getSrcB(){
  switch(D.icode){
    case OPL:
    case RMMOVL:
    case MRMOVL:
      return D.rA;
      break;
    case PUSHL:
    case POPL:
    case CALL:
    case RET:
      return ESP;
      break;
    default:
      return RNONE;
      break;
  }
}

int getDstE(){
  switch(D.icode){
    case OPL:
    case RRMOVL:
    case IRMOVL:
      return D.rB;
      break;
    case PUSHL:
    case POPL:
    case CALL:
    case RET:
      return ESP;
      break;
    default:
      return RNONE;
      break;
  }
}

int getDstM(){
  switch(D.icode){
    case POPL:
    case MRMOVL:
      return D.rA;
      break;
    default:
      return RNONE;
      break;
  }
}

selectFwdA(forwardType fwd){
  if(D.rA == RNONE) return 0;
  if(D.rA == fwd.W_dstE) return fwd.W_valE;
  return getRegister(D.rA);
}

selectFwdB(forwardType fwd){
  if(D.rA == RNONE) return 0;
  if(D.rB == fwd.W_dstE) return fwd.W_valE;
  return getRegister(D.rB);
}
