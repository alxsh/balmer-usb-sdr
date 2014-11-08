################################################################################
# Automatically-generated file. Do not edit!
################################################################################


DEPS += \
	output/CMSIS/startup_stm32l1xx_md.d \
	output/base/src/commands.d \
	output/base/src/data_process.d \
	output/base/src/delay.d \
	output/base/src/main.d \
	output/base/src/my_hardware.d \
	output/base/src/spi.d \
	output/base/src/spi_commands.d \
	output/base/src/spi_data_process.d \
	output/base/src/stm32l1xx_it.d \
	output/base/src/syscalls.d \
	output/base/src/system_stm32l1xx.d \
	output/base/src/usb_desc.d \
	output/base/src/usb_endp.d \
	output/base/src/usb_istr.d \
	output/base/src/usb_prop.d \
	output/base/src/usb_pwr.d \
	output/base/src/ili/DefaultFonts.d \
	output/base/src/ili/UTFT.d \
	output/base/src/ili/hw_ili9341.d \
	output/usb/src/otgd_fs_cal.d \
	output/usb/src/otgd_fs_dev.d \
	output/usb/src/otgd_fs_int.d \
	output/usb/src/otgd_fs_pcd.d \
	output/usb/src/usb_core.d \
	output/usb/src/usb_init.d \
	output/usb/src/usb_int.d \
	output/usb/src/usb_mem.d \
	output/usb/src/usb_regs.d \
	output/usb/src/usb_sil.d \
	output/periph/misc.d \
	output/periph/stm32l1xx_dbgmcu.d \
	output/periph/stm32l1xx_exti.d \
	output/periph/stm32l1xx_flash.d \
	output/periph/stm32l1xx_gpio.d \
	output/periph/stm32l1xx_iwdg.d \
	output/periph/stm32l1xx_lcd.d \
	output/periph/stm32l1xx_pwr.d \
	output/periph/stm32l1xx_rcc.d \
	output/periph/stm32l1xx_rtc.d \
	output/periph/stm32l1xx_spi.d \
	output/periph/stm32l1xx_syscfg.d \
	output/periph/stm32l1xx_tim.d \
	output/periph/stm32l1xx_wwdg.d \


OBJS += \
	output/CMSIS/startup_stm32l1xx_md.o \
	output/base/src/commands.o \
	output/base/src/data_process.o \
	output/base/src/delay.o \
	output/base/src/main.o \
	output/base/src/my_hardware.o \
	output/base/src/spi.o \
	output/base/src/spi_commands.o \
	output/base/src/spi_data_process.o \
	output/base/src/stm32l1xx_it.o \
	output/base/src/syscalls.o \
	output/base/src/system_stm32l1xx.o \
	output/base/src/usb_desc.o \
	output/base/src/usb_endp.o \
	output/base/src/usb_istr.o \
	output/base/src/usb_prop.o \
	output/base/src/usb_pwr.o \
	output/base/src/ili/DefaultFonts.o \
	output/base/src/ili/UTFT.o \
	output/base/src/ili/hw_ili9341.o \
	output/usb/src/otgd_fs_cal.o \
	output/usb/src/otgd_fs_dev.o \
	output/usb/src/otgd_fs_int.o \
	output/usb/src/otgd_fs_pcd.o \
	output/usb/src/usb_core.o \
	output/usb/src/usb_init.o \
	output/usb/src/usb_int.o \
	output/usb/src/usb_mem.o \
	output/usb/src/usb_regs.o \
	output/usb/src/usb_sil.o \
	output/periph/misc.o \
	output/periph/stm32l1xx_dbgmcu.o \
	output/periph/stm32l1xx_exti.o \
	output/periph/stm32l1xx_flash.o \
	output/periph/stm32l1xx_gpio.o \
	output/periph/stm32l1xx_iwdg.o \
	output/periph/stm32l1xx_lcd.o \
	output/periph/stm32l1xx_pwr.o \
	output/periph/stm32l1xx_rcc.o \
	output/periph/stm32l1xx_rtc.o \
	output/periph/stm32l1xx_spi.o \
	output/periph/stm32l1xx_syscfg.o \
	output/periph/stm32l1xx_tim.o \
	output/periph/stm32l1xx_wwdg.o \


output/CMSIS/startup_stm32l1xx_md.o: ../code/Libraries/CMSIS/Device/ST/STM32L1xx/Source/Templates/gcc_ride7/startup_stm32l1xx_md.S
	@echo 'Building target: startup_stm32l1xx_md.S'
	@$(CC) $(ASM_FLAGS) -o "$@" "$<"

output/base/src/commands.o: ./src/commands.c
	@echo 'Building target: commands.c'
	@$(CC) $(C_FLAGS) -o "$@" "$<"

output/base/src/data_process.o: ./src/data_process.c
	@echo 'Building target: data_process.c'
	@$(CC) $(C_FLAGS) -o "$@" "$<"

