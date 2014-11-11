################################################################################
# Automatically-generated file. Do not edit!
################################################################################


DEPS += \
	output/CMSIS/startup_stm32f4xx.d \
	output/base/src/cs4272.d \
	output/base/src/dac.d \
	output/base/src/delay.d \
	output/base/src/main.d \
	output/base/src/process_sound.d \
	output/base/src/spi.d \
	output/base/src/spi_commands.d \
	output/base/src/spi_data_process.d \
	output/base/src/stm32f4xx_it.d \
	output/base/src/system_stm32f4xx.d \
	output/StdPeriph_Driver/misc.d \
	output/StdPeriph_Driver/stm32f4xx_dac.d \
	output/StdPeriph_Driver/stm32f4xx_dma.d \
	output/StdPeriph_Driver/stm32f4xx_exti.d \
	output/StdPeriph_Driver/stm32f4xx_gpio.d \
	output/StdPeriph_Driver/stm32f4xx_i2c.d \
	output/StdPeriph_Driver/stm32f4xx_rcc.d \
	output/StdPeriph_Driver/stm32f4xx_spi.d \
	output/StdPeriph_Driver/stm32f4xx_syscfg.d \
	output/StdPeriph_Driver/stm32f4xx_tim.d \
	output/FFT/../CommonTables/arm_common_tables.d \
	output/FFT/arm_cfft_radix4_f32.d \
	output/FFT/arm_cfft_radix4_init_f32.d \
	output/FFT/arm_rfft_init_f32.d \
	output/FFT/arm_rfft_f32.d \


OBJS += \
	output/CMSIS/startup_stm32f4xx.o \
	output/base/src/cs4272.o \
	output/base/src/dac.o \
	output/base/src/delay.o \
	output/base/src/main.o \
	output/base/src/process_sound.o \
	output/base/src/spi.o \
	output/base/src/spi_commands.o \
	output/base/src/spi_data_process.o \
	output/base/src/stm32f4xx_it.o \
	output/base/src/system_stm32f4xx.o \
	output/StdPeriph_Driver/misc.o \
	output/StdPeriph_Driver/stm32f4xx_dac.o \
	output/StdPeriph_Driver/stm32f4xx_dma.o \
	output/StdPeriph_Driver/stm32f4xx_exti.o \
	output/StdPeriph_Driver/stm32f4xx_gpio.o \
	output/StdPeriph_Driver/stm32f4xx_i2c.o \
	output/StdPeriph_Driver/stm32f4xx_rcc.o \
	output/StdPeriph_Driver/stm32f4xx_spi.o \
	output/StdPeriph_Driver/stm32f4xx_syscfg.o \
	output/StdPeriph_Driver/stm32f4xx_tim.o \
	output/FFT/../CommonTables/arm_common_tables.o \
	output/FFT/arm_cfft_radix4_f32.o \
	output/FFT/arm_cfft_radix4_init_f32.o \
	output/FFT/arm_rfft_init_f32.o \
	output/FFT/arm_rfft_f32.o \


output/CMSIS/startup_stm32f4xx.o: ../../SoundCard/code/Libraries/CMSIS/ST/STM32F4xx/Source/Templates/gcc_ride7/startup_stm32f4xx.S
	@echo 'Building target: startup_stm32f4xx.S'
	@$(CC) $(ASM_FLAGS) -o "$@" "$<"

output/base/src/cs4272.o: ./src/cs4272.c
	@echo 'Building target: cs4272.c'
	@$(CC) $(C_FLAGS) -o "$@" "$<"

output/base/src/dac.o: ./src/dac.c
	@echo 'Building target: dac.c'
	@$(CC) $(C_FLAGS) -o "$@" "$<"

output/base/src/delay.o: ./src/delay.c
	@echo 'Building target: delay.c'
	@$(CC) $(C_FLAGS) -o "$@" "$<"

output/base/src/main.o: ./src/main.c
	@echo 'Building target: main.c'
	@$(CC) $(C_FLAGS) -o "$@" "$<"

output/base/src/process_sound.o: ./src/process_sound.c
	@echo 'Building target: process_sound.c'
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

output/base/src/stm32f4xx_it.o: ./src/stm32f4xx_it.c
	@echo 'Building target: stm32f4xx_it.c'
	@$(CC) $(C_FLAGS) -o "$@" "$<"

