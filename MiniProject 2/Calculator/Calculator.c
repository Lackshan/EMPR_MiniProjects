#include "Calculator.h"

char val[2][17];
int selectedValue = 0,characterCounter=0,output=0,int operator =0;
static int (*operators[])(int,int){&plus,&minus,&times,&div};


void main()//You know what? Just use a character counter instead of doing the shit that you are trying now.
{

	static void (*funcs[][])(tuple) = {
	{&data,  &data,  &data,  &opr},
	{&data,  &data,  &data,  &opr},
	{&data,  &data,  &data,  &opr},
	{&bckspc,&zero,  &equals,&opr}
	};

	SysTick_Config(SystemCoreClock/10-1);
	LCDInit();
	LCDClear();
	LCDPrint("*CALCUMALATOR-3*\nDoo Doo Doo Doo");
	Delay(10);
	LCDClear();
	while(1)
	{
		tuple coords = DecodeInput();
		if(coords.i != TP_FAILURE)
		{
			funcs[coords.i][coords.j]();
		}
	}
}


void data(tuple coords)
{
	strncat(val[selectedValue],(coords.i+1)+(3*coords.j)+'0',16-strlen(val[selectedValue]));
	LCDPrint(val[selectedValue][16-strlen(val[selectedValue])]);
}

void zero(tuple coords)
{
	strncat(val[selectedValue],'0',16-strlen(val[selectedValue]));
}
void disp(tuple coords)
{
	
}

void bckspc(tuple coords)
{
	 val[selectedValue][strlen(val[selectedValue])-1]= '\0';//Replace last character with the null terminator
}

void opr(tuple coords)
{
	selectedValue = abs(selectedValue-1); //Switch to the other value
	operator = coords.j; 
}

void equals(tuple coords)
{
	output = operators[operator](atoi(val[0]),atoi(val[1]));//Do the operation on the values
	disp(coords);
}

int plus(int a,int b){return a+b;}
int minus(int a,int b){return a-b;}
int div(int a,int b){return a/b;}
int times(int a,int b){return a*b;}