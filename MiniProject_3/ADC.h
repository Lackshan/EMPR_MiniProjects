#ifndef ADC_H_
#define ADC_H_

#include "lpc17xx_adc.h"
#include "lpc17xx_pinsel.h"
#include "lpc17xx_libcfg_default.h"
#include "lpc17xx_nvic.h"
#include "lpc17xx_gpdma.h"

#include "Delay.h"
#include "SerialIO.h"



void InitializeADC();

void ADC_Send();

void ADC_InitializeGPDMA(uint32_t* Dest,GPDMA_Channel_CFG_Type* GPDMA_Cfg, int NumSamples);

#endif
