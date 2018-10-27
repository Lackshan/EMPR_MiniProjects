#include "I2CGetAddresses.h"

void GetAddresses(void)
{//Note: for this practical, we don't acutally need to count the addressses 
		I2C_M_SETUP_Type trData;
		int* Addresses = (int*)calloc(0xFF,sizeof(int*));
		char outputbuf[50];
		int i,AddressPtr=0;
		uint8_t Data = 0;

		I2CInit();

		InitSerial();
		SetupVals(&trData,0x00,&Data,1);
		
		for(i=0;i<128;i++)
		{//Send Data to every address and see if it SUCCEEDS
			trData.sl_addr7bit = (uint32_t)i;
			if (I2C_MasterTransferData(I2CBUS,&trData,I2C_TRANSFER_POLLING) == SUCCESS)
			{
				
				Addresses[AddressPtr*sizeof(int*)] = i;
				AddressPtr++;
			}
		}

		sprintf(outputbuf,"%d devices connected to i2c bus\n\r",AddressPtr);
		WriteText(outputbuf);
		
		WriteText("Addresses available for I2C:\n\r");
		for(AddressPtr-=1;AddressPtr>=0;AddressPtr--)
		{
			sprintf(outputbuf,"0x%X\n\r",Addresses[AddressPtr*sizeof(int*)]);
			WriteText(outputbuf);
		}
		free(Addresses);
}
