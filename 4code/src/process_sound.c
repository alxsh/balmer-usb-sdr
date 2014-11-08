#include "dac.h"
uint16_t* DacGetBuffer();
uint16_t DacGetBufferSize();

static uint16_t g_cur_pos = SINUS_BUFFER_SIZE/2;
int g_sound_min = 1<<24;
int g_sound_max = -(1<<24);

void OnSoundData(int32_t sample)
{
	int32_t s = (sample>>8);
	if(s>g_sound_max)
		g_sound_max = s;
	if(s<g_sound_min)
		g_sound_min = s;

	uint16_t* out_buffer = DacGetBuffer();
	out_buffer[g_cur_pos] = (sample>>(14))+DAC_ZERO;
	//out_buffer[g_cur_pos] = (sample>>(8))+DAC_ZERO;

	g_cur_pos = (g_cur_pos+1)%SINUS_BUFFER_SIZE;
}