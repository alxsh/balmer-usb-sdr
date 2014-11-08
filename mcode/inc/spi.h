
#include <stdbool.h>

void SpiInit();

void SpiSend(uint16_t data);

extern uint16_t g_spi_rx_data;
extern bool g_spi_rx_complete;
extern uint16_t g_spi_exti;