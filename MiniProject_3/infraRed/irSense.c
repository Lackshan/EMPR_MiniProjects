#include "irSense.h"


void LedsOFF()
{
  LPC_GPIO1->FIOCLR = 0xffffffff;
}
void LedsON()
{
  LPC_PINCON->PINSEL3 = 0x000000;
  LPC_GPIO1->FIODIR = 0xffffffff;
  LPC_GPIO1->FIOSET = 0xffffffff;
}

double getADC()
{
  ADC_StartCmd(LPC_ADC,ADC_START_NOW);
  while(ADC_ChannelGetStatus(LPC_ADC,ADC_CHANNEL_2,1)==RESET) {  }
  return (double)ADC_GetData(ADC_CHANNEL_2);
}
dtuple Calibrate()
{
  dtuple output;
  output.i= 0;
  output.j=0;
  int i = 0;
  LCDGoHome();
  LCDPrint("Calibration     \nStart          ");
  Delay(20);
  LCDGoHome();
  LCDPrint("Place hand 10cm \nAway from unit ");
  Delay(40);//LEDS turned on for calibration
  LedsON();
  for(i = 0;i<10;i++)
  {
    output.i+=getADC();
    Delay(5);
  }
  output.i/=i;
  LedsOFF();
  Delay(20);
  LCDGoHome();
  LCDPrint("Place hand 80cm \nAway from unit ");
  Delay(40);
  LedsON();
  for(i = 0;i<10;i++)
  {
    output.j+=getADC();
    Delay(5);
  }
  output.j/=i;
  LedsOFF();
  return output;
}

int main()
{
  SysTick_Config(SystemCoreClock/10-1);
  SetupPINS();
	I2C_Init(I2CBUS,100000);
	I2C_Cmd(I2CBUS,ENABLE);
	LCDInit();
	LCDClear();

  InitSerial();
  Delay_Init();
  InitializeADC();

  LCDPrint("*Infrrrarrred-3*\nDoo Doo Doo Doo");
  Delay(30);
  LCDGoHome();
  LCDPrint("1.Calibrate     \n2.Ranging Mode ");
  char keyInput = ' ';
  dtuple avgs;
  while(keyInput !=  '1' && keyInput != '2')
  {
    keyInput = GetKeyInput();
  }
  if(keyInput == '1')
  {
    avgs = Calibrate();
  }
  else if(keyInput == '2')
  {
    avgs.j = 640;
    avgs.i = 3150;
  }
  double Data = 0,constant = (3.3/(4095*4095))*(avgs.i-avgs.j);
  int i = 0;
  char output[50] = "";
  LCDClear();
  Delay(20);
  while(1)
  {
    Data = 0;
    for(i=0;i<10;i++)
    {
      Data += getADC();
    }
    Data/=10;

    double voltage = ((double)Data/4095)*3.3;
    double calicalculation = (avgs.i-avgs.j)/(0.0875*Data);//1/((Data-avgs.j)*constant);//(4095*80/(3.3*(avgs.i + constant*Data)))+10;
    //double distance = (1.85/(0.047297297*(voltage+0.1)))-5;//voltrange^2/0.0875 *voltage+offset
    //if( distance > 80)distance = 80;
    if( calicalculation > 80)calicalculation = 80;
  //  double distance  = ((abs(Data-avgs.i))/(avgs.i-avgs.j))*70 + 10;
    sprintf(output,"%lf V   \n%lf cm   ",voltage,calicalculation);
    LCDGoHome();
    LCDPrint(output);
    Delay(20);
  }
  ADC_DeInit(LPC_ADC);
  return 0;
}
/*

Max = 200

Min = 3000



*/
