#include <stdbool.h>

bool cs4272_Init();

void cs4272_write_reg(uint8_t addr, uint8_t data);
uint8_t cs4272_read_reg(uint8_t addr);

bool cs4272_i2c_Init();