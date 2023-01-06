################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Levetoplib/levetop.c 

OBJS += \
./Levetoplib/levetop.o 

C_DEPS += \
./Levetoplib/levetop.d 


# Each subdirectory must supply rules for building sources it contributes
Levetoplib/%.o: ../Levetoplib/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	mcore-elf-gcc -I"D:\C0_New_workspace\LT268A_demo_8bits_20211026\Display" -I"D:\C0_New_workspace\LT268A_demo_8bits_20211026\MCU\vector_table" -I"D:\C0_New_workspace\LT268A_demo_8bits_20211026\MCU\uart" -I"D:\C0_New_workspace\LT268A_demo_8bits_20211026\MCU\dma" -I"D:\C0_New_workspace\LT268A_demo_8bits_20211026\MCU\sys" -I"D:\C0_New_workspace\LT268A_demo_8bits_20211026\MCU\rtc" -I"D:\C0_New_workspace\LT268A_demo_8bits_20211026\MCU\pwm" -I"D:\C0_New_workspace\LT268A_demo_8bits_20211026\MCU\pit" -I"D:\C0_New_workspace\LT268A_demo_8bits_20211026\MCU\iostring" -I"D:\C0_New_workspace\LT268A_demo_8bits_20211026\MCU\flash" -I"D:\C0_New_workspace\LT268A_demo_8bits_20211026\MCU\delay" -I"D:\C0_New_workspace\LT268A_demo_8bits_20211026\Levetoplib" -I"D:\C0_New_workspace\LT268A_demo_8bits_20211026\Function\bsp" -I"D:\C0_New_workspace\LT268A_demo_8bits_20211026\Function\bsp_user" -I"D:\C0_New_workspace\LT268A_demo_8bits_20211026" -I"D:\C0_New_workspace\LT268A_demo_8bits_20211026\Fixed\w25qxx" -I"D:\C0_New_workspace\LT268A_demo_8bits_20211026\Fixed\type" -I"D:\C0_New_workspace\LT268A_demo_8bits_20211026\Fixed\tp" -I"D:\C0_New_workspace\LT268A_demo_8bits_20211026\Fixed\SinCosTable" -I"D:\C0_New_workspace\LT268A_demo_8bits_20211026\Fixed\Module" -I"D:\C0_New_workspace\LT268A_demo_8bits_20211026\Fixed\dctouch" -I"D:\C0_New_workspace\LT268A_demo_8bits_20211026\Fixed\data" -I"D:\C0_New_workspace\LT268A_demo_8bits_20211026\QRCODE" -I"D:\CCore_IDE/tool-chain/ccore-elf/lib/gcc/mcore-elf/4.6.0/include" -I"D:\CCore_IDE/tool-chain/ccore-elf/mcore-elf/include" -O1 -fno-common -ffunction-sections -g -mlittle-endian -Wall -c  -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


