#include "lpc17xx_i2c.h"

void SetupVals(struct I2C_M_SETUP_TYPE* trData)
{
	trData.sl_addr7bit = 0x35;

	trData.tx_data = NULL;
	trData.tx_length = 0;
	trData.tx_count = 0;

	trData.rx_data = NULL;
	trData.rx_length = 0;
	trData.rx_count = 0;
}

void addTransfer(struct I2C_M_SETUP_TYPE* trData,int* Data)
{
	trData.tx_data = &Data;
	tx_length = sizeof(&Data);
	tx_count++;
}

void Display7Seg(){

	struct I2C_M_SETUP_TYPE trData;
	int* Data = (int*)malloc(sizeof(*Data)*2);

	SetupVals(&trData);
	Data[0] = 0x01;
	Data[1] = 0x01;

	addTransfer(&trData,&Data);	

	I2C_Init(LPC_I2C0,100000);
	I2C_Cmd(LPC_I2C0,1);
	I2C_MasterTransferData(LPC_I2C0,&trData,I2C_TRANSFER_POLLING);

	free(Data);
}

void main(void){

	Display7Seg();
}
