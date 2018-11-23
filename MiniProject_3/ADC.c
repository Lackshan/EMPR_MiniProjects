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

void ADC_InitializeGPDMA(uint32_t* Dest,GPDMA_Channel_CFG_Type* GPDMA_Cfg, int NumSamples)
{
  ADC_IntConfig(LPC_ADC,ADC_CHANNEL_2,ENABLE);

  NVIC_DisableIRQ(DMA_IRQn);
  NVIC_SetPriority(DMA_IRQn, ((0x01<<3)|0x01));

  GPDMA_Init();

  GPDMA_Cfg->ChannelNum = 0;
  GPDMA_Cfg->SrcMemAddr = 0;
  GPDMA_Cfg->DstMemAddr = (uint32_t)Dest;
  GPDMA_Cfg->TransferSize = NumSamples;
  GPDMA_Cfg->TransferWidth = 0;
  GPDMA_Cfg->TransferType = GPDMA_TRANSFERTYPE_P2M;
  GPDMA_Cfg->SrcConn = GPDMA_CONN_ADC;
  GPDMA_Cfg->DstConn = 0; //Point give data to the DAC converter memory address
  GPDMA_Cfg->DMALLI = 0;

  GPDMA_Setup(GPDMA_Cfg);

  NVIC_EnableIRQ(DMA_IRQn);
  GPDMA_ChannelCmd(0, ENABLE);
}
