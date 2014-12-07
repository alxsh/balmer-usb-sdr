#include "main.h"
#include "hw_config.h"
#include "usb_lib.h"
#include "usb_pwr.h"
#include "command.h"
#include "delay.h"
#include "dds.h"

#include "ili/hw_ili9341.h"
#include "ili/UTFT.h"

#include "data_process.h"
#include "spi_data_process.h"
#include "spi.h"
#include "../../4code/inc/spi_commands.h"
#include "waterfall.h"


RCC_ClocksTypeDef RCC_Clocks;

extern __IO uint32_t packet_sent;
extern __IO uint32_t packet_receive;
extern __IO uint8_t Receive_Buffer[64];
extern uint32_t Receive_length;

extern uint16_t g_spi_sended;

extern uint8_t last_command;
extern uint8_t last_receive_length;
extern uint32_t last_receive_data;

bool side_band_changed = false;
uint8_t upper_side_band = 1;

void printCmd();

/*******************************************************************************/
                                  
int main(void)
{ 

    RCC_GetClocksFreq(&RCC_Clocks);

    /* Configure SysTick IRQ and SysTick Timer to generate interrupts */
    SysTick_Config(RCC_Clocks.HCLK_Frequency / 500);

    DelayInit();

    SpiInit();

    UsbInitClockAndSystem();

    HwLcdInit();
    HwLcdPinLed(1);

    //UTFT_InitLCD(UTFT_LANDSCAPE);
    UTFT_InitLCD(UTFT_PORTRAIT);

    DdsInit();

    UTFT_setBackColor(0, 0, 0);
    UTFT_clrScr();

    WaterfallInit();

    UTFT_setColor(0, 255, 0);
    UTFT_setBackColor(0, 0, 0);

    UTFT_setFont(BigFont);
    //UTFT_verticalScrollDefinition(0, 320, 0);
    UTFT_print("SDR!", UTFT_CENTER, 0, 0);

    DdsSetFreq(2000000);

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

        WaterfallDraw();
        printCmd();
        
        /*
        i++;
        UTFT_setFont(SevenSegNumFont);
        UTFT_setColor(0, 128, 255);
        UTFT_printNumI(i, 40, 190, 0, ' ');
        UTFT_setColor(255, 255, 0);
        UTFT_printNumI(i*3, 40, 240, 0, ' ');
        */
        DelayMs(100);

        if(side_band_changed)
        {
          side_band_changed = false;
          SpiAdd8(upper_side_band);
          SpiSendCommand(SCOMMAND_SIDE_BAND);
        } else
        {
          SpiSendCommand(SCOMMAND_SOUND_BUF_DELTA);
        }
    }
}

void OnSetFreq(uint32_t freq)
{
    UTFT_setFont(BigFont);
    int y=7;
    UTFT_setColor(255, 255, 255);
    UTFT_printNumI(freq/1000, 16*2, 16*y, 5, ' ');
    UTFT_print("KHz", 16*8, 16*y, 0);
    DdsSetFreq(freq*2);
}

void OnSideBand(uint8_t usb)
{
  side_band_changed = true;
  upper_side_band = usb;
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
