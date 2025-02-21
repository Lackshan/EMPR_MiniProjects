#ifndef LCDPHW_H_
#define LCDPHW_H_

#include "I2C.h"
#include "Delay.h"
#include <string.h>
#include <stdlib.h>
#include "SerialIO.h"
#define LCD_ADDR 0x3B

void LCDGoHome();
void LCDNewLine();
void SendData(uint8_t* Data,int length);
void LCDEnable();
void LCDDisable();
void LCDGoHome();
void LCDNewLine();
void LCDInit();
void LCDClear();
void LCDPrint(char* input);

void main_LDCPrintHelloWorld(void);

#endif