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
int plus(int a,int b);
int minus(int a,int b);
int divd(int a,int b);
int times(int a,int b);
#endif
