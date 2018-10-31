#include "MiniProject2.h"

void GetInput()//Every accepted key press, assign a to prev char. After a timer, clear prevChar.
{
	int counter = 0,row =0 ;
	char prevChar= ' ';
	while(1)
	{
		char a = GetKeyInput();
		char output[2] = {a,'\0'};

		if(a == ' '){counter = MAXVAL;}
		if(a != ' ' && a != prevChar)
		{
			if(row==16)
			{
				LCDNewLine();
			}
			if(row==32)
			{
				LCDGoHome();
				row = 0;
			}
			row++;
			LCDPrint(output);
			prevChar = a;
			counter = 0;
		}
		else
		{
			if(counter == MAXVAL)
			{
				counter = 0;
				prevChar = ' ';
			}
			counter++;
		}
		Delay(POLLING_TIME);
	}
}

void main(void)
{
	Delay_Init();//Set up Delay
	InitSerial();
	GetAddresses();
	Delay(10);

	LCDInit();//Note: As initialisation of the I2C interface is done in GetAddresses, it doesn't need to be done here.
	LCDClear();
	LCDPrint("Hello World!");
	Delay(10);
	LCDClear();
	LCDPrint("Hello \n World!");//PrintToLCD needs to be modified to read newline characters
	Delay(10);
	LCDClear();

	GetInput();//This requires debouncing
}
