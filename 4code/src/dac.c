//balmer@inbox.ru
//STM32F405+CS4272 DSP module

#include <math.h>
//#include "SysTick/systick.h"
#include "dac.h"

/*
#define DAC_ZERO 2047
#define DAC_AMPLITUDE 1200

//max 375 khz
#define MIN_SINUS_PERIOD 192

static uint16_t g_dac_amplitude = DAC_AMPLITUDE;
static uint16_t g_sinusBuffer[SINUS_BUFFER_SIZE];
static uint32_t SinusBufferSize = SINUS_BUFFER_SIZE;
static uint32_t g_dac_period = 0; // * 1/SystemCoreClock sec SystemCoreClock==72000000
float g_sinusBufferFloat[SINUS_BUFFER_SIZE];

uint32_t DacPeriod(void)
{
	return g_dac_period;
}

float DacFrequency()
{
	if(g_dac_period==0)
		return 1.0f;
	return SystemCoreClock/(float)g_dac_period;
}

uint32_t DacSamplesPerPeriod(void)
{
	return SinusBufferSize;
}

uint32_t DacSampleTicks(void)
{
	return g_dac_period/SinusBufferSize;
}

void DacSinusCalculate()
{
	float mul = 2*pi/SinusBufferSize;
	for(int i=0; i<SinusBufferSize; i++)
	{
		float s = sin(i*mul);
		g_sinusBufferFloat[i] = s;
		g_sinusBuffer[i] = (uint16_t) lround(s*g_dac_amplitude)+DAC_ZERO;
	}
}

void DacInit(void)
{  
	DacSinusCalculate();
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA1, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC, ENABLE);	

	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

  	DAC_InitTypeDef DAC_InitStructure;
	DAC_InitStructure.DAC_Trigger = DAC_Trigger_None;
	DAC_InitStructure.DAC_WaveGeneration = DAC_WaveGeneration_None;
	DAC_InitStructure.DAC_OutputBuffer = DAC_OutputBuffer_Enable;
	
	DAC_Init(DAC_Channel_1, &DAC_InitStructure);
	//delay_us(100);
	DAC_Cmd(DAC_Channel_1, ENABLE);
	DAC_SetChannel1Data(DAC_Align_12b_R, DAC_ZERO);

}


//If frequency<=1 khz
//	SinusBufferSize maximal
//	TIM_Period = SystemCoreClock / SINUS_BUFFER_SIZE / frequency
void DacSetFrequency(uint32_t frequency)
{
	DacSetPeriod(SystemCoreClock/frequency, DAC_AMPLITUDE);
}

//	sinusPeriod in SystemCoreClock quants
void DacSetPeriod(uint32_t sinusPeriod, uint16_t amplitude)
{
	g_dac_amplitude = amplitude;
	if(sinusPeriod<MIN_SINUS_PERIOD)
		sinusPeriod = MIN_SINUS_PERIOD;
	//assert_param(frequency>=100 && frequency<=200000);
	DMA_Cmd(DMA1_Stream2, DISABLE);
	TIM_Cmd(TIM2, DISABLE);

	DAC_SetChannel1Data(DAC_Align_12b_R, DAC_ZERO);

	uint32_t prescaler;
	uint32_t period;
	prescaler = 1;
	period = 24;

	//Нужно чтобы SinusBufferSize был кратен 4
	sinusPeriod = (sinusPeriod/(period*4))*(period*4);

	//Пусть будет не кратным 4, попробуем частоту 100 КГц
	//sinusPeriod = (sinusPeriod/period)*period;

	SinusBufferSize = sinusPeriod/period;

	if(SinusBufferSize>SINUS_BUFFER_SIZE)
	{
		//period = 72;
		prescaler = sinusPeriod/period/SINUS_BUFFER_SIZE;
		while(SINUS_BUFFER_SIZE*prescaler*period<sinusPeriod)
		{
			prescaler++;
		}

		uint32_t p4 = period*prescaler*4;
		sinusPeriod = (sinusPeriod/p4)*p4;

		SinusBufferSize = sinusPeriod/period/prescaler;
	}

	DacSinusCalculate();

	DMA_InitTypeDef DMA_InitStructure;
	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&DAC->DHR12R1;
	DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)&g_sinusBuffer;
	DMA_InitStructure.DMA_DIR = DMA_DIR_MemoryToPeripheral;
	DMA_InitStructure.DMA_BufferSize = SinusBufferSize;
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;
	DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;         
	DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_HalfFull;
	DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
	DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
	DMA_Cmd(DMA1_Channel2, ENABLE);


	//72 MHz / TIM_Prescaler / TIM_Period
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
	TIM_TimeBaseStructure.TIM_Period = period-1;
	TIM_TimeBaseStructure.TIM_Prescaler = prescaler-1;
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
	TIM_SetCounter(TIM2, 0);

	TIM_DMACmd(TIM2, TIM_DMA_Update, ENABLE);

#ifdef USE_ADC12
	TIM_OCInitTypeDef TIM_OCInitStructure;
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = 1;
	TIM_OCInitStructure.TIM_OCPolarity=TIM_OCPolarity_Low;
	TIM_OC2Init(TIM2, &TIM_OCInitStructure);//ADC1 EXT3
#else
	TIM_OCInitTypeDef TIM_OCInitStructure;
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = 1;
	TIM_OCInitStructure.TIM_OCPolarity=TIM_OCPolarity_Low;
	TIM_OC3Init(TIM2, &TIM_OCInitStructure);//ADC3 EXT1
#endif

	g_dac_period = period * prescaler * SinusBufferSize;
}

void DacStart()
{
	TIM_Cmd(TIM2, ENABLE);
}
*/

