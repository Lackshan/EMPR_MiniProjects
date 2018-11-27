/***********************************************************************//**
 * @file		PWM.h
 * @brief		Contains all macro definitions and function prototypes
 * 				support for PWM on LPC1768
 * @version		1.0
 * @date		14. November. 2018
 * @author		Lackshan Senkodan
 **************************************************************************/

/* Includes ------------------------------------------------------------------- */
#include "LPC17xx.h"

/* Public Macros -------------------------------------------------------------- */
#define PWMPRESCALE (25-1) //25 PCLK cycles to increment TC by 1 i.e. 1 Micro-second

/* Global Variables -------------------------------------------------------------- */
//volatile uint32_t MR_1 = &LPC_PWM1->MR1;
//static LPC_PWM_TypeDef (* const MR[7]) = { &LPC_PWM1->MR0, &LPC_PWM1->MR1, &LPC_PWM1->MR2, &LPC_PWM1->MR3, &LPC_PWM1->MR4, &LPC_PWM1->MR5, &LPC_PWM1->MR6 };

/* Public Types --------------------------------------------------------------- */
typedef struct {
	volatile uint32_t* PINSEL_Register;
	int PINCON;
	volatile uint32_t* Match_Register;
} PWM_Pin_Type;

/* Public Functions ----------------------------------------------------------- */
void initPWM(PWM_Pin_Type Pin) {
	/*Assuming that PLL0 has been setup with CCLK = 100Mhz and PCLK = 25Mhz.*/
	*Pin.PINSEL_Register |= Pin.PINCON; //Selects output pin
	LPC_PWM1->PCR = 0x0; 				//Selects PWM mode: Single or Double edged
	LPC_PWM1->PR = PWMPRESCALE; 		//Clock cycles to increment by
	LPC_PWM1->MR0 = 1000; 				//Set period duration - 1000us = 1ms period duration
	LPC_PWM1->MCR = (1<<1); 			//Reset PWM TC on PWM1MR0 match
	LPC_PWM1->LER = (1<<0) | (1<<1); 	//update values in MR0 and MR1 respectively
										// IMPLEMENT METHOD OF CHOOSING VALUES FOR MR1-MR6!!
	LPC_PWM1->PCR = (1<<9); 			//enable PWM output
	LPC_PWM1->TCR = (1<<1); 			//Reset PWM TC & PR

	LPC_PWM1->TCR = (1<<0) | (1<<3); 	//enable counters and PWM Mode
										//PWM Generation goes active now!
}

void updatePulseWidth(PWM_Pin_Type Pin, unsigned int pulseWidth) {
	*Pin.Match_Register = pulseWidth; 	//Update Match Register with new value
	LPC_PWM1->LER = (1<<1); 			//Load the MR1 new value at start of next cycle
										// IMPLEMENT METHOD OF CHOOSING VALUES FOR MR1-MR6!!
}

/* --------------------------------- End Of File ------------------------------ */
