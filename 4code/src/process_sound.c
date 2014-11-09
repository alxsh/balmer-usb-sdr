#include "dac.h"
#include "cs4272.h"
#include "process_sound.h"

uint16_t* DacGetBuffer();
uint16_t DacGetBufferSize();

static uint16_t g_cur_pos = SINUS_BUFFER_SIZE/2;
int g_sound_min = 1<<24;
int g_sound_max = -(1<<24);

static uint16_t g_dma_cur_pos = 0;

void OnSoundData(int32_t sample)
{
	int32_t s = (sample>>8);
	if(s>g_sound_max)
		g_sound_max = s;
	if(s<g_sound_min)
		g_sound_min = s;

	uint16_t* out_buffer = DacGetBuffer();
	out_buffer[g_cur_pos] = (sample>>(14))+DAC_ZERO;
	//out_buffer[g_cur_pos] = (sample>>(12))+DAC_ZERO;

	g_cur_pos = (g_cur_pos+1)%SINUS_BUFFER_SIZE;
}

void CopySoundData(uint16_t start, uint16_t count)
{
	uint16_t* data4 = sound_buffer+start;
	for(int idx=0; idx<count; idx+=4, data4+=4)
	{
		int32_t sample = (((int32_t)data4[0])<<16)+data4[1];
		OnSoundData(sample);
	}
}

void SoundQuant()
{
	if(!g_i2s_dma)
		return;
	//NDTR - количество байт в DMA буфере, которое еще осталось скопировать.
	uint16_t ndtr = (uint16_t)DMA1_Stream0->NDTR;
	if(ndtr>SOUND_BUFFER_SIZE)
		return;
	uint16_t pos = SOUND_BUFFER_SIZE - ndtr;
	pos = pos & ~(uint16_t)3;

	if(g_dma_cur_pos==pos)
	{
	} else
	if(g_dma_cur_pos<pos)
	{
		CopySoundData(g_dma_cur_pos, pos-g_dma_cur_pos);
	} else
	{
		CopySoundData(g_dma_cur_pos, SOUND_BUFFER_SIZE-g_dma_cur_pos);
		CopySoundData(0, pos);
	}

	g_dma_cur_pos = pos;
}