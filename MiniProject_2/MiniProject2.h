#ifndef MIN2_H_
#define MIN2_H_

#include "I2C.h"
#include "Delay.h"
#include "SerialIO.h"

#include "LDC_PrintHelloWorld.h"
#include "KeyAccess.h"
#include "I2CGetAddresses.h"

#define POLLING_TIME 1 //in centi seconds
#define MAXVAL 3

void GetInput();

#endif