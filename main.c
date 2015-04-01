#include <stdio.h>
#include <stdbool.h>
#include "tools.h"
#include "memory.h"
#include "dump.h"
#include "registers.h"
#include "forwarding.h"
#include "executeStage.h"
#include "fetchStage.h"
#include "writebackStage.h"
#include "decodeStage.h"
#include "memoryStage.h"
#include "loader.h"

// @file    main.c
// @author  rhoadskj
// @brief   the main file. runs yess.

void initialize();
forwardType fwd;

int main(int argc, char *argv[])
{
    bool memError;
    unsigned int memValue;
    unsigned int clockCount = 0;
    bool stop = false;

    initialize();

    dumpProgramRegisters();
    dumpProcessorRegisters();
    dumpMemory();

    if (argc != 2 || load(argv[1]) == 0)
    {
        printf("ERROR: file opening failed.\n");
        printf("USAGE: yess <filename>.yo\n");
        dumpMemory();
        return 0;
    }

//    while(!stop)
//    {
//        stop = writebackStage(&fwd);
//        memoryStage();
//        executeStage();
//        decodeStage(fwd);
//        fetchStage();
//        clockCount++;
//    }

//    printf("Total Clock Cycles = %d\n", clockCount);

    return 1;
}

// @func    initialize()
// @author  given
// @brief   clears the memory and registers.
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

