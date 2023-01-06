################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include USER/subdir.mk
-include QRCODE/subdir.mk
-include MCU/vector_table/subdir.mk
-include MCU/uart/subdir.mk
-include MCU/rtc/subdir.mk
-include MCU/pwm/subdir.mk
-include MCU/pit/subdir.mk
-include MCU/iostring/subdir.mk
-include MCU/flash/subdir.mk
-include MCU/dma/subdir.mk
-include MCU/delay/subdir.mk
-include Function/bsp_user/subdir.mk
-include Function/bsp/subdir.mk
-include Fixed/w25qxx/subdir.mk
-include Fixed/tp/subdir.mk
-include Fixed/dctouch/subdir.mk
-include Fixed/data/subdir.mk
-include Fixed/SinCosTable/subdir.mk
-include Display/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: LT268A_TFT_public_demo_8bits_20211026_LIB-KLL.elf

# Tool invocations
LT268A_TFT_public_demo_8bits_20211026_LIB-KLL.elf: $(OBJS) $(USER_OBJS) ../linkmap
	@echo 'Building target: $@'
	@echo 'Invoking: Cross GCC Linker'
	mcore-elf-ld -EL --gc-sections -L"D:\CCore_IDE/tool-chain/ccore-elf/mcore-elf/lib/c0_div" -L"D:\E Battery Display Screen\project_2\LT268A_TFT_public_demo_8bits_20211026_LIB-KLL\Levetoplib" -L"D:\CCore_IDE/tool-chain/ccore-elf/lib/gcc/mcore-elf/4.6.0/c0_div" -e __start -N -t -warn-common -Map LT268A_TFT_public_demo_8bits_20211026_LIB-KLL.map -T../linkmap -o "LT268A_TFT_public_demo_8bits_20211026_LIB-KLL.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '
	$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	-$(RM) $(C++_DEPS)$(OBJS)$(C_DEPS)$(CC_DEPS)$(CPP_DEPS)$(EXECUTABLES)$(CXX_DEPS)$(C_UPPER_DEPS) LT268A_TFT_public_demo_8bits_20211026_LIB-KLL.elf *.bin *.s *.obj *.map *.elf *.a
	-@echo ' '

post-build:
	-mcore-elf-objcopy  -O binary LT268A_TFT_public_demo_8bits_20211026_LIB-KLL.elf LT268A_TFT_public_demo_8bits_20211026_LIB-KLL.bin& mcore-elf-objdump -D LT268A_TFT_public_demo_8bits_20211026_LIB-KLL.elf > LT268A_TFT_public_demo_8bits_20211026_LIB-KLL.obj& mcore-elf-size LT268A_TFT_public_demo_8bits_20211026_LIB-KLL.elf
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY: post-build

-include ../makefile.targets
