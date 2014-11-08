#include "hw_config.h"
#include "spi_data_process.h"
#include "spi.h"
#include <string.h>

static bool receive_phase = false;

static bool spi_command_received = false;
static uint8_t spi_receive_command = 0;
static uint8_t spi_receive_length = 0;
static uint8_t spi_receive_pos = 0;
static uint8_t spi_receive_buffer[SPI_PACKET_SIZE]; 


static uint8_t spi_send_length = 0;
static uint8_t spi_send_pos = 0;
static uint8_t spi_send_buffer[SPI_PACKET_SIZE];

bool SpiBusy()
{
	return spi_send_length>0 || receive_phase;
}

static void SpiCheckCompleteSend()
{
	if(spi_send_pos>=spi_send_length)
	{
		spi_send_length = 0;
		receive_phase = true;
		spi_receive_command = 0;
		spi_receive_length = 0;
		spi_receive_pos = 0;
		spi_command_received = false;
	}
}

void SpiDataReceive(uint16_t data)
{
	if(receive_phase)
	{
		if(spi_command_received)
		{
			if(spi_receive_pos<spi_receive_length)
			{
				*(uint16_t*)(spi_receive_buffer+spi_receive_pos) = data;
				spi_receive_pos += 2;
			}

		} else
		{
			spi_command_received = true;
			spi_receive_command = data>>8;
			spi_receive_length = data&0xFF;
			if(spi_receive_length>SPI_PACKET_SIZE)
			{
				//Error!
				spi_receive_length = SPI_PACKET_SIZE;
			}
		}

		if(spi_receive_pos>=spi_receive_length)
		{
			SpiCommandReceive(spi_receive_command, spi_receive_length, spi_receive_buffer);
			receive_phase = false;
		} else
		{
			SpiSend(0);
		}
	} else
	{
		if(spi_send_pos<spi_send_length)
		{
			SpiSend(*(uint16_t*)(spi_send_buffer+spi_send_pos));
			spi_send_pos += 2;
		} else
		{
			SpiCheckCompleteSend();
		}
	}
}

void SpiAdd(uint8_t* data, uint32_t size)
{
	if(spi_send_length+size>SPI_PACKET_SIZE)
		size = SPI_PACKET_SIZE - spi_send_length;
	for(int i=0; i<size; i++)
	{
		spi_send_buffer[spi_send_length++] = data[i];
	}
}

void SpiAddStr(char* data)
{
	SpiAdd((uint8_t*)data, strlen(data));
}

void SpiAdd8(uint8_t data)
{
	SpiAdd((uint8_t*)&data, sizeof(data));
}

void SpiAdd16(uint16_t data)
{
	SpiAdd((uint8_t*)&data, sizeof(data));
}

void SpiAdd32(uint32_t data)
{
	SpiAdd((uint8_t*)&data, sizeof(data));
}

void SpiSendCommand(uint8_t command)
{
	receive_phase = false;
	uint16_t data = ((uint16_t)command)<<8;
	data |= spi_send_length;
	spi_send_pos = 0;

	SpiSend(data);
}

void SpiSlaveReady()
{
	//Иницилизируем прием данных.
	SpiSend(0);
}
