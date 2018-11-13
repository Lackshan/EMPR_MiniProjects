#include "PWM.h"
//This is for the standard pwm module. There is also mcpwm for motor control.
void InitializePWM()
{
  PINSEL_CFG_Type PINCFG;//PWM - check the pin
  PINCFG.Funcnum = 1;
  PINCFG.OpenDrain =0;
  PINCFG.Pinmode = 0;
  PINCFG.Pinnum = 0;
  PINCFG.Portnum = 2;
  PINSEL_ConfigPin(&PINCFG);

  PWM_TIMERCFG_Type timercfg;
  timercfg.PrescaleOption = PWM_TIMER_PRESCALE_USVAL;
  timercfg.PrescaleValue = 1;//I don't know what this should actually be. //Tick Time in microseconds
  PWM_ConfigStructInit(PWM_MODE_TIMER,&timercfg);

  PWM_Init(LPC_PWM1,PWM_MODE_TIMER,&timercfg);
  PWM_ChannelConfig(LPC_PWM1,1,PWM_CHANNEL_SINGLE_EDGE);//Figure out which channel to use



  PWM_MATCHCFG_Type MatchConfig;
  MatchConfig.IntOnMatch = DISABLE;
  MatchConfig.MatchChannel = 0;
  MatchConfig.ResetOnMatch = DISABLE;
  MatchConfig.StopOnMatch = DISABLE;

  PWM_MatchUpdate(LPC_PWM1,0,100,PWM_MATCH_UPDATE_NOW);
  PWM_ConfigMatch(LPC_PWM1,&MatchConfig);
//  PWM_ChannelCmd(LPC_PWM1,0,ENABLE);
  MatchConfig.MatchChannel = 1;

  PWM_MatchUpdate(LPC_PWM1,1,20,PWM_MATCH_UPDATE_NOW);
  PWM_ConfigMatch(LPC_PWM1,&MatchConfig);
  PWM_ChannelCmd(LPC_PWM1,1,ENABLE);
  PWM_ResetCounter(LPC_PWM1);
  PWM_CounterCmd(LPC_PWM1,ENABLE);
  PWM_Cmd(LPC_PWM1,ENABLE);

}

void ChangeDutyCycle(uint32_t percent)
{
  PWM_MatchUpdate(LPC_PWM1,1,percent,PWM_MATCH_UPDATE_NOW);
}
