#include "main.h"
#include "hw_config.h"
#include "usb_lib.h"
#include "usb_pwr.h"
#include "command.h"
#include "delay.h"

#include "ili/hw_ili9341.h"
#include "ili/UTFT.h"

#include "data_process.h"
#include "spi.h"


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

    UsbInitClockAndSystem();

    HwLcdInit();
    HwLcdPinLed(1);

    //UTFT_InitLCD(UTFT_LANDSCAPE);
    UTFT_InitLCD(UTFT_PORTRAIT);

    UTFT_setBackColor(0, 0, 0);
    UTFT_clrScr();

    UTFT_setColor(0, 255, 0);
    UTFT_setBackColor(0, 0, 0);

    UTFT_setFont(BigFont);
    UTFT_print("SDR!", UTFT_CENTER, 16, 0);

    SpiInit();

    UTFT_print("Spi Init", UTFT_CENTER, 32, 0);

    int i = 0;

    while(1)
    {
        UTFT_setColor(0, 128, 255);
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
                DataReceive((uint8_t*)Receive_Buffer, Receive_length);;
              }
            }
            Receive_length = 0;
          }
        }

        i++;
        UTFT_setFont(SevenSegNumFont);
        UTFT_setColor(0, 128, 255);
        UTFT_printNumI(i, 40, 190, 0, ' ');
        UTFT_setColor(255, 255, 0);
        UTFT_printNumI(i*3, 40, 240, 0, ' ');
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
