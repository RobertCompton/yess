#include <stdio.h>
#include <stdbool.h>
#include "tools.h"

// @file    tools.c
// @author  comptonrj / rhoadskj
// @brief   the tools for modifying bits and bytes.

// @func    getBits()
// @author  comptonrj
// @brief   get the bits in a range.
unsigned int getBits(int low, int high, unsigned int source)
{
    if(low < 0 || high > 31 || low > high) return 0;
    unsigned int temp = source;
    temp = temp << (31 - high);
    temp = temp >> (31 - (high - low));
    return temp;
}

// @func    setBits()
// @author  comptonrj
// @brief   set the bits in a range.
unsigned int setBits(int low, int high, unsigned int source)
{
    unsigned int temp = source;
    if(low < 0 || high > 31 || low > high) return temp;
    unsigned int mask = 0xFFFFFFFF;
    mask = mask >> low;
    mask = mask << (low + (31 - high));
    mask = mask >> (31 - high);
    temp = temp | mask;
    return temp;
}

// @func    clearBits()
// @author  comptonrj / rhoadskj
// @brief   clears the bits in a range (sets to 0).
unsigned int clearBits(int low, int high, unsigned int source)
{
    unsigned int temp = source;
    if(low < 0 || high > 31 || low > high) return temp;
    unsigned int mask = 0xFFFFFFFF;
    mask = mask >> low;
    mask = mask << (low + (31 - high));
    mask = mask >> (31 - high);
    mask = ~mask;
    temp = temp & mask;
    return temp;
}

// @func    assignOneBit()
// @author  comptonrj / rhoadskj
// @brief   sets a single bit.
unsigned int assignOneBit(int bitNumber, int bitValue, unsigned int source)
{
    unsigned int temp = source;
    if(bitNumber < 0 || bitNumber> 31 || bitValue < 0 || bitValue > 1) return temp;
    if(bitValue == 0) return clearBits(bitNumber, bitNumber, source);
    if(bitValue == 1) return setBits(bitNumber, bitNumber, source);
    return temp;
}

// @func    getByteNumber()
// @author  comptonrj / rhoadskj
// @brief   gets the byte at a certain location, 0 through 3.
unsigned char getByteNumber(int byteNo, unsigned int source)
{
   unsigned int temp = source;
   if(byteNo < 0 || byteNo > 3) return 0;
   unsigned char ret;
   unsigned int mask = 0x000000FF;
   mask = mask << (byteNo * 8);
   ret = (temp & mask) >> (byteNo * 8);
   return ret;
}

// @func    putByteNumber()
// @author  comptonrj / rhoadskj
// @brief   sets the byte at a certain location, 0 through 3.
unsigned int putByteNumber(int byteNo, unsigned char byteValue, unsigned int source)
{
    unsigned int temp = source;
    if(byteNo < 0 || byteNo > 3) return temp;
    unsigned int mask = byteValue << (byteNo * 8);
    temp = clearBits(byteNo * 8, byteNo * 8 + 7, temp);
    temp = temp | mask;
    return temp;
}

// @func    buildWord()
// @author  rhoadskj
// @brief   makes a word, using putByteNumber() for each byte.
unsigned int buildWord(unsigned char byte0, unsigned char byte1, unsigned char byte2, unsigned char byte3)
{
    unsigned int temp = 0x00000000;
    temp = putByteNumber(0, byte0, temp);
    temp = putByteNumber(1, byte1, temp);
    temp = putByteNumber(2, byte2, temp);
    temp = putByteNumber(3, byte3, temp);
    return temp;
}

// @func    isNegative()
// @author  rhoadskj
// @brief   checks to see if the source is negative.
bool isNegative(unsigned int source)
{
   unsigned int temp = source;
   temp = temp & 0x80000000;
   if(temp >  0) return 1;
   return 0;
}

// @func    expandBits
// @author  rhoadskj
// @brief   expands the bits for printing purposes, spaces included.
void expandBits(unsigned int source, char bits[36])
{
    int i = 0;
    int count = 0;
    for(; i < 35; i++){
        if(i == 8 || i == 17 || i == 26){
            bits[i] = 0x20;
        }
        else{
            bits[i] = getBits(31 - count, 31 - count, source) + 0x30;
            count++;
        }
    }
    bits[35] = 0;
}

// @func    clearBuffer()
// @author  rhoadskj
// @brief   clears the buffer. shocking, I know.
void clearBuffer(char * buff, int size)
{
    int i = 0;
    for(; i < size; i++){
        buff[i] = 0;
    }
}

