################################################################################
# MRS Version: 2.1.0
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Profile/devinfoservice.c \
../Profile/gattprofile.c 

C_DEPS += \
./Profile/devinfoservice.d \
./Profile/gattprofile.d 

OBJS += \
./Profile/devinfoservice.o \
./Profile/gattprofile.o 



# Each subdirectory must supply rules for building sources it contributes
Profile/%.o: ../Profile/%.c
	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -mcmodel=medany -msmall-data-limit=8 -mno-save-restore -fmax-errors=20 -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -g -DDEBUG=1 -I"c:/Users/86135/Desktop/WearableGasDetect/CH582F_Peri/CH582F/Ld" -I"c:/Users/86135/Desktop/WearableGasDetect/CH582F_Peri/CH582F/Profile/include" -I"c:/Users/86135/Desktop/WearableGasDetect/CH582F_Peri/CH582F/HAL/include" -I"c:/Users/86135/Desktop/WearableGasDetect/CH582F_Peri/CH582F/LIB" -I"c:/Users/86135/Desktop/WearableGasDetect/CH582F_Peri/CH582F/Startup" -I"c:/Users/86135/Desktop/WearableGasDetect/CH582F_Peri/CH582F/RVMSIS" -I"c:/Users/86135/Desktop/WearableGasDetect/CH582F_Peri/CH582F/StdPeriphDriver/inc" -I"c:/Users/86135/Desktop/WearableGasDetect/CH582F_Peri/CH582F/user/inc" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
