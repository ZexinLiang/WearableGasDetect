################################################################################
# MRS Version: 1.9.2
# 自动生成的文件。不要编辑！
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../user/src/RF_PHY.c \
../user/src/adc.c \
../user/src/bme68x.c \
../user/src/bmeInRegis.c \
../user/src/bmelink.c \
../user/src/data.c \
../user/src/i2c.c \
../user/src/jed.c \
../user/src/main.c \
../user/src/peripheral.c \
../user/src/scd40reg.c \
../user/src/scd4x_i2c.c \
../user/src/sensirion_common.c \
../user/src/sensirion_i2c.c \
../user/src/sensirion_i2c_hal.c \
../user/src/task.c 

OBJS += \
./user/src/RF_PHY.o \
./user/src/adc.o \
./user/src/bme68x.o \
./user/src/bmeInRegis.o \
./user/src/bmelink.o \
./user/src/data.o \
./user/src/i2c.o \
./user/src/jed.o \
./user/src/main.o \
./user/src/peripheral.o \
./user/src/scd40reg.o \
./user/src/scd4x_i2c.o \
./user/src/sensirion_common.o \
./user/src/sensirion_i2c.o \
./user/src/sensirion_i2c_hal.o \
./user/src/task.o 

C_DEPS += \
./user/src/RF_PHY.d \
./user/src/adc.d \
./user/src/bme68x.d \
./user/src/bmeInRegis.d \
./user/src/bmelink.d \
./user/src/data.d \
./user/src/i2c.d \
./user/src/jed.d \
./user/src/main.d \
./user/src/peripheral.d \
./user/src/scd40reg.d \
./user/src/scd4x_i2c.d \
./user/src/sensirion_common.d \
./user/src/sensirion_i2c.d \
./user/src/sensirion_i2c_hal.d \
./user/src/task.d 


# Each subdirectory must supply rules for building sources it contributes
user/src/%.o: ../user/src/%.c
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -mcmodel=medany -msmall-data-limit=8 -mno-save-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common  -g -DDEBUG=3 -I"C:\Users\86135\Desktop\WearableGasDetect\CH582F\CH582F\Ld" -I"C:\Users\86135\Desktop\WearableGasDetect\CH582F\CH582F\Profile\include" -I"C:\Users\86135\Desktop\WearableGasDetect\CH582F\CH582F\HAL\include" -I"C:\Users\86135\Desktop\WearableGasDetect\CH582F\CH582F\LIB" -I"C:\Users\86135\Desktop\WearableGasDetect\CH582F\CH582F\Startup" -I"C:\Users\86135\Desktop\WearableGasDetect\CH582F\CH582F\RVMSIS" -I"C:\Users\86135\Desktop\WearableGasDetect\CH582F\CH582F\StdPeriphDriver\inc" -I"C:\Users\86135\Desktop\WearableGasDetect\CH582F\CH582F\user\inc" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

