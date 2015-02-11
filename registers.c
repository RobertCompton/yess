#include <stdio.h>
#include <stdbool.h>
#include "tools.h"
#include "registers.h"

// @file    registers.c
// @author  comptonrj
// @brief   handles the registers used.

static unsigned int registers[REGSIZE];
static unsigned int CC;


// @func    getRegister()
// @author  @comptonrj
// @brief   returns the register at the number passed.
// 
// @param   regNum      the number of the register to get.
// @return              the register itself.
unsigned int getRegister(int regNum){
    if(regNum < 0 || regNum >= REGSIZE)
        return 0;
    return registers[regNum];
}

// @func    setRegister()
// @author  @comptonrj
// @brief   sets the register at the number passed.
// 
// @param   regNum      the number of the register to set.
// @param   regValue    the value to set the register to.
void setRegister(int regNum, unsigned int regValue){ 
    if(regNum < 0 || regNum >= REGSIZE)
        return;
    registers[regNum] = regValue;
}

// @func    clearRegisters()
// @author  comptonrj
// @brief   clears all the registers.
void clearRegisters(){
    int i = 0;
    for(; i < REGSIZE; i++)
        registers[i] = 0;
}

// @func    setCC()
// @author  comptonrj
// @brief   sets the condition codes.
//
// @param   bitNumber   the number of the bit to set.
// @param   value       the value to change it to.
void setCC(unsigned int bitNumber, unsigned int value){
    if(bitNumber < 0 || bitNumber > 2) return;
    if(value != 0 && value != 1) return;
    CC = assignOneBit(bitNumber, value, CC);
}

// @func    getCC()
// @author  comptonrj
// @brief   returns the condition codes.
//
// @param   bitNumber   the number of bit to look at.
// @return              the condition code value.
unsigned int getCC(unsigned int bitNumber){
    if(bitNumber < 0 || bitNumber > 2) return;
    return getBits(bitNumber, bitNumber, CC); 
}

