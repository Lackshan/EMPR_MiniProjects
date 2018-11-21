#ifndef CALC_H_
#define CALC_H_

#include "I2C.h"
#include "Delay.h"
#include "SerialIO.h"

#include "LDC_PrintHelloWorld.h"
#include "KeyAccess.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

void data(tuple coords);
void zero(tuple coords);
void disp(char* charString);
void bckspc(tuple coords);
void opr(tuple coords);
void equals(tuple coords);
float plus(float a,float b);
float minus(float a,float b);
float divd(float a,float b);
float times(float a,float b);
#endif
