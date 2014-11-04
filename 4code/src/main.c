#include "main.h"
#include "dac.h"
#include "delay.h"
#include "spi.h"

RCC_ClocksTypeDef RCC_Clocks;

int main(void)
{  
  /* SysTick end of count event each 1ms */
  RCC_GetClocksFreq(&RCC_Clocks);
  SysTick_Config(RCC_Clocks.HCLK_Frequency / 1000);

  DelayInit();
  DelayMs(100);

  SpiInit();

  DacInit();
  //DacSetFrequency(1000);
  //DacSetPeriod(48, 2000);
  DacSetPeriod(48, 600);
  DacStart();

  while (1)
  {
  }

  DelayInit();

  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
  GPIO_InitTypeDef gpio_A; 
  gpio_A.GPIO_Pin  = GPIO_Pin_4;
  gpio_A.GPIO_Mode = GPIO_Mode_OUT;
  gpio_A.GPIO_PuPd = GPIO_PuPd_NOPULL;
  gpio_A.GPIO_Speed = GPIO_Speed_25MHz;
  gpio_A.GPIO_OType = GPIO_OType_PP;
  GPIO_Init(GPIOA, &gpio_A);


  while (1)
  {
    GPIO_SetBits(GPIOA, GPIO_Pin_4);
    //DelayUs(1000);
    DelayMs(1);
    GPIO_ResetBits(GPIOA, GPIO_Pin_4);
    //DelayUs(1000);
    DelayMs(1);
  }
}

#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *   where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

  
/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