output/base/src/delay.o: ./src/delay.c
	@echo 'Building target: delay.c'
	@$(CC) $(C_FLAGS) -o "$@" "$<"

output/base/src/main.o: ./src/main.c
	@echo 'Building target: main.c'
	@$(CC) $(C_FLAGS) -o "$@" "$<"

output/base/src/my_hardware.o: ./src/my_hardware.c
	@echo 'Building target: my_hardware.c'
	@$(CC) $(C_FLAGS) -o "$@" "$<"

output/base/src/spi.o: ./src/spi.c
	@echo 'Building target: spi.c'
	@$(CC) $(C_FLAGS) -o "$@" "$<"

output/base/src/spi_commands.o: ./src/spi_commands.c
	@echo 'Building target: spi_commands.c'
	@$(CC) $(C_FLAGS) -o "$@" "$<"

output/base/src/spi_data_process.o: ./src/spi_data_process.c
	@echo 'Building target: spi_data_process.c'
	@$(CC) $(C_FLAGS) -o "$@" "$<"

output/base/src/stm32l1xx_it.o: ./src/stm32l1xx_it.c
	@echo 'Building target: stm32l1xx_it.c'
	@$(CC) $(C_FLAGS) -o "$@" "$<"

output/base/src/syscalls.o: ./src/syscalls.c
	@echo 'Building target: syscalls.c'
	@$(CC) $(C_FLAGS) -o "$@" "$<"

output/base/src/system_stm32l1xx.o: ./src/system_stm32l1xx.c
	@echo 'Building target: system_stm32l1xx.c'
	@$(CC) $(C_FLAGS) -o "$@" "$<"

output/base/src/usb_desc.o: ./src/usb_desc.c
	@echo 'Building target: usb_desc.c'
	@$(CC) $(C_FLAGS) -o "$@" "$<"

output/base/src/usb_endp.o: ./src/usb_endp.c
	@echo 'Building target: usb_endp.c'
	@$(CC) $(C_FLAGS) -o "$@" "$<"

output/base/src/usb_istr.o: ./src/usb_istr.c
	@echo 'Building target: usb_istr.c'
	@$(CC) $(C_FLAGS) -o "$@" "$<"

output/base/src/usb_prop.o: ./src/usb_prop.c
	@echo 'Building target: usb_prop.c'
	@$(CC) $(C_FLAGS) -o "$@" "$<"

output/base/src/usb_pwr.o: ./src/usb_pwr.c
	@echo 'Building target: usb_pwr.c'
	@$(CC) $(C_FLAGS) -o "$@" "$<"

output/base/src/ili/DefaultFonts.o: ./src/ili/DefaultFonts.c
	@echo 'Building target: DefaultFonts.c'
	@$(CC) $(C_FLAGS) -o "$@" "$<"

output/base/src/ili/UTFT.o: ./src/ili/UTFT.c
	@echo 'Building target: UTFT.c'
	@$(CC) $(C_FLAGS) -o "$@" "$<"

output/base/src/ili/hw_ili9341.o: ./src/ili/hw_ili9341.c
	@echo 'Building target: hw_ili9341.c'
	@$(CC) $(C_FLAGS) -o "$@" "$<"

output/usb/src/otgd_fs_cal.o: ../code/Libraries/STM32_USB-FS-Device_Driver/src/otgd_fs_cal.c
	@echo 'Building target: otgd_fs_cal.c'
	@$(CC) $(C_FLAGS) -o "$@" "$<"

output/usb/src/otgd_fs_dev.o: ../code/Libraries/STM32_USB-FS-Device_Driver/src/otgd_fs_dev.c
	@echo 'Building target: otgd_fs_dev.c'
	@$(CC) $(C_FLAGS) -o "$@" "$<"

output/usb/src/otgd_fs_int.o: ../code/Libraries/STM32_USB-FS-Device_Driver/src/otgd_fs_int.c
	@echo 'Building target: otgd_fs_int.c'
	@$(CC) $(C_FLAGS) -o "$@" "$<"

output/usb/src/otgd_fs_pcd.o: ../code/Libraries/STM32_USB-FS-Device_Driver/src/otgd_fs_pcd.c
	@echo 'Building target: otgd_fs_pcd.c'
	@$(CC) $(C_FLAGS) -o "$@" "$<"

output/usb/src/usb_core.o: ../code/Libraries/STM32_USB-FS-Device_Driver/src/usb_core.c
	@echo 'Building target: usb_core.c'
	@$(CC) $(C_FLAGS) -o "$@" "$<"

output/usb/src/usb_init.o: ../code/Libraries/STM32_USB-FS-Device_Driver/src/usb_init.c
	@echo 'Building target: usb_init.c'
	@$(CC) $(C_FLAGS) -o "$@" "$<"

