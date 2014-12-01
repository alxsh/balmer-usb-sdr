#include "dds.h"
#include "delay.h"

#define DDS_GPIO GPIOA
#define DDS_RESET GPIO_Pin_0
#define DDS_DATA GPIO_Pin_1 //AD7
#define DDS_FQ_UD GPIO_Pin_2
#define DDS_W_CLK GPIO_Pin_3

#define DELAY_COUNT 1

void DdsInit()
{
	GPIO_InitTypeDef GPIO_InitStruct;		
	// enable clock for used IO pins
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
	/*
	PD6 - CS_I
	PD7 - CS_A
	*/
	GPIO_InitStruct.GPIO_Pin = DDS_RESET | DDS_DATA | DDS_FQ_UD | DDS_W_CLK;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(DDS_GPIO, &GPIO_InitStruct);
	
	//GPIO_SetBits(DDS_GPIO, GPIO_Pin_6);
	GPIO_SetBits(DDS_GPIO, DDS_RESET);
	GPIO_ResetBits(DDS_GPIO, DDS_DATA);
	GPIO_ResetBits(DDS_GPIO, DDS_FQ_UD);
	GPIO_ResetBits(DDS_GPIO, DDS_W_CLK);

	DelayUs(20);
	GPIO_ResetBits(DDS_GPIO, DDS_RESET);
}

static void DdsByte(uint8_t data)
{
	uint8_t i;
	for(i=0; i<8; i++)
	{
		uint8_t bit = (data >> i) & 1;
		GPIO_WriteBit(DDS_GPIO, DDS_DATA, bit);
		DelayUs(DELAY_COUNT);
		GPIO_SetBits(DDS_GPIO, DDS_W_CLK);
		DelayUs(DELAY_COUNT);
		GPIO_ResetBits(DDS_GPIO, DDS_W_CLK);
	}
}

void DdsSetWord(uint32_t data)
{
	GPIO_SetBits(DDS_GPIO, DDS_W_CLK);
	DelayUs(DELAY_COUNT);
	GPIO_ResetBits(DDS_GPIO, DDS_W_CLK);
	DelayUs(DELAY_COUNT);
	GPIO_SetBits(DDS_GPIO, DDS_FQ_UD);
	DelayUs(DELAY_COUNT);
	GPIO_ResetBits(DDS_GPIO, DDS_FQ_UD);

	DdsByte((uint8_t)data);
	DdsByte((uint8_t)(data>>8));
	DdsByte((uint8_t)(data>>16));
	DdsByte((uint8_t)(data>>24));
	DdsByte(0); //control word

	GPIO_SetBits(DDS_GPIO, DDS_FQ_UD);
	DelayUs(DELAY_COUNT);
	GPIO_ResetBits(DDS_GPIO, DDS_FQ_UD);
}

void DdsSetFreq(uint32_t freq)
{
	uint64_t CLKIN = 125000000; //125 МГц
	uint32_t data = (uint32_t)((((uint64_t)freq)<<32)/CLKIN);
	DdsSetWord(data);
}