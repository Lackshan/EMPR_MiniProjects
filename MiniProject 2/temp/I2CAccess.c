#include "lpc17xx_i2c.h"
#define I2CBUS LPC_I2C1

void SetupVals(struct I2C_M_SETUP_TYPE* trData,int* Data)
{
	trData.sl_addr7bit = 0x35;

	trData.tx_data = Data;
	trData.tx_length = sizeof(&Data);
	trData.tx_count = 0;

	trData.rx_data = NULL;
	trData.rx_length = 0;
	trData.rx_count = 0;

	trData.retransmissions_max = 2;
}
void TransferData
void main(void)
{
	struct I2C_M_SETUP_TYPE trData;
	int Data;
	
	I2C_Init(I2CBUS,100000);
	I2C_Cmd(I2CBUS,ENABLE);
	SetupVals(&trData,&Data);

	I2C_MasterTransferData(I2CBUS,&trData,I2C_TRANSFER_INTERRUPT);
	
	I2C_MonitorModeConfig(I2CBus,I2C_MONITOR_CFG_SCL_OUTPUT,ENABLE);
	I2C_MonitorModeCmd(I2CBUS,ENABLE);
	
	
}
