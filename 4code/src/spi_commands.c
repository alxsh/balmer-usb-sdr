#include "spi_data_process.h"
#include "spi_commands.h"
#include "dac.h"
#include "process_sound.h"

extern uint16_t fft_calculate_time;

void SpiCommandReceive(uint8_t command, uint8_t receive_length, uint8_t* receive_buffer)
{
	if(command==SCOMMAND_TMP)
	{
		SpiAdd16(fft_calculate_time);
		//SpiAdd16(1234);
	} else
	if(command==SCOMMAND_SOUND_BUF_DELTA)
	{
		uint16_t pos_in = DacGetWritePos();
		uint16_t pos_out = DacGetReadPos();
		uint16_t pos_delta = 0;
		if(pos_out>pos_in)
		{
			pos_delta = pos_out-pos_in;
		} else
		{
			pos_delta = DAC_BUFFER_SIZE+pos_out-pos_in;
		}

		SpiAdd16(pos_delta);
	} else
	{
		for(int i=0; i<receive_length; i++)
		{
			SpiAdd8(receive_buffer[i]);
		}

	}

	SpiSendCommand(command);
}