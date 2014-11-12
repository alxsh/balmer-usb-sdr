#include "dac.h"
#include "cs4272.h"
#include "process_sound.h"
#include "arm_math.h"
#include "delay.h"

uint16_t* DacGetBuffer();
uint16_t DacGetBufferSize();

#define FFT_LENGTH 512

static uint16_t g_cur_pos = DAC_BUFFER_SIZE/2;
int g_sound_min = 1<<24;
int g_sound_max = -(1<<24);
static uint16_t g_dma_cur_pos = 0;

static arm_rfft_instance_f32 S_RFFT;
static arm_cfft_radix4_instance_f32 S_CFFT;
float32_t in_fft_buffer[FFT_LENGTH];
float32_t out_fft_buffer[FFT_LENGTH];
uint16_t fft_calculate_time = 0;

static uint16_t prev_time_ms = 0;

uint16_t DacGetWritePos()
{
	return g_cur_pos;
}

uint16_t DacGetDeltaPos()
{
	uint16_t pos_in = DacGetWritePos();
	uint16_t pos_out = DacGetReadPos();
	uint16_t pos_delta;
	if(pos_out>pos_in)
	{
		pos_delta = pos_out-pos_in;
	} else
	{
		pos_delta = DAC_BUFFER_SIZE+pos_out-pos_in;
	}

	return pos_delta;
}

void DacCorrectWritePos()
{
	uint16_t pos_delta = DacGetDeltaPos();

	g_cur_pos += pos_delta-DAC_BUFFER_SIZE/2;
	g_cur_pos %= DAC_BUFFER_SIZE;
}

void OnSoundData(int32_t sample)
{
	uint16_t* out_buffer = DacGetBuffer();
	int s = (sample>>(14))+DAC_ZERO;;
	if(s<0)
		s = 0;
	if(s>4095)
		s=4095;
	out_buffer[g_cur_pos] = s;

	g_cur_pos = (g_cur_pos+1)%DAC_BUFFER_SIZE;
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
		pos = (pos+SOUND_BUFFER_SIZE-4)%SOUND_BUFFER_SIZE;
		if(g_dma_cur_pos<pos)
		{
			CopySoundData(g_dma_cur_pos, pos-g_dma_cur_pos);
			g_dma_cur_pos = pos;
		}
	} else
	{
		//pos = (pos+SOUND_BUFFER_SIZE-4)%SOUND_BUFFER_SIZE;
		if(pos<g_dma_cur_pos)
		{
			CopySoundData(g_dma_cur_pos, SOUND_BUFFER_SIZE-g_dma_cur_pos);
			CopySoundData(0, pos);
			g_dma_cur_pos = pos;
		}
	}

	//Раз в секунду корректируем положение записи, чтобы была синхронизация частоты чтением и записью.
	uint16_t cur_time = TimeMs();
	if( ((uint16_t)(cur_time-prev_time_ms))>1000)
	{
		prev_time_ms = cur_time;
		DacCorrectWritePos();
	}

}

void InitFft()
{
	arm_rfft_init_f32(&S_RFFT, &S_CFFT, FFT_LENGTH, 0, 0);

	for(int i=0; i<FFT_LENGTH; i+=2)
	{
		in_fft_buffer[i] = 0.0f;
		in_fft_buffer[i+1] = 1.0f;
	}

	uint16_t start = TimeUs();
	arm_rfft_f32(&S_RFFT, in_fft_buffer, out_fft_buffer);
	fft_calculate_time =  TimeUs()-start;
}
