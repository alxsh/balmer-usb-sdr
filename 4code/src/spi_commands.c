#include "spi_data_process.h"
#include "spi_commands.h"
#include "dac.h"
#include "process_sound.h"

extern uint16_t fft_calculate_time;
extern int32_t g_fft_min;
extern int32_t g_fft_max;
extern uint16_t g_sound_quant_time;

void SpiCommandReceive(uint8_t command, uint8_t receive_length, uint8_t* receive_buffer)
{
	if(command==SCOMMAND_TMP)
	{
		SpiAdd16(fft_calculate_time);
		//SpiAdd16(1234);
	} else
	if(command==SCOMMAND_SOUND_BUF_DELTA)
	{
		uint16_t pos_delta = DacGetDeltaPos();
		SpiAdd32(pos_delta);
	} else
	if(command==SCOMMAND_FFT_MIN_MAX)
	{
		//SpiAdd32(fft_calculate_time);
		SpiAdd32(g_fft_min);
		//SpiAdd32(g_sound_quant_time);
		SpiAdd32(g_fft_max);
	} else
	if(command==SCOMMAND_FFT_LINE)
	{
		uint8_t offset = receive_buffer[0];
		for(int i=0; i<32; i++)
		{
			SpiAdd16(fft_to_display[offset+i]);
		}
	} else
	{
		for(int i=0; i<receive_length; i++)
		{
			SpiAdd8(receive_buffer[i]);
		}

	}

	SpiSendCommand(command);
}