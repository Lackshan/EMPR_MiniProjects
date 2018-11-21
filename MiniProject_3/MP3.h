#ifndef MP3_H_
#define MP3_H_

#define PRECISION 134
#define MAXVOLTS 2.5
#define PI 3.1415926535897932384626433832
#define POLLING_TIME 1
#define MAXVAL 3

#include <math.h>
#include <stdlib.h>
#include <stdlib.h>

#include "PWM.h"
#include "Timer.h"
#include "SinetoSineGetter.h"
#include "ADC.h"
#include "DAC.h"
#include "KeyAccess.h"
#include "Delay.h"
#include "lpc17xx_adc.h"

void Stage2();
void Stage3();
void Stage4();

#endif
