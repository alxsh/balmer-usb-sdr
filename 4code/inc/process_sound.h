#define FFT_LENGTH 256


void OnSoundData(int32_t sample);
void SoundQuant();

void InitFft();

//Куда в текущий момент пишем в буфере
uint16_t DacGetWritePos();

//Расстояние между позийией записи и чтения.
uint16_t DacGetDeltaPos();

extern uint16_t fft_to_display[FFT_LENGTH];