#ifndef KEY_H_
#define KEY_H_

#include "SerialIO.h"
#include "I2C.h"

typedef struct {int i,j;}tuple;

#define TP_FAILURE 9
//Figure out some hacky way of assigning a tuple to this

char GetKeyInput();
unsigned char GetKeyData(char BitMask);
void mainKeyAccess();
tuple DecodeInput();


#endif