output/usb/src/usb_int.o: ../code/Libraries/STM32_USB-FS-Device_Driver/src/usb_int.c
	@echo 'Building target: usb_int.c'
	@$(CC) $(C_FLAGS) -o "$@" "$<"

output/usb/src/usb_mem.o: ../code/Libraries/STM32_USB-FS-Device_Driver/src/usb_mem.c
	@echo 'Building target: usb_mem.c'
	@$(CC) $(C_FLAGS) -o "$@" "$<"

output/usb/src/usb_regs.o: ../code/Libraries/STM32_USB-FS-Device_Driver/src/usb_regs.c
	@echo 'Building target: usb_regs.c'
	@$(CC) $(C_FLAGS) -o "$@" "$<"

output/usb/src/usb_sil.o: ../code/Libraries/STM32_USB-FS-Device_Driver/src/usb_sil.c
	@echo 'Building target: usb_sil.c'
	@$(CC) $(C_FLAGS) -o "$@" "$<"

output/periph/misc.o: ../code/Libraries/STM32L1xx_StdPeriph_Driver/src/misc.c
	@echo 'Building target: misc.c'
	@$(CC) $(C_FLAGS) -o "$@" "$<"

output/periph/stm32l1xx_dbgmcu.o: ../code/Libraries/STM32L1xx_StdPeriph_Driver/src/stm32l1xx_dbgmcu.c
	@echo 'Building target: stm32l1xx_dbgmcu.c'
	@$(CC) $(C_FLAGS) -o "$@" "$<"

output/periph/stm32l1xx_exti.o: ../code/Libraries/STM32L1xx_StdPeriph_Driver/src/stm32l1xx_exti.c
	@echo 'Building target: stm32l1xx_exti.c'
	@$(CC) $(C_FLAGS) -o "$@" "$<"

output/periph/stm32l1xx_flash.o: ../code/Libraries/STM32L1xx_StdPeriph_Driver/src/stm32l1xx_flash.c
	@echo 'Building target: stm32l1xx_flash.c'
	@$(CC) $(C_FLAGS) -o "$@" "$<"

output/periph/stm32l1xx_gpio.o: ../code/Libraries/STM32L1xx_StdPeriph_Driver/src/stm32l1xx_gpio.c
	@echo 'Building target: stm32l1xx_gpio.c'
	@$(CC) $(C_FLAGS) -o "$@" "$<"

output/periph/stm32l1xx_iwdg.o: ../code/Libraries/STM32L1xx_StdPeriph_Driver/src/stm32l1xx_iwdg.c
	@echo 'Building target: stm32l1xx_iwdg.c'
	@$(CC) $(C_FLAGS) -o "$@" "$<"

output/periph/stm32l1xx_lcd.o: ../code/Libraries/STM32L1xx_StdPeriph_Driver/src/stm32l1xx_lcd.c
	@echo 'Building target: stm32l1xx_lcd.c'
	@$(CC) $(C_FLAGS) -o "$@" "$<"

output/periph/stm32l1xx_pwr.o: ../code/Libraries/STM32L1xx_StdPeriph_Driver/src/stm32l1xx_pwr.c
	@echo 'Building target: stm32l1xx_pwr.c'
	@$(CC) $(C_FLAGS) -o "$@" "$<"

output/periph/stm32l1xx_rcc.o: ../code/Libraries/STM32L1xx_StdPeriph_Driver/src/stm32l1xx_rcc.c
	@echo 'Building target: stm32l1xx_rcc.c'
	@$(CC) $(C_FLAGS) -o "$@" "$<"

output/periph/stm32l1xx_rtc.o: ../code/Libraries/STM32L1xx_StdPeriph_Driver/src/stm32l1xx_rtc.c
	@echo 'Building target: stm32l1xx_rtc.c'
	@$(CC) $(C_FLAGS) -o "$@" "$<"

output/periph/stm32l1xx_spi.o: ../code/Libraries/STM32L1xx_StdPeriph_Driver/src/stm32l1xx_spi.c
	@echo 'Building target: stm32l1xx_spi.c'
	@$(CC) $(C_FLAGS) -o "$@" "$<"

output/periph/stm32l1xx_syscfg.o: ../code/Libraries/STM32L1xx_StdPeriph_Driver/src/stm32l1xx_syscfg.c
	@echo 'Building target: stm32l1xx_syscfg.c'
	@$(CC) $(C_FLAGS) -o "$@" "$<"

output/periph/stm32l1xx_tim.o: ../code/Libraries/STM32L1xx_StdPeriph_Driver/src/stm32l1xx_tim.c
	@echo 'Building target: stm32l1xx_tim.c'
	@$(CC) $(C_FLAGS) -o "$@" "$<"

output/periph/stm32l1xx_wwdg.o: ../code/Libraries/STM32L1xx_StdPeriph_Driver/src/stm32l1xx_wwdg.c
	@echo 'Building target: stm32l1xx_wwdg.c'
	@$(CC) $(C_FLAGS) -o "$@" "$<"



