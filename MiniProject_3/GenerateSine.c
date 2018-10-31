#include "GenerateSine.h"

int main()
{
  InitSerial();
  uint32_t* SineWaveTable = (uint32_t*)malloc(sizeof(uint32_t)*PRECISION);
  int Frequency = 100,i;//in Hz
  double MaxAmplitude = 3;//in Volts

  GPDMA_LLI_Type LLI_Struct;
  GPDMA_Channel_CFG_Type CCFG_Struct;
  for(i = 0;i<PRECISION;i++)
  {
    SineWaveTable[i] = (uint32_t)(sin(2*i*PI/PRECISION)* MaxAmplitude * 1241+(1241*MaxAmplitude)) ;
    //Calculate Sine and multiply Each Wavetable entry by Amplitude and convert to UINT32
  }

  InitializeGPDMA(SineWaveTable,&LLI_Struct,&CCFG_Struct,PRECISION);
  InitializeDAC();
  DAC_StartSend(Frequency,PRECISION);
  while(1)
  {
    /*for(i=0;i<PRECISION;i++)
    {
      DAC_UpdateValue(LPC_DAC,SineWaveTable[i]);
      Delay(1);
    }*/
  }//Loop forever or do what you want

  free(SineWaveTable);
  return 0;
}
