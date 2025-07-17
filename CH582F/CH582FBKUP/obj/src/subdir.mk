################################################################################
# MRS Version: 1.9.2
# 自动生成的文件。不要编辑！
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/RF_PHY.c \
../src/bme68x.c \
../src/bmelink.c \
../src/i2c.c \
../src/jed.c \
../src/main.c \
../src/peripheral.c \
../src/scd4x_i2c.c \
../src/sensirion_common.c \
../src/sensirion_i2c.c \
../src/sensirion_i2c_hal.c \
../src/task.c 

OBJS += \
./src/RF_PHY.o \
./src/bme68x.o \
./src/bmelink.o \
./src/i2c.o \
./src/jed.o \
./src/main.o \
./src/peripheral.o \
./src/scd4x_i2c.o \
./src/sensirion_common.o \
./src/sensirion_i2c.o \
./src/sensirion_i2c_hal.o \
./src/task.o 

C_DEPS += \
./src/RF_PHY.d \
./src/bme68x.d \
./src/bmelink.d \
./src/i2c.d \
./src/jed.d \
./src/main.d \
./src/peripheral.d \
./src/scd4x_i2c.d \
./src/sensirion_common.d \
./src/sensirion_i2c.d \
./src/sensirion_i2c_hal.d \
./src/task.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -mcmodel=medany -msmall-data-limit=8 -mno-save-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common  -g -DDEBUG=1 -I"D:\CH32_project\CH582F\CH582F\inc" -I"D:\CH32_project\CH582F\CH582F\Ld" -I"D:\CH32_project\CH582F\CH582F\Profile\include" -I"D:\CH32_project\CH582F\CH582F\HAL\include" -I"D:\CH32_project\CH582F\CH582F\LIB" -I"D:\CH32_project\CH582F\CH582F\Startup" -I"D:\CH32_project\CH582F\CH582F\RVMSIS" -I"D:\CH32_project\CH582F\CH582F\StdPeriphDriver\inc" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

