#ifndef _COMMAND_H_
#define _COMMAND_H_
#include <stdbool.h>

void USBCommandReceive(uint8_t* commandBuffer, uint16_t commandSize);

void USBAdd(uint8_t* data, uint32_t size);
void USBAddStr(char* data);
void USBAdd8(uint8_t data);
void USBAdd16(uint16_t data);
void USBAdd32(uint32_t data);
void USBSend(void);

#endif//_COMMAND_H_