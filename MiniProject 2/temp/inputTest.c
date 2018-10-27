#include <stdio.h>

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

void main()
{
	char keys[4][4] = {
		{'1','2','3','A'},
		{'4','5','6','B'},
		{'7','8','9','C'},
		{'*','0','#','D'}
	};
	int i,j;
	uint8_t Data;


	InitSerial();
	
}