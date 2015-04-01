#include <stdbool.h>
int load(char*);
bool validFileName(char*);
bool fileExists(char*);
void discardRest(FILE*);
unsigned int grabAddress(char*, int);
bool isAddress(char*, int, int);
bool isData(char*, int, int);
bool isSpaces(char*, int, int);
unsigned char grabDataByte(char*,int);
bool checkLine(char*);
