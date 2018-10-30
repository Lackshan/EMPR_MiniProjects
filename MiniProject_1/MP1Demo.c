#include "MP1Demo.h"

void main(void)
{
	int i;
	setupAll();
	SysTick_Config(SystemCoreClock/10-1);
	InitSerial();
	WriteText("Starting Count\n\r");
	WriteText("Dec - Hex - Bin\n\r");
	char outputbuf[50];
	for(i=0;i<16;i++)
	{
		sprintf(&outputbuf,"%d   - 0x%X - %c%c%c%c\n\r",i,i,INT_TO_NIBBLE(i)) ;
		WriteText(outputbuf);
		displaydigit(i);
		Delay(10);
		clearAll();

	}
	WriteText("Finished Count\n\r");
}


void InitSerial()
{
	UART_CFG_Type UartConfiguration;
	UART_FIFO_CFG_Type FifoConfiguration;
	PINSEL_CFG_Type PinConfig;
	
	PinConfig.Funcnum = 1;
	PinConfig.OpenDrain = 0;
	PinConfig.Pinmode = 0;
	PinConfig.Portnum = 0;
	PinConfig.Pinnum = 2;
	PINSEL_ConfigPin(&PinConfig);
	PinConfig.Pinnum = 3;
	PINSEL_ConfigPin(&PinConfig);

	UART_ConfigStructInit(&UartConfiguration);
	UART_FIFOConfigStructInit(&FifoConfiguration);
	
	UART_Init((LPC_UART_TypeDef *)LPC_UART0, &UartConfiguration);
	UART_FIFOConfig((LPC_UART_TypeDef *)LPC_UART0, &FifoConfiguration);
	UART_TxCmd((LPC_UART_TypeDef *)LPC_UART0, ENABLE);
}

int WriteText(char* TexttoWrite)
{
	return(UART_Send((LPC_UART_TypeDef *)LPC_UART0,(uint8_t*)TexttoWrite,strlen(TexttoWrite)+1, BLOCKING));
}

void displaydigit(int input)
{	
	int i;
	unsigned long int cake[4]  = {LED1,LED2,LED3,LED4};
	for(i=0;i<4;i++)
	{
		if(input == 0)return;

		if(input%2)
		{
			GPIO_SetValue(1,cake[i]);
		}
	input/=2;	
	}	
}

void setupAll(void)
{
	GPIO_SetDir(1,LED1,1);
	GPIO_SetDir(1,LED2,1);
	GPIO_SetDir(1,LED3,1);
	GPIO_SetDir(1,LED4,1);
}
void clearAll(void)
{
	GPIO_ClearValue(1,LED1);
	GPIO_ClearValue(1,LED2);
	GPIO_ClearValue(1,LED3);
	GPIO_ClearValue(1,LED4);
}

void SysTick_Handler(void)
{
	Counter++;
}

void Delay(unsigned long tick)
{
	unsigned long systickcnt;
	systickcnt = Counter;
	while((Counter-systickcnt)<tick);
}
