################################################################################
# MRS Version: 1.9.2
# 自动生成的文件。不要编辑！
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../user/src/central.c \
../user/src/control.c \
../user/src/main.c 

OBJS += \
./user/src/central.o \
./user/src/control.o \
./user/src/main.o 

C_DEPS += \
./user/src/central.d \
./user/src/control.d \
./user/src/main.d 


# Each subdirectory must supply rules for building sources it contributes
user/src/%.o: ../user/src/%.c
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -mcmodel=medany -msmall-data-limit=8 -mno-save-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common  -g -DDEBUG=1 -I"C:\Users\86135\Desktop\WearableGasDetect\MainBoard_CH582\MainBoard_CH582\Ld" -I"C:\Users\86135\Desktop\WearableGasDetect\MainBoard_CH582\MainBoard_CH582\Profile\include" -I"C:\Users\86135\Desktop\WearableGasDetect\MainBoard_CH582\MainBoard_CH582\HAL\include" -I"C:\Users\86135\Desktop\WearableGasDetect\MainBoard_CH582\MainBoard_CH582\LIB" -I"C:\Users\86135\Desktop\WearableGasDetect\MainBoard_CH582\MainBoard_CH582\Startup" -I"C:\Users\86135\Desktop\WearableGasDetect\MainBoard_CH582\MainBoard_CH582\RVMSIS" -I"C:\Users\86135\Desktop\WearableGasDetect\MainBoard_CH582\MainBoard_CH582\StdPeriphDriver\inc" -I"C:\Users\86135\Desktop\WearableGasDetect\MainBoard_CH582\MainBoard_CH582\user\inc" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

