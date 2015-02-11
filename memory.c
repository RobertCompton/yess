#include <stdio.h>
#include <stdbool.h>
#include "memory.h"

// @file    memory.c
// @author  comptonrj / rhoadskj
// @brief   the virtual memory space.

static unsigned int memory[MEMSIZE];

// @func    fetch()
// @author  comptonrj
// @brief   fetches stuff at the address.
//
// @param   address     the address to fetch stuff at.
// @param   memError    whether or not there is a memory error.
// @return              the stuff at the address.
unsigned int fetch(int address, bool *memError){
  if (address < 0 || address >= MEMSIZE){
    *memError = true;
    return 0;
  }
  return memory[address];
}

// @func    store()
// @author  comptonrj
// @brief   stores stuff at the address.
//
// @param   address     the address to store stuff at.
// @param   value       the stuff to store.
// @param   memError    whether or not there is a memory error.
void store(int address, unsigned int value, bool *memError){
  if (address < 0 || address >= MEMSIZE){
    *memError = true;
    return;
  }
  memory[address] = value;
}

// @func    getByte()
// @author  comptonrj / rhoadskj
// @brief   gets the specific byte at the address.
//
// @param   byteAddress the address of the byte... duh.
// @param   memError    whether or not there is a memory error.
// @return              the byte at the address.
// TODO: Fix this shit to actually access by byte address.
unsigned char getByte(int byteAddress, bool * memError){
    if (byteAddress < 0 || byteAddress >= MEMSIZE*4){
        *memError = true;
        return 0;
    }
    int wordAddress = byteAddress/4;
    int byteNumber = getBits(0, 3, byteAddress);
    int byte = memory[byteAddress];
    return getByteNumber(byteNumber, byte);
}

// @func    putByte()
// @author  comptonrj / rhoadskj
// @brief   sets the byte at the given address.
//
// @param   byteAddress the address of the byte.
// @param   value       the byte to change it to.
// @param   memError    whether or not there is a memory error.
// TODO: Fix this shit to actually access by byte address.
void putByte(int byteAddress, unsigned char value, bool * memError){
    if (byteAddress < 0 || byteAddress >= MEMSIZE){
        *memError = true;
        return;
    }
    int wordAddress = byteAddress/4;
    int byteNumber = getBits(0, 3, byteAddress);
    *memError = false;
    memory[byteAddress] = putByteNumber(byteNumber, value, memory[byteAddress]);
}

// @func    getWord()
// @author  comptonrj
// @brief   like getByte, but in word form!
//
// @param   byteAddress the address of the byte.
// @param   memError    whether or not there is a memory error.
// @return              the word at the address.
unsigned int getWord(int byteAddress, bool * memError){
    if (byteAddress < 0 || byteAddress >= MEMSIZE || !!(byteAddress&0x3)){
        *memError = true;
        return 0;
    }
    *memError = false;
    return memory[byteAddress];
}

// @func    putWord()
// @author  comptonrj
// @brief   like putByte, but in word form!
//
// @param   byteAddress the address of the byte.
// @param   value       the word to set at the address.
// @param   memError    whether or not there is a memory error.
void putWord(int byteAddress, unsigned int value, bool * memError){
    if (byteAddress < 0 || byteAddress >= MEMSIZE || !!(byteAddress&0x3)){
        *memError = true;
        return;
    }
    *memError = false;
    memory[byteAddress] = value;
}

// @func    clearMemory()
// @author  comptonrj
// @brief   clears the memory, sets everything to 0.
void clearMemory(){
    int i = 0;
    for(; i < MEMSIZE; i++)
        memory[i] = 0;
}
