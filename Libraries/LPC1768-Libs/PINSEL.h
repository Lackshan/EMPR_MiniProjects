/*
LPC_PINCON->PINSELx = (1<<y)
PINSEL refers to the registers that enable pins. PINSEL0 & 1 are for P0, PINSEL2 & 3 are for P1,
all the way up to PINSEL9 & 10 for P4.

First PINSEL register for a port is for pins[15:0] and second is for pins[31:16].

Not all ports are 32 bits wide but each PINSEL register is 16bits wide.

Refer to:
https://www.exploreembedded.com/wiki/LPC1768:_Register_Configuration(lpc17xx.h)
https://www.ocfreaks.com/lpc1768-gpio-programming-tutorial/
https://openlabpro.com/guide/led-blinking-using-lpc1768/
*/