#include "spi_data_process.h"

void SpiCommandReceive(uint8_t command, uint8_t receive_length, uint8_t* receive_buffer)
{
	for(int i=0; i<receive_length; i++)
	{
		SpiAdd8(receive_buffer[i]);
	}

	SpiSendCommand(command);
}