
void OnSoundData(int32_t sample);
void SoundQuant();

void InitFft();

//Куда в текущий момент пишем в буфере
uint16_t DacGetWritePos();

//Расстояние между позийией записи и чтения.
uint16_t DacGetDeltaPos();