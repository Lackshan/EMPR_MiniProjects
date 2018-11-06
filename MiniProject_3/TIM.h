#ifndef TIM_H_
#define TIM_H_

#include "lpc17xx_timer.h"
#include "lpc17xx_libcfg_default.h"
#include "lpc17xx_pinsel.h"
#include "lpc17xx_gpio.h"

#define TINST LPC_TIM0

void InitializeTIM();
void StartTIM();
void StopTIM();
#endif
