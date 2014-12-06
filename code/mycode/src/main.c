#include "main.h"
#include "hw_config.h"
#include "usb_lib.h"
#include "usb_pwr.h"
#include "command.h"
#include "delay.h"
#include "dds.h"
#include "data_process.h"

RCC_ClocksTypeDef RCC_Clocks;

extern __IO uint32_t packet_sent;
extern __IO uint32_t packet_receive;
extern __IO uint8_t Receive_Buffer[64];
extern uint32_t Receive_length;

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
    if (bDeviceState == CONFIGURED)
    {
      CDC_Receive_DATA();
      //Check to see if we have data yet
      if (Receive_length  != 0)
      {
        if (packet_sent == 1)
        {
          if(Receive_length>0)
          {
            DataReceive((uint8_t*)Receive_Buffer, Receive_length);
          }
        }
        Receive_length = 0;
      }
    }
  }

}

void OnSetFreq(uint32_t freq)
{
    DdsSetFreq(freq*2);
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
