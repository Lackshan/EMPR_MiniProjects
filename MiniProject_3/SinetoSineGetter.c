#include "SinetoSineGetter.h"

int main()
{
  InitSerial();
  InitializeDAC();
  InitializeADC();

  uint32_t Data = 0;

  while(1)
  {//Read a value from ADC, output it through DAC.
    ADC_StartCmd(LPC_ADC,ADC_START_NOW);
    while(ADC_ChannelGetStatus(LPC_ADC,ADC_CHANNEL_2,1)==RESET);
    Data = ADC_GetData(ADC_CHANNEL_2);
    DAC_UpdateValue(LPC_ADC,Data);
  }
  return 0;
}
