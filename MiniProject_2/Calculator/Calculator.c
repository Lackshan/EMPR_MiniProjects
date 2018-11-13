#include "Calculator.h"

char val[2][17],oprSymbols[4] = {'+','-','*','/'};;
int selectedValue = 0,output=0,operator =0,cleardisp =0;
static int (*operators[])(int,int) = {&plus,&minus,&times,&divd};

void main()//You know what? Just use a character counter instead of doing the shit that you are trying now.
{
	InitSerial();
	static void (*funcs[])(tuple) = {
  	&data,  &data,  &data,  &opr,
		&data,  &data,  &data,  &opr,
		&data,  &data,  &data,  &opr,
		&bckspc,&zero,  &equals,&opr
	};
	SysTick_Config(SystemCoreClock/10-1);
	SetupPINS();
	I2C_Init(I2CBUS,100000);
	I2C_Cmd(I2CBUS,ENABLE);
	LCDInit();
	LCDClear();
	LCDPrint("*CALCUMALATOR-3*\nDoo Doo Doo Doo");
	Delay(50);
	LCDClear();
	tuple prevcoords,coords;
	coords.i = TP_FAILURE;
	while(1)
	{
		coords = DecodeInput();
	  if(coords.i != TP_FAILURE)
		{
			if(!(coords.i == prevcoords.i && coords.j == prevcoords.j))
			{
				if(cleardisp)
				{
					LCDClear();
					LCDGoHome();
					cleardisp = 0;
				}
				prevcoords = coords;
				funcs[(coords.i*4)+coords.j](coords);
			}
		}
		else
		{
			prevcoords.i = TP_FAILURE;
			prevcoords.j = TP_FAILURE;
		}
	}
}


void data(tuple coords)
{
	char nchar = (coords.j+1)+(3*coords.i)+'0';
	char outputbuf[2] = {nchar,'\0'};
	strcat(val[selectedValue],outputbuf);
	disp(outputbuf);
}

void zero(tuple coords)
{

	char outputbuf[2] = {'0','\0'};
	strcat(val[selectedValue],outputbuf);
	disp(outputbuf);
}

void disp(char* charString)
{
	LCDPrint(charString);
}

void bckspc(tuple coords)
{
	LCDClear();
	LCDGoHome();
	val[0][0] = '\0';
	val[1][0] = '\0';
	selectedValue = abs(selectedValue-1);
	output = 0;
}

void opr(tuple coords)
{
	selectedValue = abs(selectedValue-1); //Switch to the other value
	operator = coords.i;
	char outputBuf[2] = {oprSymbols[coords.i],'\0'};
	disp(outputBuf);
	LCDNewLine();
}

void equals(tuple coords)
{
	output = operators[operator](atoi(val[0]),atoi(val[1]));//Do the operation on the values
	char outputBuf[50];
	sprintf(outputBuf,"%d",output);
	LCDClear();
	LCDGoHome();
	disp(outputBuf);
	cleardisp = 1;
	val[0][0] = '\0';
	val[1][0] = '\0';
	selectedValue = abs(selectedValue-1);
	output = 0;
}

int plus(int a,int b){return a+b;}
int minus(int a,int b){return a-b;}
int divd(int a,int b){return a/b;}
int times(int a,int b){return a*b;}
