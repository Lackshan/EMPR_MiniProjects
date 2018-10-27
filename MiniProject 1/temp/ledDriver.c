#include "lpc17xx_gpio.h"
#include "lpc17xx_systick.h"
#include "lpc17xx_libcfg_default.h"

#define LED1 1<<18
#define LED2 1<<20
#define LED3 1<<21
#define LED4 1<<23


volatile unsigned long Counter;

void SysTick_Handler(void)
{
	Counter++;
	/*if(Counter<16)
	{
		displaydigit(Counter);
	}*/
}

void Delay(unsigned long tick){
	unsigned long systickcnt;
	systickcnt = Counter;
	while((Counter-systickcnt)<tick);
}
void displaydigit(int input)
{	
	int i;
	unsigned long int cake[4]  = {LED1,LED2,LED3,LED4};
	for(i=0;i<4;i++)
	{
		if(input == 0)return;

		if(input%2)
		{
			GPIO_SetValue(1,cake[i]);
		}
	input/=2;	
	}	
}


/*void flashAllLEDS()
{
	unsigned long int i;
	GPIO_SetValue(1,LED1);
	for(i = 0;i<7294967;i++);
	GPIO_ClearValue(1,LED1);
	GPIO_SetValue(1,LED2);
	for(i = 0;i<7294967;i++);
	GPIO_ClearValue(1,LED2);
	GPIO_SetValue(1,LED3);
	for(i = 0;i<7294967;i++);
	GPIO_ClearValue(1,LED3);
	GPIO_SetValue(1,LED4);
	for(i = 0;i<7294967;i++);
	GPIO_ClearValue(1,LED4);
}*/

void setupAll()
{
	GPIO_SetDir(1,LED1,1);
	GPIO_SetDir(1,LED2,1);
	GPIO_SetDir(1,LED3,1);
	GPIO_SetDir(1,LED4,1);
}
void clearAll()
{
	GPIO_ClearValue(1,LED1);
	GPIO_ClearValue(1,LED2);
	GPIO_ClearValue(1,LED3);
	GPIO_ClearValue(1,LED4);
}

void main(void)
{	
	int i,j;
	setupAll();
	SysTick_Config(SystemCoreClock/1000-1);
	
	//flashAllLEDS();

	for(i=0;i<16;i++)
	{
		displaydigit(i);
		//for(j = 0;j<7294967;j++);
		Delay(1000);
		clearAll();

	}

}



