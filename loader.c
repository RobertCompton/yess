#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "loader.h"

// @file    loader.c
// @author  rhoadskj
// @brief   loads the .yo program.

// @func    main()
// @author  tba
// @brief
int main() { }

// @func    validFileName()
// @author  comptonrj
// @brief   Checks to see if the passed file is valid
bool validFileName(char *fileName){
  char *point;
  if((point = strrchr(fileName,'.')) != NULL ) {
    if(strcmp(point,".yo") == 0) {
      //Target file does not exist
      return fileExists(fileName);
    }
  }
  //Target file is not a .yo file
  return 0;
}

// @func    fileExists
// @author  comprontj
// @brief   Checks to see if the pased fileName str exists
bool fileExists(char *fileName){
  FILE *file = fopen(fileName, "r");
  bool exists = (file == 0) ? 0 : 1;
  fclose(file);
  return exists;
}

// @func    discardRest()
// @author  tba
void discardRest() { }

// @func    grabAddress()
// @author  tba
unsigned int grabAddress() { }

// @func    isAddress()
// @author  tba
bool isAddress() { }

// @func    isData()
// @author  tba
bool isData() { }

// @func    isSpaces()
// @author  tba
bool isSpaces() { }

// @func    checkHex()
// @author  tba
bool checkHex() { }

// @func    grabDataByte()
// @author  tba
unsigned int grabDataByte() { }

// @func    checkLine()
// @author  tba
bool checkLine() { }

