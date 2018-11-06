#include "GenerateSine.h"

int main()
{//NOTE: Pin Is PIN 18 on the header board
  InitSerial();
  Delay_Init();
  uint32_t* SineWaveTable = (uint32_t*)malloc(sizeof(uint32_t)*PRECISION);
  int Frequency = 10,i;//in Hz
  double MaxAmplitude = 3,oldMax=0;//in Volts

  GPDMA_LLI_Type LLI_Struct;
  GPDMA_Channel_CFG_Type CCFG_Struct;
  for(i = 0;i<PRECISION;i++)
  {
    SineWaveTable[i] = (uint32_t)(sin(2*i*PI/PRECISION)* MaxAmplitude * 9680+(9680*MaxAmplitude));
    //Calculate Sine and multiply Each Wavetable entry by Amplitude and convert to UINT32
  }
  InitializeDAC();
  InitializeGPDMA(SineWaveTable,&LLI_Struct,&CCFG_Struct,PRECISION);
  DAC_StartSend(Frequency,PRECISION);
  while(1)
  {//Every Ten Seconds, Change the Frequency and Amplitude
    Delay(100);
    oldMax = MaxAmplitude;
    MaxAmplitude = (((double)rand()/RAND_MAX)*MAXVOLTS)+0.5;
    for(i = 0;i<PRECISION;i++)
    {
      SineWaveTable[i] = (uint32_t)((double)(SineWaveTable[i]*MaxAmplitude)/oldMax);
    }
    DAC_StartSend(rand()%100,PRECISION);
    WriteText("Changed\n\r");

  }//Loop forever or do what you want

  free(SineWaveTable);
  return 0;
}
