#
# "base" - base directory
# "dirs" - directiry with sources, all source files in this directory added (without recursion)
# "files" - raw list of source files
# "output" - output path prefix

sources = [
{
	"base" : "../../SoundCard/code/Libraries/CMSIS/ST/STM32F4xx/Source/Templates/gcc_ride7",
	"output" : "CMSIS",
	"files" : [
		"startup_stm32f4xx.S"
		]

},
{
	"base" : ".",
	"output" : "base",
	"dirs" : [
		"src"
	]
},
{
	"base" : "../../SoundCard/code/Libraries/STM32F4xx_StdPeriph_Driver/src",
	"output" : "StdPeriph_Driver",
	"files" : [
		"misc.c",
		"stm32f4xx_dac.c",
		"stm32f4xx_dma.c",
		"stm32f4xx_exti.c",
		"stm32f4xx_gpio.c",
		"stm32f4xx_i2c.c",
		"stm32f4xx_rcc.c",
		"stm32f4xx_spi.c",
		"stm32f4xx_syscfg.c",
		"stm32f4xx_tim.c"
		]
},
{
	"base" : "../../SoundCard/code/Libraries/CMSIS/DSP_Lib/Source",
	"output" : "FFT",
	"files" : [
		"CommonTables/arm_common_tables.c",
		"ComplexMathFunctions/arm_cmplx_mag_f32.c",
		"TransformFunctions/arm_cfft_radix4_f32.c",
		"TransformFunctions/arm_cfft_radix4_init_f32.c",
		"TransformFunctions/arm_rfft_init_f32.c",
		"TransformFunctions/arm_rfft_f32.c"
		]
}
]


