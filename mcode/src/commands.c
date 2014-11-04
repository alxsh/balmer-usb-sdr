#include "hw_config.h"
#include "data_process.h"
#include "ili/UTFT.h"
#include "spi.h"

uint16_t g_spi_sended = 0;

void PacketReceive(volatile uint8_t* data, uint32_t size)
{
	uint8_t command = data[0];
	data++;
	size--;

	switch(command)
	{
	case 1://COMMAND_PRINT_INT
		{
			volatile int value = *(int*)(data+0);
			volatile int x = *(int*)(data+4);
			volatile int y = *(int*)(data+8);
			
			UTFT_printNumI(value,
						   x,
						   y, 0, ' ');
		}
		return;

	case 2://COMMAND_SEND_SPI
		{
			g_spi_sended = *(uint16_t*)(data+0);
			SpiSend(g_spi_sended);
		}
		return;

	case 0://COMMAND_NONE
	default:
		USBAdd8(command);
		USBAdd32(size);
		USBSend();
		break;
	}

}
