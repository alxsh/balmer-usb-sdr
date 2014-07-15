#include "main.h"
#include "hw_config.h"
#include "usb_lib.h"
#include "usb_pwr.h"
#include "command.h"
#include "delay.h"
#include "dds.h"

RCC_ClocksTypeDef RCC_Clocks;

/*******************************************************************************/
                                  
int main(void)
{ 

  RCC_GetClocksFreq(&RCC_Clocks);

  /* Configure SysTick IRQ and SysTick Timer to generate interrupts */
  SysTick_Config(RCC_Clocks.HCLK_Frequency / 500);

  DelayInit();
  DdsInit();

  UsbInitClockAndSystem();
  while(1)
  {
      Delay5us(10);
  }

}

#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
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
