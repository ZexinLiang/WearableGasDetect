################################################################################
# MRS Version: 2.1.0
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../user/src/RF_PHY.c \
../user/src/bme68x.c \
../user/src/bmeInRegis.c \
../user/src/bmelink.c \
../user/src/central.c \
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

C_DEPS += \
./user/src/RF_PHY.d \
./user/src/bme68x.d \
./user/src/bmeInRegis.d \
./user/src/bmelink.d \
./user/src/central.d \
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

OBJS += \
./user/src/RF_PHY.o \
./user/src/bme68x.o \
./user/src/bmeInRegis.o \
./user/src/bmelink.o \
./user/src/central.o \
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



# Each subdirectory must supply rules for building sources it contributes
user/src/%.o: ../user/src/%.c
	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -mcmodel=medany -msmall-data-limit=8 -mno-save-restore -fmax-errors=20 -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -g -DDEBUG=1 -I"c:/Users/86135/Desktop/WearableGasDetect/CH582F_Peri/CH582F/Ld" -I"c:/Users/86135/Desktop/WearableGasDetect/CH582F_Peri/CH582F/Profile/include" -I"c:/Users/86135/Desktop/WearableGasDetect/CH582F_Peri/CH582F/HAL/include" -I"c:/Users/86135/Desktop/WearableGasDetect/CH582F_Peri/CH582F/LIB" -I"c:/Users/86135/Desktop/WearableGasDetect/CH582F_Peri/CH582F/Startup" -I"c:/Users/86135/Desktop/WearableGasDetect/CH582F_Peri/CH582F/RVMSIS" -I"c:/Users/86135/Desktop/WearableGasDetect/CH582F_Peri/CH582F/StdPeriphDriver/inc" -I"c:/Users/86135/Desktop/WearableGasDetect/CH582F_Peri/CH582F/user/inc" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
