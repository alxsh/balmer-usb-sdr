#include "spi_data_process.h"
#include "spi_commands.h"

extern uint16_t fft_calculate_time;

void SpiCommandReceive(uint8_t command, uint8_t receive_length, uint8_t* receive_buffer)
{
	if(command==1)
	{
		SpiAdd16(fft_calculate_time);
		//SpiAdd16(1234);
	} else
	{
		for(int i=0; i<receive_length; i++)
		{
			SpiAdd8(receive_buffer[i]);
		}

	}

	SpiSendCommand(command);
}