output/base/src/system_stm32f4xx.o: ./src/system_stm32f4xx.c
	@echo 'Building target: system_stm32f4xx.c'
	@$(CC) $(C_FLAGS) -o "$@" "$<"

output/StdPeriph_Driver/misc.o: ../../SoundCard/code/Libraries/STM32F4xx_StdPeriph_Driver/src/misc.c
	@echo 'Building target: misc.c'
	@$(CC) $(C_FLAGS) -o "$@" "$<"

output/StdPeriph_Driver/stm32f4xx_dac.o: ../../SoundCard/code/Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_dac.c
	@echo 'Building target: stm32f4xx_dac.c'
	@$(CC) $(C_FLAGS) -o "$@" "$<"

output/StdPeriph_Driver/stm32f4xx_dma.o: ../../SoundCard/code/Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_dma.c
	@echo 'Building target: stm32f4xx_dma.c'
	@$(CC) $(C_FLAGS) -o "$@" "$<"

output/StdPeriph_Driver/stm32f4xx_exti.o: ../../SoundCard/code/Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_exti.c
	@echo 'Building target: stm32f4xx_exti.c'
	@$(CC) $(C_FLAGS) -o "$@" "$<"

output/StdPeriph_Driver/stm32f4xx_gpio.o: ../../SoundCard/code/Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_gpio.c
	@echo 'Building target: stm32f4xx_gpio.c'
	@$(CC) $(C_FLAGS) -o "$@" "$<"

output/StdPeriph_Driver/stm32f4xx_i2c.o: ../../SoundCard/code/Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_i2c.c
	@echo 'Building target: stm32f4xx_i2c.c'
	@$(CC) $(C_FLAGS) -o "$@" "$<"

output/StdPeriph_Driver/stm32f4xx_rcc.o: ../../SoundCard/code/Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_rcc.c
	@echo 'Building target: stm32f4xx_rcc.c'
	@$(CC) $(C_FLAGS) -o "$@" "$<"

output/StdPeriph_Driver/stm32f4xx_spi.o: ../../SoundCard/code/Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_spi.c
	@echo 'Building target: stm32f4xx_spi.c'
	@$(CC) $(C_FLAGS) -o "$@" "$<"

output/StdPeriph_Driver/stm32f4xx_syscfg.o: ../../SoundCard/code/Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_syscfg.c
	@echo 'Building target: stm32f4xx_syscfg.c'
	@$(CC) $(C_FLAGS) -o "$@" "$<"

output/StdPeriph_Driver/stm32f4xx_tim.o: ../../SoundCard/code/Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_tim.c
	@echo 'Building target: stm32f4xx_tim.c'
	@$(CC) $(C_FLAGS) -o "$@" "$<"

output/FFT/../CommonTables/arm_common_tables.o: ../../SoundCard/code/Libraries/CMSIS/DSP_Lib/Source/TransformFunctions/../CommonTables/arm_common_tables.c
	@echo 'Building target: arm_common_tables.c'
	@$(CC) $(C_FLAGS) -o "$@" "$<"

output/FFT/arm_cfft_radix4_f32.o: ../../SoundCard/code/Libraries/CMSIS/DSP_Lib/Source/TransformFunctions/arm_cfft_radix4_f32.c
	@echo 'Building target: arm_cfft_radix4_f32.c'
	@$(CC) $(C_FLAGS) -o "$@" "$<"

output/FFT/arm_cfft_radix4_init_f32.o: ../../SoundCard/code/Libraries/CMSIS/DSP_Lib/Source/TransformFunctions/arm_cfft_radix4_init_f32.c
	@echo 'Building target: arm_cfft_radix4_init_f32.c'
	@$(CC) $(C_FLAGS) -o "$@" "$<"

output/FFT/arm_rfft_init_f32.o: ../../SoundCard/code/Libraries/CMSIS/DSP_Lib/Source/TransformFunctions/arm_rfft_init_f32.c
	@echo 'Building target: arm_rfft_init_f32.c'
	@$(CC) $(C_FLAGS) -o "$@" "$<"

output/FFT/arm_rfft_f32.o: ../../SoundCard/code/Libraries/CMSIS/DSP_Lib/Source/TransformFunctions/arm_rfft_f32.c
	@echo 'Building target: arm_rfft_f32.c'
	@$(CC) $(C_FLAGS) -o "$@" "$<"



