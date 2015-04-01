#include "memory.h"
#include "registers.h"
#include "forwarding.h"
#include "fetchStage.h"
#include "instructions.h"
#include "decodeStage.h"

// @file    fetchStage.c
// @author  rhoadskj
// @brief   the fetch stage of yess. given.

// F register holds the input for the fetch stage.
// it is only accessible from this file. (static)
static fregister F;

// @func    fetchStage
// @brief   The driver function
void fetchStage()
{
  //values to be passed to decodeStage
  unsigned int stat, icode, ifun, rA, rB, valC, valP;
  unsigned int f_pc;
  unsigned int opcode;
  bool memErr;
  valC = rA = rB = 0;
  f_pc = F.predPC;
  opcode = getByte(f_pc, &memErr);
  icode = opcode & 0x000000F0;
  ifun = opcode & 0x0000000F;
  stat = getStatus(&memErr, icode);
  if(needRegids(icode)){
    rA = getByte(f_pc+1, &memErr);
    rB = getByte(f_pc+2, &memErr);
  }
  if(needValC(icode)){
    int i = (icode == JMP || icode == CALL) ? 3 : 4;
    int end = i + 4;
    for(; i < end; i++){
      valC += getByte(f_pc + i, &memErr);
      valC << 2;
    }
  }
  //use instruction and f_pc to figure out below values

  updateDregister(stat, icode, ifun, rA, rB, valC, valP);
  F.predPC = predictPC(F.predPC, icode);
}

unsigned int getStatus(bool *memErr, unsigned int icode){
  if (*memErr) return SADR;
  if (!isValidInstr(icode)) return SINS;
  if (icode == HALT) return SHLT;
  return SAOK;
}
bool isValidInstr(icode){
  if(icode > 12) return false;
  return true;
}

bool needRegids(icode){
  if(icode == RRMOVL) return true;
  if(icode == OPL)    return true;
  if(icode == PUSHL)  return true;
  if(icode == POPL)   return true;
  if(icode == IRMOVL) return true;
  if(icode == RMMOVL) return true;
  if(icode == MRMOVL) return true;
  return false;
}

bool needValC(icode){
  if(icode == IRMOVL) return true;
  if(icode == RMMOVL) return true;
  if(icode == MRMOVL) return true;
  if(icode == JMP)    return true;
  if(icode == CALL)   return true;
  return false;
}

// @func    predictPC
// @brief   predictions the next predPC
unsigned int predictPC(unsigned int pastPC, unsigned int icode)
{
  int newPC;
  newPC++;
  if(needRegids(icode))
    newPC += 2;
  if(needValC(icode))
    newPC += 4;
  return newPC;
}

unsigned int selectPC(){
  return F.predPC;
}

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
