
#include "delay.h"
#include "spi.h"
#include "spi_data_process.h"

uint8_t g_slave_ready = 0;

/*
	Use
	EXTI Slave - PA4
	SPI1_SCK   - PA5 21 *
	SPI1_MISO  - PA6 22 *
	SPI1_MOSI  - PA7 23 *

	Пускай пока скорость будет маленькая 125 КГц примерно
*/
void SpiInit()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	SPI_InitTypeDef SPI_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE); //For exti

	//SPI lines
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_40MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	GPIO_PinAFConfig(GPIOA, GPIO_PinSource5, GPIO_AF_SPI1);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource6, GPIO_AF_SPI1);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource7, GPIO_AF_SPI1);

	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_16b;
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2;//SPI_BaudRatePrescaler_256;
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
	SPI_InitStructure.SPI_CRCPolynomial = 15;
	SPI_Init(SPI1, &SPI_InitStructure);
	SPI_I2S_ITConfig(SPI1,SPI_I2S_IT_RXNE,ENABLE);
	SPI_NSSInternalSoftwareConfig(SPI1, SPI_NSSInternalSoft_Set);
	//SPI_SSOutputCmd(SPI1, ENABLE);
	SPI_Cmd(SPI1, ENABLE);
	NVIC_EnableIRQ(SPI1_IRQn);

	//SPI_I2S_SendData(SPI1, 1234);

	//Init EXTI

	//EXTI line
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;//GPIO_Speed_40MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, EXTI_PinSource4);

	EXTI_InitTypeDef exti;
	exti.EXTI_Line = EXTI_Line4;
	exti.EXTI_Mode = EXTI_Mode_Interrupt;
	exti.EXTI_Trigger = EXTI_Trigger_Rising;
	exti.EXTI_LineCmd = ENABLE;
	EXTI_Init(&exti);

	NVIC_EnableIRQ(EXTI4_IRQn);
}

void SpiSend(uint16_t data)
{
	while( SPI1->SR & SPI_I2S_FLAG_BSY );
	SPI1->DR = data;
}

void SpiOnReceive()
{
	if (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE)==SET) {
		volatile uint16_t data = SPI1->DR; //Читаем то что пришло
		SpiDataReceive(data);
		//SPI1->DR = 1234;
	}
}

void SpiSlaveEvent()
{
	g_slave_ready++;
	SpiSlaveReady();
}