#define   OUT_FREQ          5000                                 // Output waveform frequency
#define   SINE_RES          128                                  // Waveform resolution
#define   DAC_DHR12R1_ADDR  0x40007408                           // DMA writes into this reg on every request
#define   CNT_FREQ          42000000                             // TIM6 counter clock (prescaled APB1)
#define   TIM_PERIOD        ((CNT_FREQ)/((SINE_RES)*(OUT_FREQ))) // Autoreload reg value

const uint16_t function[SINE_RES] = { 2048, 2145, 2242, 2339, 2435, 2530, 2624, 2717, 2808, 2897, 
                                      2984, 3069, 3151, 3230, 3307, 3381, 3451, 3518, 3581, 3640, 
                                      3696, 3748, 3795, 3838, 3877, 3911, 3941, 3966, 3986, 4002, 
                                      4013, 4019, 4020, 4016, 4008, 3995, 3977, 3954, 3926, 3894, 
                                      3858, 3817, 3772, 3722, 3669, 3611, 3550, 3485, 3416, 3344, 
                                      3269, 3191, 3110, 3027, 2941, 2853, 2763, 2671, 2578, 2483, 
                                      2387, 2291, 2194, 2096, 1999, 1901, 1804, 1708, 1612, 1517, 
                                      1424, 1332, 1242, 1154, 1068, 985, 904, 826, 751, 679, 
                                      610, 545, 484, 426, 373, 323, 278, 237, 201, 169, 
                                      141, 118, 100, 87, 79, 75, 76, 82, 93, 109, 
                                      129, 154, 184, 218, 257, 300, 347, 399, 455, 514, 
                                      577, 644, 714, 788, 865, 944, 1026, 1111, 1198, 1287, 
                                      1378, 1471, 1565, 1660, 1756, 1853, 1950, 2047 };           

static void TIM6_Config(void);
static void DAC1_Config(void);           

void DacTestInit()
{
  GPIO_InitTypeDef gpio_A;
 
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);                  
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC, ENABLE);
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA1, ENABLE);

  gpio_A.GPIO_Pin  = GPIO_Pin_4;
  gpio_A.GPIO_Mode = GPIO_Mode_AN;
  gpio_A.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOA, &gpio_A);

  TIM6_Config();  
  DAC1_Config(); 
}

static void TIM6_Config(void)
{
  TIM_TimeBaseInitTypeDef TIM6_TimeBase;

  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE);
 
  TIM_TimeBaseStructInit(&TIM6_TimeBase); 
  TIM6_TimeBase.TIM_Period        = (uint16_t)TIM_PERIOD;          
  TIM6_TimeBase.TIM_Prescaler     = 10;       
  TIM6_TimeBase.TIM_ClockDivision = 0;    
  TIM6_TimeBase.TIM_CounterMode   = TIM_CounterMode_Up;  
  TIM_TimeBaseInit(TIM6, &TIM6_TimeBase);
  TIM_SelectOutputTrigger(TIM6, TIM_TRGOSource_Update);

  TIM_Cmd(TIM6, ENABLE);
}

static void DAC1_Config(void)
{
  DAC_InitTypeDef DAC_INIT;
  DMA_InitTypeDef DMA_INIT;
  
  DAC_INIT.DAC_Trigger        = DAC_Trigger_T6_TRGO;
  DAC_INIT.DAC_WaveGeneration = DAC_WaveGeneration_None;
  DAC_INIT.DAC_OutputBuffer   = DAC_OutputBuffer_Enable;
  DAC_Init(DAC_Channel_1, &DAC_INIT);

  DMA_DeInit(DMA1_Stream5);
  DMA_INIT.DMA_Channel            = DMA_Channel_7;  
  DMA_INIT.DMA_PeripheralBaseAddr = (uint32_t)DAC_DHR12R1_ADDR;
  DMA_INIT.DMA_Memory0BaseAddr    = (uint32_t)&function;
  DMA_INIT.DMA_DIR                = DMA_DIR_MemoryToPeripheral;
  DMA_INIT.DMA_BufferSize         = SINE_RES;
  DMA_INIT.DMA_PeripheralInc      = DMA_PeripheralInc_Disable;
  DMA_INIT.DMA_MemoryInc          = DMA_MemoryInc_Enable;
  DMA_INIT.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
  DMA_INIT.DMA_MemoryDataSize     = DMA_MemoryDataSize_HalfWord;
  DMA_INIT.DMA_Mode               = DMA_Mode_Circular;
  DMA_INIT.DMA_Priority           = DMA_Priority_High;
  DMA_INIT.DMA_FIFOMode           = DMA_FIFOMode_Disable;         
  DMA_INIT.DMA_FIFOThreshold      = DMA_FIFOThreshold_HalfFull;
  DMA_INIT.DMA_MemoryBurst        = DMA_MemoryBurst_Single;
  DMA_INIT.DMA_PeripheralBurst    = DMA_PeripheralBurst_Single;
  DMA_Init(DMA1_Stream5, &DMA_INIT);

  DMA_Cmd(DMA1_Stream5, ENABLE);
  DAC_Cmd(DAC_Channel_1, ENABLE);
  DAC_DMACmd(DAC_Channel_1, ENABLE);
}