/***********************************************************************//**
 * @file		Timer.h
 * @brief		Contains all functions
 * 				for PWM on LPC1768
 * @version		1.0
 * @date		14. November. 2018
 * @author		Lackshan Senkodan
 **************************************************************************/

/* Includes ------------------------------------------------------------------- */
#include "LPC17xx.h"

/* Public Functions ----------------------------------------------------------- */
void initTimer(LPC_TIM_TypeDef* Timer)
{
	Timer->CTCR = 0x0;
	Timer->PR = 25000-1; //Increment TC at every 24999+1 clock cycles
	//25000 clock cycles @25Mhz = 1 mS
	Timer->TCR = 0x02; //Reset Timer
}

void delayMS(unsigned int milliseconds, LPC_TIM_TypeDef* Timer)
{
	Timer->TCR = 0x02; //Reset Timer
	Timer->TCR = 0x01; //Enable timer

	while(Timer->TC < milliseconds); //wait until timer counter reaches the desired delay

	Timer->TCR = 0x00; //Disable timer
}

/* --------------------------------- End Of File ------------------------------ */

// Need to implement Match Register stuff so each timer can generate 4 delays each.