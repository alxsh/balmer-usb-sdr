#include "dac.h"
#include "process_sound.h"
#include "arm_math.h"
#include "delay.h"

#include <limits.h>
#include <math.h>

#define FFT_LENGTH 256


//static arm_rfft_instance_f32 S_RFFT;
static arm_cfft_radix4_instance_f32 S_CFFT;
static int32_t in_fft_buffer32[FFT_LENGTH];
static float in_fft_buffer[FFT_LENGTH*2];
static float out_fft_buffer[FFT_LENGTH];
uint16_t fft_calculate_time = 0;
static int in_fft_cur_pos = 0;
int32_t g_fft_min = 0;
int32_t g_fft_max = 0;

void CalculateFft();

void OnSoundDataFft(int32_t sample)
{
	if(in_fft_cur_pos<FFT_LENGTH)
	{
		in_fft_buffer32[in_fft_cur_pos] = (sample>>8);
		//in_fft_buffer[in_fft_cur_pos] = (sample>>8);
		in_fft_cur_pos++;
	}
}

void InitFft()
{
	for(int i=0; i<FFT_LENGTH; i++)
	{
		in_fft_buffer[i] = 0;
	}

	float sum = 0.0f;
	for(int i=0; i<FFT_LENGTH; i++)
	{
		sum += in_fft_buffer[i];
	}

	g_fft_min = g_fft_max = sum;

	in_fft_cur_pos = 0;
	//arm_rfft_init_f32(&S_RFFT, &S_CFFT, FFT_LENGTH, 0, 0);

	uint32_t ifftFlag = 0; 
	uint32_t doBitReverse = 1;
	arm_cfft_radix4_init_f32(&S_CFFT, FFT_LENGTH,
	  								ifftFlag, doBitReverse); 
/*
	uint16_t start = TimeUs();
	//arm_rfft_f32(&S_RFFT, in_fft_buffer, out_fft_buffer);
	arm_cfft_radix4_f32(&S_CFFT, in_fft_buffer); 
	fft_calculate_time =  TimeUs()-start;
*/
}

void CalculateFft()
{
	if(in_fft_cur_pos<FFT_LENGTH)
		return;
	uint16_t start = TimeUs();
	//DelayUs(100);
	for(int i=0; i<FFT_LENGTH; i++)
	{
		in_fft_buffer[i*2] = in_fft_buffer32[i]*1e-4f;
		in_fft_buffer[i*2+1] = 0;
	}
	
	arm_cfft_radix4_f32(&S_CFFT, in_fft_buffer); 
	arm_cmplx_mag_f32(in_fft_buffer, out_fft_buffer, FFT_LENGTH);  

	float sum = 0.0f;
	for(int i=0; i<FFT_LENGTH; i++)
	{
		sum += out_fft_buffer[i];
	}
	
	g_fft_min = sum;
	g_fft_max = (uint16_t)(TimeUs()-start);

	//uint16_t start = TimeUs();
	//arm_rfft_f32(&S_RFFT, in_fft_buffer, out_fft_buffer);
	//out_fft_buffer[0] = in_fft_buffer[0]+in_fft_buffer[1];
	//fft_calculate_time =  TimeUs()-start;

	//g_fft_min = INT_MAX;
	//g_fft_max = INT_MIN;

	in_fft_cur_pos = 0;
}