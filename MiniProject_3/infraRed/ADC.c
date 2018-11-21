#include "ADC.h"

void InitializeADC()
{
  //Open pins:

  PINSEL_CFG_Type PINCFG;//GPIO Number
  PINCFG.Funcnum = 1;
  PINCFG.OpenDrain =0;
  PINCFG.Pinmode = 0;
  PINCFG.Pinnum = 25;
  PINCFG.Portnum = 0;
  PINSEL_ConfigPin(&PINCFG);
  //Run Default Functions

  ADC_Init(LPC_ADC,200000);
  //ADC_IntConfig(LPC_ADC,ADC_ADINTEN2,DISABLE);//Enable ADC Interrupts
  ADC_ChannelCmd(LPC_ADC,ADC_CHANNEL_2,ENABLE);//Enable channel to use
  //ADC_EdgeStartConfig(LPC_ADC,ADC_START_ON_FALLING);//Specify the edge to start inputting on
}
