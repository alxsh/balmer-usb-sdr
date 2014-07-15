// balmer@inbox.ru 2014 SDR
#include "command.h"
#include "main.h"
#include "dds.h"

void USBCommandReceive(uint8_t* commandBuffer, uint16_t commandSize)
{
	uint32_t wrd;
	//if(commandSize==0)
	//	return;
	switch(commandBuffer[0])
	{
	case 1://COMMAND_HELLO
		USBAddStr("Hello!");
		break;
	case 2://COMMAND_DDS_WORD
		wrd = *(uint32_t*)(commandBuffer+1);
		DdsSetWord(wrd);
		USBAddStr("DDSW");
		USBAdd32(wrd);
		break;
	}
	USBSend();	
}
