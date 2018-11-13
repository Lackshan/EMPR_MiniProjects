#include "LCDIO.h"

void LCDClear()
{
	I2C_M_SETUP_Type trData;
	int Data[2] = {0x00,0x01};
	SetupVals(&trData,&Data,2);
	I2C_MasterTransferData(I2CBUS,&trData,I2C_TRANSFER_POLLING);
}


void LCDInit()
{
	I2C_M_SETUP_Type trData;
	int Data[15] = {0x00,0x34,0x0c,0x06,0x35,0x04,0x10,0x42,0x9f,0x34,0x02};
	SetupVals(&trData,&Data,15);
	I2C_MasterTransferData(I2CBUS,&trData,I2C_TRANSFER_POLLING);
}

void LCDPrint(char* input)//Sends Data Directly to the output stream 
{
	I2C_M_SETUP_Type trData;
	int i;
	for(i = 0; i<strlen(input);i++)
	{
		int ToSend[4] = {0x00,(0x80+i),0x40,input[i]};
		SetupVals(&trData,&ToSend,4);
		I2C_MasterTransferData(I2CBUS,&trData,I2C_TRANSFER_POLLING);
	}	
}

