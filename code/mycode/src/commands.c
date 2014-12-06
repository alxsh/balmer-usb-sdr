#include "hw_config.h"
#include "data_process.h"

void OnSetFreq(uint32_t freq);

void PacketReceive(volatile uint8_t* data, uint32_t size)
{
	uint8_t command = data[0];
	data++;
	size--;

	switch(command)
	{

	case 3://COMMAND_SET_FREQ
		OnSetFreq(*(uint32_t*)(data+0));
		return;

	case 0://COMMAND_NONE
	default:
		USBAdd8(command);
		USBAdd32(size);
		USBSend();
		break;
	}

}
