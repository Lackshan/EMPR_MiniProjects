#include "MP3.h"

void Stage2()
{
  uint32_t* SineWaveTable = (uint32_t*)malloc(sizeof(uint32_t)*PRECISION);
  int Frequency = 10,counter = 0,i;//in Hz
  double MaxAmplitude = 3,oldMax=0;//in Volts

  GPDMA_LLI_Type LLI_Struct;
  GPDMA_Channel_CFG_Type CCFG_Struct;
  for(i = 0;i<PRECISION;i++)
  {
    SineWaveTable[i] = (uint32_t)(sin(2*i*PI/PRECISION)* MaxAmplitude * 9680+(9680*MaxAmplitude));
    //Calculate Sine and multiply Each Wavetable entry by Amplitude and convert to UINT32
  }
  InitializeGPDMA(SineWaveTable,&LLI_Struct,&CCFG_Struct,PRECISION);
  DAC_StartSend(Frequency,PRECISION);
  char keyInput = ' ';
  while(keyInput == ' ')
  {//Every Ten Seconds, Change the Frequency and Amplitude
    Delay(2);
    char outputbuf[50];
    sprintf(outputbuf,"Loop %d\n\r",counter);
    WriteText(outputbuf);
    if(counter > 50)
    {
      WriteText("Changing Wave Function\n\r");
      counter = 0;
      oldMax = MaxAmplitude;
      MaxAmplitude = (((double)rand()/RAND_MAX)*MAXVOLTS)+0.5;
      for(i = 0;i<PRECISION;i++)
      {
        SineWaveTable[i] = (uint32_t)((double)(SineWaveTable[i]*MaxAmplitude)/oldMax);
      }
      DAC_StartSend(rand()%100,PRECISION);
    }
    keyInput = GetKeyInput();
    counter++;
  }
  WriteText("Finished Looping\n\r");
  free(SineWaveTable);
}
void Stage3()
{
  uint32_t Data = 0;
  char keyInput = ' ';
  while(keyInput == ' ')
  {//Read a value from ADC, output it through DAC.
    ADC_StartCmd(LPC_ADC,ADC_START_NOW);
    while(ADC_ChannelGetStatus(LPC_ADC,ADC_CHANNEL_2,1)==RESET);
    Data = ADC_GetData(ADC_CHANNEL_2);
    DAC_UpdateValue(LPC_DAC,Data);
    keyInput = GetKeyInput();
  }
}
void Stage4()
{
  void (*f)(void)  = Stage4IR;
  char keyInput = ' ';

  InitializeTIM(f);
  InitializePWM();
  StartTIM();

  while(keyInput == ' ')
  {
    keyInput = GetKeyInput();
  }
  StopTIM();
}
void Stage4IR()//Change the PWM timer
{
  ChangeDutyCycle(50);
}


int main(void)
{
  InitSerial();
  I2CInit();
  SetupPINS();
  Delay_Init();
  InitializeDAC();
  InitializeADC();

  WriteText("Initialization Comprrrete\n\r");
  Stage2();
  Delay(10);
  WriteText("Stage2 complete, starting stage 3\n\r");
  Stage3();
  Delay(10);
  WriteText("Stage3 complete, starting stage 4\n\r");
  Stage4();
  Delay(10);
  WriteText("End\n\r");
  return 0;
}
