#include "main.h"
#include "hw_config.h"
#include "stm32l1xx_tim.h"
#include "delay.h"

void DelayInit()
{
	TIM_TimeBaseInitTypeDef tim_init;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE);

	TIM_Cmd(TIM6, DISABLE);
	TIM_DeInit(TIM6);

	tim_init.TIM_Prescaler = RCC_Clocks.PCLK1_Frequency/1000000-1; //1 us per tick
	tim_init.TIM_CounterMode = TIM_CounterMode_Up;
	tim_init.TIM_Period = 0xFFFF;
	tim_init.TIM_ClockDivision = TIM_CKD_DIV1;

	TIM_TimeBaseInit(TIM6, &tim_init);
	TIM_SetCounter(TIM6, 0);
	TIM_Cmd(TIM6, ENABLE);
}

void DelayUs(uint16_t countUs)
{
	uint16_t start = TIM6->CNT;
	while(TIM6->CNT-start < countUs);
}
