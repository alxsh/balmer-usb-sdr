#ifndef __HW_CONFIG_H
#define __HW_CONFIG_H

/* Includes ------------------------------------------------------------------*/
#include "usb_type.h"

/* Exported functions ------------------------------------------------------- */
void UsbInitClockAndSystem(void);
void Enter_LowPowerMode(void);
void Leave_LowPowerMode(void);
void USB_Cable_Config (FunctionalState NewState);

void Get_SerialNum(void);


#endif  /*__HW_CONFIG_H*/
