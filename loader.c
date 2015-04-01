#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "loader.h"

// @func    load()
// @author  comptonrj / rhoadskj
// @brief   loads the file from a filename
int load(char *fileName)
{
    FILE *file;
    char *mode = "r";

    file = fopen(fileName, mode);

    if (!validFileName(fileName)) {
        printf("%s is not a valid file.\n", fileName);
        return 0;
    }

    // the current line number
    unsigned int lnCount = 1;
    // the string for the important part of a potential data record
    char line[21];
    // addr is the address pulled from the current line
    // memPointer is the byte address that may be written to in memory
    // lineIndex is the index of the line array which is currently being read from
    int addr = 0;
    int memPointer = 0;
    int lineIndex = 0;
    // unsigned char (btye) to hold the grabbed data byte from the current line
    unsigned char data;
    // bool that will be set to true if there is an error accessing memory
    bool memErr = false;
    while (fgets(line, sizeof(line), file)) {
      
      bool lineIn = false;
      int i = 0;

      for (; i < sizeof(line); i++) {
        if (line[i] == '\n') lineIn = true;
      }
      
      if (!lineIn) discardRest(file);
      
      if (!checkLine(line)) {
          printf("Error on line %d:\n", lnCount);
          printf("%s\n", line);
          return 0;
      }


      if(!isSpaces(line, 9, 10)){
        lineIndex = 9;
        addr = grabAddress(line, 5);
        if(memPointer > addr){
          printf("Error on line %d:\n", lnCount);
          printf("%s\n", line);
          printf("Address referenced on line %d has already been written.\n", lnCount);
          return 0;
        }
        memPointer = addr;
        while(!isSpaces(line, lineIndex, lineIndex + 1)){
          data = grabDataByte(line, lineIndex);
          putByte(memPointer, data, &memErr);
          if (memErr){
            printf("Error on line %d:\n", lnCount);
            printf("%s\n", line);
            printf("Memory access returned that there was a memory error.\n");
            return 0;
          }
          lineIndex = lineIndex + 2;
          memPointer++;
        }
      }
      lnCount++;
    }

    fclose(file);
    return 1;
}

// @func    isAddress()
// @author  rhoadskj / comptonrj
// @brief   checks to see if the string is an address
bool isAddress(char *record, int start, int end)
{
    if (end > strlen(record)) return false;
    int i = start;
    for (;i <= end; i++) {
        if (!isxdigit(record[i])) return false;
    }
    return true;
}

// @func    isSpaces
// @author  rhoadskj / comptonrj
// @brief   checks to see if the string is white space
bool isSpaces(char *record, int start, int end)
{
    if (end < strlen(record))
    {
        printf("loop1\n");    
        int i = start;
        for (;i <= end; i++) {
            if (record[i] != ' ') return false;
        }
    }
    else
    {
        int i = start;
        for (; i <= strlen(record); i++) {
            if (record[i] != ' ') return false;
        }
    }

    return true;
}

// @func    isData()
// @author  rhoadskj / comptonrj
// @brief   checks to see if the string is data
bool isData(char *record, int start, int end)
{
    if (end < strlen(record))
    {
        printf("loop1\n");
        int i = start;
        for (; i <= end; i++) {
            if (!isxdigit(record[i]) || record[i] == ' ')
                return false;
        }
    }
    else
    {
        printf("loop2\n");
        int i = start;
        for (; i <= strlen(record); i++) {
            printf("%d : %c : %d\n", i, record[i], (record[i] == ' '));
            if (!isxdigit(record[i]) || record[i] == ' ')
                return false;
        }
    }
    return true;
}

// @func    checkLine()
// @author  rhoadskj / comptonrj
// @brief   checks for errors in the line
bool checkLine(char *line)
{
    printf("%d\n", strlen(line));
    // if the line is blank
    if (isSpaces(line, 0, 20)) return true;

    // if the line isn't blank
    if (!isSpaces(line, 0, 1)) return false;
    if (line[2] != '0') return false;
    if (line[3] != 'x') return false;
    if (!isAddress(line, 4, 6)) return false;
    if (line[7] != ':') return false;
    if (line[8] != ' ') return false;

    // compares opcode to check to see if the length of the line
    // is the correct length    
    char opcode = line[9];
    
    if (opcode == '0' ||
        opcode == '1' ||
        opcode == '9')
    {
        if (!isData(line, 9, 10)) return false;
        if (!isSpaces(line, 11, 20)) return false;
    }

    if (opcode == '2' ||
        opcode == '6' ||
        opcode == 'A' ||
        opcode == 'B')
    {
        if (!isData(line, 9, 12)) return false;
        if (!isSpaces(line, 13, 20)) return false;
    }

    if (opcode == '7' ||
        opcode == '8')
    {
        if (!isData(line, 9, 18)) return false;
        if (!isSpaces(line, 19, 20)) return false;
    }

    if (opcode == '3' ||
        opcode == '4' ||
        opcode == '5')
    {
        if (!isData(line, 9, 20)) return false;
    }

    return true;
}

// @func    grabAddress()
// @author  rhoadskj / comptonrj
// @brief   grabs an address from a line
unsigned int grabAddress(char *record, int start)
{
    // assumes already checked for address
    char hex[3];
    hex[0] = record[start];
    hex[1] = record[start + 1];
    hex[2] = record[start + 2];
    return (int) strtol(hex, NULL, 16);
}

// @func    validFileName()
// @author  comptonrj
// @brief   Checks to see if the passed file is valid
bool validFileName(char *fileName)
{
    char *point;
    if ((point = strrchr(fileName,'.')) != NULL ) {
        if (strcmp(point,".yo") == 0) {
        return fileExists(fileName);
        }
    }
    return false;
}

// @func    fileExists
// @author  comprontj
// @brief   Checks to see if the pased fileName str exists
bool fileExists(char *fileName)
{
    FILE *file = fopen(fileName, "r");
    bool exists = (file == 0) ? false : true;
    fclose(file);
    return exists;
}

// @func    discardRest()
// @author  rhoadskj
// @brief   discards the rest of the line after the buffer
void discardRest(FILE *file)
{
    char current = fgetc(file);
    while(current != '\n' && current != EOF){
        current = fgetc(file);
    }
}

// @func    grabDataByte()
// @author  rhoadskj
// @brief   grabs the byte at the data location
unsigned char grabDataByte(char *record, int index)
{
    // assumes already checked for data
    char hex[2];
    hex[0] = record[index];
    hex[1] = record[index + 1];
    return (char) strtol(hex, NULL, 16);
}

