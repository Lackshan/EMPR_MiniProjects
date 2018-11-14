#ifndef irSENSE_H_
#define irSENSE_H_

#include <stdlib.h>
#include <string.h>

#include "ADC.h"
#include "Delay.h"
#include "SerialIO.h"
#include "KeyAccess.h"
#include "LDC_PrintHelloWorld.h"
#include "I2C.h"

typedef struct {double i,j;}dtuple;

void LedsOFF();
void LedsON();
double getADC();
dtuple Calibrate();

#endif
