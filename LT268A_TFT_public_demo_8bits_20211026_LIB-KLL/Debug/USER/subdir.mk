################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../USER/main.c \
../USER/vector_rce.c 

S_SRCS += \
../USER/crt0.s \
../USER/fp_ff1.s 

OBJS += \
./USER/crt0.o \
./USER/fp_ff1.o \
./USER/main.o \
./USER/vector_rce.o 

C_DEPS += \
./USER/main.d \
./USER/vector_rce.d 


# Each subdirectory must supply rules for building sources it contributes
USER/%.o: ../USER/%.s
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Assembler'
	mcore-elf-as -g -gstabs -EL -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

USER/%.o: ../USER/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	mcore-elf-gcc -I"D:\E Battery Display Screen\project_2\LT268A_TFT_public_demo_8bits_20211026_LIB-KLL\Display" -I"D:\E Battery Display Screen\project_2\LT268A_TFT_public_demo_8bits_20211026_LIB-KLL\MCU\vector_table" -I"D:\E Battery Display Screen\project_2\LT268A_TFT_public_demo_8bits_20211026_LIB-KLL\MCU\uart" -I"D:\E Battery Display Screen\project_2\LT268A_TFT_public_demo_8bits_20211026_LIB-KLL\MCU\dma" -I"D:\E Battery Display Screen\project_2\LT268A_TFT_public_demo_8bits_20211026_LIB-KLL\MCU\sys" -I"D:\E Battery Display Screen\project_2\LT268A_TFT_public_demo_8bits_20211026_LIB-KLL\MCU\rtc" -I"D:\E Battery Display Screen\project_2\LT268A_TFT_public_demo_8bits_20211026_LIB-KLL\MCU\pwm" -I"D:\E Battery Display Screen\project_2\LT268A_TFT_public_demo_8bits_20211026_LIB-KLL\MCU\pit" -I"D:\E Battery Display Screen\project_2\LT268A_TFT_public_demo_8bits_20211026_LIB-KLL\MCU\iostring" -I"D:\E Battery Display Screen\project_2\LT268A_TFT_public_demo_8bits_20211026_LIB-KLL\MCU\flash" -I"D:\E Battery Display Screen\project_2\LT268A_TFT_public_demo_8bits_20211026_LIB-KLL\MCU\delay" -I"D:\E Battery Display Screen\project_2\LT268A_TFT_public_demo_8bits_20211026_LIB-KLL\Levetoplib" -I"D:\E Battery Display Screen\project_2\LT268A_TFT_public_demo_8bits_20211026_LIB-KLL\Function\bsp" -I"D:\E Battery Display Screen\project_2\LT268A_TFT_public_demo_8bits_20211026_LIB-KLL\Function\bsp_user" -I"D:\E Battery Display Screen\project_2\LT268A_TFT_public_demo_8bits_20211026_LIB-KLL" -I"D:\E Battery Display Screen\project_2\LT268A_TFT_public_demo_8bits_20211026_LIB-KLL\Fixed\w25qxx" -I"D:\E Battery Display Screen\project_2\LT268A_TFT_public_demo_8bits_20211026_LIB-KLL\Fixed\type" -I"D:\E Battery Display Screen\project_2\LT268A_TFT_public_demo_8bits_20211026_LIB-KLL\Fixed\tp" -I"D:\E Battery Display Screen\project_2\LT268A_TFT_public_demo_8bits_20211026_LIB-KLL\Fixed\SinCosTable" -I"D:\E Battery Display Screen\project_2\LT268A_TFT_public_demo_8bits_20211026_LIB-KLL\Fixed\Module" -I"D:\E Battery Display Screen\project_2\LT268A_TFT_public_demo_8bits_20211026_LIB-KLL\Fixed\dctouch" -I"D:\E Battery Display Screen\project_2\LT268A_TFT_public_demo_8bits_20211026_LIB-KLL\Fixed\data" -I"D:\E Battery Display Screen\project_2\LT268A_TFT_public_demo_8bits_20211026_LIB-KLL\QRCODE" -I"D:\CCore_IDE/tool-chain/ccore-elf/lib/gcc/mcore-elf/4.6.0/include" -I"D:\CCore_IDE/tool-chain/ccore-elf/mcore-elf/include" -O1 -fno-common -ffunction-sections -g -mlittle-endian -Wall -c  -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


