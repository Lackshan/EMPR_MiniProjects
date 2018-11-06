#include "TIM.h"

void (*f)(void) = 0;

void InitializeTIM(void (*function)(void))
{
  f = function;//The function to be run on an interrupt

  TIM_TIMERCFG_Type timercfg;
  timercfg.PrescaleOption = TIM_PRESCALE_USVAL;
  timercfg.PrescaleValue = 100;
  TIM_ConfigStructInit(TIM_TIMER_MODE,&timercfg);

  TIM_MATCHCFG_Type matchcfg;
  matchcfg.MatchChannel = 0;
  matchcfg.IntOnMatch = TRUE;
  matchcfg.ResetOnMatch = TRUE;
  matchcfg.StopOnMatch = FALSE;
  matchcfg.ExtMatchOutputType = TIM_EXTMATCH_TOGGLE;
  matchcfg.MatchValue = 500;
  TIM_ConfigMatch(TINST,&matchcfg);

  NVIC_SetPriority(TIMER0_IRQn,0x09);
  NVIC_EnableIRQ(TIMER0_IRQn);

  TIM_Init(TINST,TIM_TIMER_MODE,&timercfg);

}

void TIMER0_IRQHandler(void)
{
  TIM_ClearIntPending(TINST,TIM_MR0_INT);
  TIM_ResetCounter(TINST);
  f(); // Runs the specified function every interrupt
}

void StartTIM()
{
  TIM_Cmd(TINST,ENABLE);
}

void StopTIM()
{
  TIM_Cmd(TINST,DISABLE);
  TIM_DeInit(TINST);
}
