#ifndef PWM_H_
#define PWM_H_

#include <stdlib.h>

#include "lpc17xx_libcfg_default.h"
#include "lpc17xx_pinsel.h"
#include "lpc17xx_pwm.h"
#include "TIM.h"

void InitializePWM();
void ChangeDutyCycle(uint32_t percent);

#endif
