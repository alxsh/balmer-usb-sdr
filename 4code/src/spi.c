#include "delay.h"
#include "spi.h"
/*
	EXTI Slave 			 - PB12
	SPI2_SCK             - PB13 34 *
	SPI2_MISO            - PB14 35 *
	SPI2_MOSI            - PB15 36 *
*/

void SpiInit()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	SPI_InitTypeDef SPI_InitStructure;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_25MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_25MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	GPIO_PinAFConfig(GPIOB, GPIO_PinSource13, GPIO_AF_SPI2);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource14, GPIO_AF_SPI2);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource15, GPIO_AF_SPI2);
	 
	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_16b;
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_4;
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
	SPI_InitStructure.SPI_Mode = SPI_Mode_Slave;
	SPI_InitStructure.SPI_CRCPolynomial = 15;
	SPI_Init(SPI2, &SPI_InitStructure);

	SPI_I2S_ITConfig(SPI2, SPI_I2S_IT_RXNE,ENABLE);
	SPI_Cmd(SPI2, ENABLE);
	NVIC_EnableIRQ(SPI2_IRQn);

	SPI2->DR = 0x4000;
}

extern int g_sound_min;
extern int g_sound_max;


void SpiOnReceive()
{
	if (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE)==SET) {
		volatile uint16_t data = SPI2->DR; //Читаем то что пришло

		if(g_sound_min <= g_sound_max)
		{
			data = g_sound_max-g_sound_min;
			g_sound_min = 1<<24;
			g_sound_max = -(1<<24);
		}

		SPI2->DR = data;
	}
}

void SpiComplete()
{
	GPIO_SetBits(GPIOB, GPIO_Pin_12);
	DelayUs(2);
	GPIO_ResetBits(GPIOB, GPIO_Pin_12);
}
