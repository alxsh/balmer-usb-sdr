RM := rm -rf
TC=arm-none-eabi
CC=$(TC)-gcc
LD=$(TC)-ld -v
OBJCOPY=$(TC)-objcopy
AR=$(TC)-ar
GDB=$(TC)-gdb


C_INCLIDES= -Iinc
C_INCLIDES+= -I../code/Libraries/STM32L1xx_StdPeriph_Driver/inc
C_INCLIDES+= -I../code/Libraries/CMSIS/Include
C_INCLIDES+= -I../code/Libraries/CMSIS/Device/ST/STM32L1xx/Include
C_INCLIDES+= -I../code/Libraries/STM32_USB-FS-Device_Driver/inc
C_INCLIDES+= -includeinc/stm32l1xx_conf.h

ifeq ($(MAKECMDGOALS),debug)
C_DEFINES= -DDEBUG -DUSE_FULL_ASSERT
C_FLAGS= -O0 -g3
endif

ifeq ($(MAKECMDGOALS),release)
C_DEFINES= -DNDEBUG
C_FLAGS= -Os
endif

C_DEFINES+= -DSTM32L1XX_MD
C_DEFINES+= -DHSE_VALUE=8000000
C_DEFINES+= -std=c99

#balmer compiler flags to remove unused functions
C_FLAGS += -fdata-sections -ffunction-sections
C_FLAGS+= -Wall -c -mthumb -mcpu=cortex-m3 -mfix-cortex-m3-ldrd -MMD $(C_INCLIDES) $(C_DEFINES) 

C_FLAGS+= -funsigned-char


LDFLAGS = -nostartfiles -mthumb -mcpu=cortex-m3 -T "stm32_flash_md.ld" -mfix-cortex-m3-ldrd  -Wl,-Map=linker.map -Wl,-cref  -Wl,--gc-sections 
ASM_FLAGS = -x assembler-with-cpp -c -mthumb -mcpu=cortex-m3


TARGET=output/program

# All of the sources participating in the build are defined here
include sources.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(DEPS)),)
-include $(DEPS)
endif
endif

# All Target
#all: executable

release: executable

debug: executable

# Tool invocations
executable: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: GCC C++ Linker'
	@$(TC)-g++ $(LDFLAGS) -o "$(TARGET)_$(MAKECMDGOALS)" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo 'Create Binary'
	$(OBJCOPY) -S  -O binary  "$(TARGET)_$(MAKECMDGOALS)" "$(TARGET)_$(MAKECMDGOALS).bin"
	@echo ' '

# Other Targets
clean:
	-@echo 'Clean files'	
	-@$(RM) $(OBJS)$(DEPS) $(TARGET)
	-@echo ' '

flashd:
	python /balmer/radio/stm32/tools/stm32_flash.py "${CURDIR}/$(TARGET)_debug.bin"

flashr:
	python /balmer/radio/stm32/tools/stm32_flash.py "${CURDIR}/$(TARGET)_release.bin"

.PHONY: all clean dependents
