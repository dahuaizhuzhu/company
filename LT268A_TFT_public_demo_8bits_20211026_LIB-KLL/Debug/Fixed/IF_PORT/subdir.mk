################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Fixed/IF_PORT/if_port.c 

OBJS += \
./Fixed/IF_PORT/if_port.o 

C_DEPS += \
./Fixed/IF_PORT/if_port.d 


# Each subdirectory must supply rules for building sources it contributes
Fixed/IF_PORT/%.o: ../Fixed/IF_PORT/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	mcore-elf-gcc -I"E:\C0_New_workspace\LT268A_TFT_240_320_20191204_USB_public_initial\Display" -I"E:\C0_New_workspace\LT268A_TFT_240_320_20191204_USB_public_initial\MCU\vector_table" -I"E:\C0_New_workspace\LT268A_TFT_240_320_20191204_USB_public_initial\MCU\uart" -I"E:\C0_New_workspace\LT268A_TFT_240_320_20191204_USB_public_initial\MCU\dma" -I"E:\C0_New_workspace\LT268A_TFT_240_320_20191204_USB_public_initial\MCU\sys" -I"E:\C0_New_workspace\LT268A_TFT_240_320_20191204_USB_public_initial\MCU\rtc" -I"E:\C0_New_workspace\LT268A_TFT_240_320_20191204_USB_public_initial\MCU\pwm" -I"E:\C0_New_workspace\LT268A_TFT_240_320_20191204_USB_public_initial\MCU\pit" -I"E:\C0_New_workspace\LT268A_TFT_240_320_20191204_USB_public_initial\MCU\iostring" -I"E:\C0_New_workspace\LT268A_TFT_240_320_20191204_USB_public_initial\MCU\flash" -I"E:\C0_New_workspace\LT268A_TFT_240_320_20191204_USB_public_initial\MCU\delay" -I"E:\C0_New_workspace\LT268A_TFT_240_320_20191204_USB_public_initial\Levetoplib" -I"E:\C0_New_workspace\LT268A_TFT_240_320_20191204_USB_public_initial\Function\bsp" -I"E:\C0_New_workspace\LT268A_TFT_240_320_20191204_USB_public_initial\Fixed\w25qxx" -I"E:\C0_New_workspace\LT268A_TFT_240_320_20191204_USB_public_initial\Fixed\type" -I"E:\C0_New_workspace\LT268A_TFT_240_320_20191204_USB_public_initial\Fixed\tp" -I"E:\C0_New_workspace\LT268A_TFT_240_320_20191204_USB_public_initial\Fixed\SinCosTable" -I"E:\C0_New_workspace\LT268A_TFT_240_320_20191204_USB_public_initial\Fixed\Module" -I"E:\C0_New_workspace\LT268A_TFT_240_320_20191204_USB_public_initial\Fixed\IF_PORT" -I"E:\C0_New_workspace\LT268A_TFT_240_320_20191204_USB_public_initial\Fixed\dctouch" -I"E:\C0_New_workspace\LT268A_TFT_240_320_20191204_USB_public_initial\Fixed\data" -I"E:\C0_New_workspace\LT268A_TFT_240_320_20191204_USB_public_initial\QRCODE" -I"E:\Tools\CCore_IDE/tool-chain/ccore-elf/lib/gcc/mcore-elf/4.6.0/include" -I"E:\Tools\CCore_IDE/tool-chain/ccore-elf/mcore-elf/include" -O1 -fno-common -ffunction-sections -g -mlittle-endian -Wall -c  -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


