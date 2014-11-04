#include "dac.h"
uint16_t* DacGetBuffer();
uint16_t DacGetBufferSize();

static uint16_t g_cur_pos = SINUS_BUFFER_SIZE/2;

void OnSoundData(int32_t sample)
{
	uint16_t* out_buffer = DacGetBuffer();
	out_buffer[g_cur_pos] = (sample>>(14))+DAC_ZERO;

	g_cur_pos = (g_cur_pos+1)%SINUS_BUFFER_SIZE;
}