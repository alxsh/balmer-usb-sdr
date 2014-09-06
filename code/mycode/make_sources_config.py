#
# "base" - base directory
# "dirs" - directiry with sources, all source files in this directory added (without recursion)
# "files" - raw list of source files
# "output" - output path prefix

sources = [
{
	"base" : "../Libraries/CMSIS/Device/ST/STM32L1xx/Source/Templates/gcc_ride7",
	"output" : "CMSIS",
	"files" : [
		"startup_stm32l1xx_md.S"
		]

},
{
	"base" : ".",
	"output" : "base",
	"dirs" : [
		"src",
		"../Libraries/STM32_USB-FS-Device_Driver/src"
		]
},
{
	"base" : "../Libraries/STM32L1xx_StdPeriph_Driver/src",
	"output" : "periph",
	"files" : [
		"misc.c",
		#"stm32l1xx_adc.c",
		#"stm32l1xx_aes.c",
		#"stm32l1xx_aes_util.c",
		#"stm32l1xx_comp.c",
		#"stm32l1xx_crc.c",
		#"stm32l1xx_dac.c",
		"stm32l1xx_dbgmcu.c",
		#"stm32l1xx_dma.c",
		"stm32l1xx_exti.c",
		"stm32l1xx_flash.c",
		#"stm32l1xx_flash_ramfunc.c",
		#"stm32l1xx_fsmc.c",
		"stm32l1xx_gpio.c",
		#"stm32l1xx_i2c.c",
		"stm32l1xx_iwdg.c",
		"stm32l1xx_lcd.c",
		#"stm32l1xx_opamp.c",
		"stm32l1xx_pwr.c",
		"stm32l1xx_rcc.c",
		"stm32l1xx_rtc.c",
		#"stm32l1xx_sdio.c",
		#"stm32l1xx_spi.c",
		"stm32l1xx_syscfg.c",
		"stm32l1xx_tim.c",
		#"stm32l1xx_usart.c",
		"stm32l1xx_wwdg.c"
	]

}
]


