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
#include "loader.h"

// @file    main.c
// @author  rhoadskj
// @brief   the main file. runs yess.

void initialize();

int main(int argc, char *argv[])
{
    bool memError;
    unsigned int memValue;
    FILE *yo;
    char ln[80];
    unsigned int count = 0;

    initialize();

    bool loadError = !load(argc, argv);

    dumpProgramRegisters();
    dumpProcessorRegisters();
    dumpMemory();

    if (loadError || !isValidFile(argv[1])) {
        printf("ERROR: file opening failed.\n");
        printf("USAGE: yess <filename>.yo\n");
        return 0;
    }

    yo = fopen(argv[1],"r");
    while (fgets(ln, 80, yo)) {
        if (!checkLine(ln)) {
            printf("error on line %d:\n%s\n", count, ln);
        }

        else {
            // STUFF
        }

        count++;
    }

    fclose(yo);
    return 1;
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

