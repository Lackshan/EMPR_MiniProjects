#include "ADC.h"
#include <stdlib.h>


int main()
{
  InitSerial();
  Delay_Init();
  InitializeADC();
  uint32_t Data = 0;
  char output[50] = "";
  while(1)
  {
    ADC_StartCmd(LPC_ADC,ADC_START_NOW);
    while(ADC_ChannelGetStatus(LPC_ADC,ADC_CHANNEL_2,1)==RESET) {  }
    Data = ADC_GetData(ADC_CHANNEL_2);
    double voltage = ((double)Data/4095)*3.3;
    sprintf(output,"%lf\n\r",voltage);
    WriteText(output);
    Delay(5);
  }
  ADC_DeInit(LPC_ADC);
  return 0;
}
