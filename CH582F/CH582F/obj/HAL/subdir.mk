################################################################################
# MRS Version: 1.9.2
# 自动生成的文件。不要编辑！
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../HAL/KEY.c \
../HAL/LED.c \
../HAL/MCU.c \
../HAL/RTC.c \
../HAL/SLEEP.c 

OBJS += \
./HAL/KEY.o \
./HAL/LED.o \
./HAL/MCU.o \
./HAL/RTC.o \
./HAL/SLEEP.o 

C_DEPS += \
./HAL/KEY.d \
./HAL/LED.d \
./HAL/MCU.d \
./HAL/RTC.d \
./HAL/SLEEP.d 


# Each subdirectory must supply rules for building sources it contributes
HAL/%.o: ../HAL/%.c
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -mcmodel=medany -msmall-data-limit=8 -mno-save-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common  -g -DDEBUG=1 -I"C:\Users\86135\Desktop\WearableGasDetect\CH582F\CH582F\Ld" -I"C:\Users\86135\Desktop\WearableGasDetect\CH582F\CH582F\Profile\include" -I"C:\Users\86135\Desktop\WearableGasDetect\CH582F\CH582F\HAL\include" -I"C:\Users\86135\Desktop\WearableGasDetect\CH582F\CH582F\LIB" -I"C:\Users\86135\Desktop\WearableGasDetect\CH582F\CH582F\Startup" -I"C:\Users\86135\Desktop\WearableGasDetect\CH582F\CH582F\RVMSIS" -I"C:\Users\86135\Desktop\WearableGasDetect\CH582F\CH582F\StdPeriphDriver\inc" -I"C:\Users\86135\Desktop\WearableGasDetect\CH582F\CH582F\user\inc" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

