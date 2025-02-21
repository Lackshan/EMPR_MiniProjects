#include "MP3.h"
#define PWMPRESCALE (25-1) //25 PCLK cycles to increment TC by 1 i.e. 1 Micro-second

void EINT3_IRQHandler(void)
{
  LPC_SC->EXTINT = 1<<3;
  LPC_GPIOINT->IO0IntClr = (1<<5);
  key = GetKeyInput();
  if(key != prevKey && key != ' ')
  {
    buttonpress  = 1;
    prevKey = key;
    WriteText("button Pressed");
  }
  else if (key == ' ')
  {
    prevKey = ' ';
  }
}

void Stage2()
{
  buttonpress = 0;
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
  while(buttonpress == 0)
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
    counter++;
  }
  WriteText("Finished Looping\n\r");
  free(SineWaveTable);
}
void Stage3()
{
  buttonpress = 0;
  uint32_t Data = 0;
  while(buttonpress == 0)
  {//Read a value from ADC, output it through DAC.
    ADC_StartCmd(LPC_ADC,ADC_START_NOW);
    while(ADC_ChannelGetStatus(LPC_ADC,ADC_CHANNEL_2,1)==RESET);
    Data = ADC_GetData(ADC_CHANNEL_2);
    DAC_UpdateValue(LPC_DAC,Data);
  }
}

void Stage4()
{
  PWM_Pin_Type P26 = {&LPC_PINCON->PINSEL4, (1<<0), &LPC_PWM1->MR1}; // PWM 1.1 on Pin 2.0 - DIP26
  initPWM(P26);
  initTimer(LPC_TIM0);
  int j;
  for(j=0; j<5; j++) {
      int i;
      for(i=0; i<=1000; i++) {
          updatePulseWidth(P26, i);
          delayMS(5, LPC_TIM0);
    }
  }

}

int main(void)
{
  InitSerial();
  key = ' ';
  SystemInit();
  LPC_GPIO0->FIODIR &= ~(1<<5);
  LPC_GPIOINT->IO0IntClr = (1<<5);
  LPC_SC->EXTINT = 1<<3;
  LPC_GPIOINT->IO0IntEnF |= (1<<5);

  /*LPC_PINCON->PINSEL1 = (1<<7);//Check which pins the pcf8574 uses
  LPC_SC->EXTMODE = 1; //Edge Triggered
  LPC_SC->EXTPOLAR = 1;//Falling vs Rising Edge*/
  NVIC_EnableIRQ(EINT3_IRQn);
  __enable_irq();

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
