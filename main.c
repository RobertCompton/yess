#include <stdio.h>
#include <stdbool.h>
#include "tools.h"
#include "memory.h"
#include "dump.h"
#include "registers.h"
#include "executeStage.h"
#include "fetchStage.h"
#include "writebackStage.h"
#include "decodeStage.h"
#include "memoryStage.h"

// @file    main.c
// @author  rhoadskj
// @brief   the main file. runs yess.

void initialize();

int main(int argv, char * args[])
{
    bool memError;
    unsigned int memValue;

    initialize();

    // TODO: what type?
    // loadError = !load(argc, args);
    
    dumpProgramRegisters();
    dumpProcessorRegisters();
    dumpMemory();
    
    // if called with no arguments following 'yess', prints error.
    if (argc < 2) {
        printf("ERROR: file opening failed, no file passed \n");
        printf("USAGE: yess <filename>.yo \n");
    }

    // if called with too many arguments, prints error.
    if (argc > 2) {
        printf("ERROR: file opening failed, too many arguments. \n");
        printf("USAGE: yess <filename.yo \n");
     }
    
    // TODO: just so it can compile currently.
    return 0;
}

void initialize()
{
    clearMemory();
    clearRegisters();
    clearFregister();
    clearDregister();
    clearEregister();
    clearMregister();
    clearWregister();
}


