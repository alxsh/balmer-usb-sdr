#include "spi_data_process.h"

uint8_t last_command = 0;
uint8_t last_receive_length = 33;
uint32_t last_receive_data = 33;

void SpiCommandReceive(uint8_t command, uint8_t receive_length, uint8_t* receive_buffer)
{
	last_command = command;
	last_receive_length = receive_length;
	last_receive_data = *(uint32_t*)receive_buffer;
}