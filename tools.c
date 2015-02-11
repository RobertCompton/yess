#include <stdio.h>
#include <stdbool.h>
#include "tools.h"

/*
   Replace the return 0 with the code to perform the required function.
   Do not change the function prototypes.
   Be sure to check for errors in input.
   Document EACH function with a function header (description, parameters,
   return).
*/

unsigned int getBits(int low, int high, unsigned int source)
{
    if(low < 0 || high > 31 || low > high) return 0;
    unsigned int temp = source;
    temp = temp << (31 - high);
    temp = temp >> (31 - (high - low));
    return temp;
}

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

unsigned int assignOneBit(int bitNumber, int bitValue, unsigned int source)
{
    unsigned int temp = source;
    if(bitNumber < 0 || bitNumber> 31 || bitValue < 0 || bitValue > 1) return temp;
    if(bitValue == 0) return clearBits(bitNumber, bitNumber, source);
    if(bitValue == 1) return setBits(bitNumber, bitNumber, source);
    return temp;
}

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

unsigned int putByteNumber(int byteNo, unsigned char byteValue, unsigned int source)
{
    unsigned int temp = source;
    if(byteNo < 0 || byteNo > 3) return temp;
    unsigned int mask = byteValue << (byteNo * 8);
    temp = clearBits(byteNo * 8, byteNo * 8 + 7, temp);
    temp = temp | mask;
    return temp;
}


unsigned int buildWord(unsigned char byte0, unsigned char byte1, unsigned char byte2, unsigned char byte3)
{
    unsigned int temp = 0x00000000;
    temp = putByteNumber(0, byte0, temp);
    temp = putByteNumber(1, byte1, temp);
    temp = putByteNumber(2, byte2, temp);
    temp = putByteNumber(3, byte3, temp);
    return temp;
}

bool isNegative(unsigned int source)
{
   unsigned int temp = source;
   temp = temp & 0x80000000;
   if(temp >  0) return 1;
   return 0;
}

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

void clearBuffer(char * buff, int size)
{
    int i = 0;
    for(; i < size; i++){
        buff[i] = 0;
    }
}

