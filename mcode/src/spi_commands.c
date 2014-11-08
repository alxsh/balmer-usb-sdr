#include "spi_data_process.h"

uint8_t last_command = 0;
uint8_t last_receive_length = 33;
uint32_t last_receive_data = 33;

extern uint16_t g_spi_sended;
extern uint16_t g_spi_retry;

void SpiCommandReceive(uint8_t command, uint8_t receive_length, uint8_t* receive_buffer)
{
	last_command = command;
	last_receive_length = receive_length;
	last_receive_data = *(uint32_t*)receive_buffer;
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