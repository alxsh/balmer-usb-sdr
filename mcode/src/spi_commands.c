#include "spi_data_process.h"
#include "ili/UTFT.h"
#include "../../4code/inc/spi_commands.h"
#include "waterfall.h"


uint8_t last_command = 0;
uint8_t last_receive_length = 33;
uint32_t last_receive_data = 33;

extern uint16_t g_spi_sended;
extern uint16_t g_spi_retry;
extern uint8_t g_slave_ready;

int32_t g_fft_min = 0;
int32_t g_fft_max = 0;
uint16_t g_fft_line_offset = 0;


void printCmd()
{
    UTFT_setFont(BigFont);
    
    uint8_t y = 1;
    if(SpiBusy())
    	UTFT_setColor(255, 255, 0);
    else
    	UTFT_setColor(0, 128, 255);
    //UTFT_printNumI(g_spi_sended, 16, 32, 5, ' ');
    UTFT_print("Cmd", 0, 16*y, 0);

    UTFT_setColor(0, 128, 255);
    UTFT_printNumI(last_command, 16*4, 16*y, 3, ' ');
    UTFT_printNumI(g_slave_ready, 16*11, 16*y, 3, ' ');
    y++;

    UTFT_print("Len", 0, 16*y, 0);
    UTFT_printNumI(last_receive_length, 16*4, 16*y, 3, ' ');
    y++;


    UTFT_print("D=", 0, 16*y, 0);
    UTFT_printNumI(last_receive_data, 16*3, 16*y, 5, ' ');
    y++;    

    UTFT_print("MI=", 0, 16*y, 0);
    UTFT_printNumI(g_fft_min, 16*3, 16*y, 6, ' ');
    y++;    

    UTFT_print("MA=", 0, 16*y, 0);
    UTFT_printNumI(g_fft_max, 16*3, 16*y, 6, ' ');
    y++;    
}


void SpiCommandReceive(uint8_t command, uint8_t receive_length, uint8_t* receive_buffer)
{
	last_command = command;
	last_receive_length = receive_length;

	if(command==SCOMMAND_SOUND_BUF_DELTA)
	{
        last_receive_data = *(uint32_t*)receive_buffer;
		SpiSendCommand(SCOMMAND_FFT_MIN_MAX);
	} else
	if(command==SCOMMAND_FFT_MIN_MAX)
	{
		if(receive_length>=8)
		{
			g_fft_min = *(int32_t*)(receive_buffer+0);
			g_fft_max = *(int32_t*)(receive_buffer+4);

            SpiAdd8(g_fft_line_offset);
            SpiSendCommand(SCOMMAND_FFT_LINE);
		}
	} else
    if(command==SCOMMAND_FFT_LINE)
    {
        for(int i=0; i<32; i++)
        {
            int idx = i+g_fft_line_offset;
            if(idx<WATERFALL_WIDTH)
                w_line[idx] = AmplitudeToColor(((uint16_t*)receive_buffer)[i]);
        }

        g_fft_line_offset+=32;
        if(g_fft_line_offset<256)
        {
            SpiAdd8(g_fft_line_offset);
            SpiSendCommand(SCOMMAND_FFT_LINE);
        } else
        {
            g_fft_line_offset = 0;
        }
    }
/*
	if(g_spi_retry>0)
	{
		SpiAdd16(g_spi_sended);
		SpiSendCommand(2);
		g_spi_retry--;
		g_spi_sended++;
	}
*/
}