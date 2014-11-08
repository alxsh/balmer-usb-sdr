#include "spi_data_process.h"

void SpiCommandReceive(uint8_t command, uint8_t receive_length, uint8_t* receive_buffer)
{
	SpiAdd32(1234);
	SpiSendCommand(command);
}