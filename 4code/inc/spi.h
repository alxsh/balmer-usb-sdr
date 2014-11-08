void SpiInit();

void SpiSend(uint16_t data);

//Операция завершилась успешно, можно дальше общаться с устройством.
void SpiStartSend();
void SpiEndSend();
