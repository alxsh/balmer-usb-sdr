#include <stdbool.h>

#define SPI_PACKET_SIZE 64

//prototype, declared in annoter file
//Получили ответ от slave
void SpiCommandReceive(uint8_t command, uint8_t receive_length, uint8_t* receive_buffer);

//Пришли данные от slave
void SpiDataReceive(uint16_t data);
//slave говорит, что он говто посылать ответ
void SpiSlaveReady();
//если true, то данные нельзя посылать
bool SpiBusy();

//add data to packet
void SpiAdd(uint8_t* data, uint32_t size);
void SpiAddStr(char* data);
void SpiAdd8(uint8_t data);
void SpiAdd16(uint16_t data);
void SpiAdd32(uint32_t data);
//send command + data filled before 
void SpiSendCommand(uint8_t command);
