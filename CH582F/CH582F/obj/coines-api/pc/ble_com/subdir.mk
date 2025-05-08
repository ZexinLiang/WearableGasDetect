################################################################################
# MRS Version: 1.9.2
# 自动生成的文件。不要编辑！
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../coines-api/pc/ble_com/ble_com.c \
../coines-api/pc/ble_com/simpleble_lib_loader.c 

OBJS += \
./coines-api/pc/ble_com/ble_com.o \
./coines-api/pc/ble_com/simpleble_lib_loader.o 

C_DEPS += \
./coines-api/pc/ble_com/ble_com.d \
./coines-api/pc/ble_com/simpleble_lib_loader.d 


# Each subdirectory must supply rules for building sources it contributes
coines-api/pc/ble_com/%.o: ../coines-api/pc/ble_com/%.c
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -mcmodel=medany -msmall-data-limit=8 -mno-save-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common  -g -DDEBUG=1 -I"../StdPeriphDriver/inc" -I"D:\CH32_project\CH582F\CH582F\coines-api" -I"../RVMSIS" -I"/CH582F/APP/include" -I"D:\CH32_project\CH582F\CH582F\inc" -I"/CH582F/Startup" -I"D:\CH32_project\CH582F\CH582F\Ld" -I"D:\CH32_project\CH582F\CH582F\Profile\include" -I"D:\CH32_project\CH582F\CH582F\HAL\include" -I"D:\CH32_project\CH582F\CH582F\LIB" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

