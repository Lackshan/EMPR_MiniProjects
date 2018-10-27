#ifndef MP1_H_
#define MP1_H_

#include <string.h>
#include <stdio.h>

#include "lpc17xx_libcfg_default.h"
#include "lpc17xx_systick.h"
#include "lpc17xx_pinsel.h"
#include "lpc17xx_uart.h"
#include "lpc17xx_gpio.h"
#include "lpc_types.h"

#define LED1 1<<18
#define LED2 1<<20
#define LED3 1<<21
#define LED4 1<<23

#define INT_TO_NIBBLE(nibble) (nibble&0x08 ? '1':'0'),(nibble&0x04 ? '1':'0'),(nibble&0x02 ? '1':'0'),(nibble&0x01 ? '1':'0')

void InitSerial();

int WriteText(char* TexttoWrite);

void displaydigit(int input);
void setupAll(void);
void clearAll(void);

volatile unsigned long Counter;
void Delay(unsigned long tick);
void SysTick_Handler(void);
#endif
