#include "Delay.h"

void SysTick_Handler(void)
{
	Counter++;
}

void Delay(unsigned long tick)
{
	unsigned long systickcnt;
	systickcnt = Counter;
	while((Counter-systickcnt)<tick);
}
void Delay_Init()
{
	SysTick_Config(SystemCoreClock/10-1);
}
