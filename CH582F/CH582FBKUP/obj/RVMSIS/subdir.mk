################################################################################
# MRS Version: 1.9.2
# 自动生成的文件。不要编辑！
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../RVMSIS/core_riscv.c 

OBJS += \
./RVMSIS/core_riscv.o 

C_DEPS += \
./RVMSIS/core_riscv.d 


# Each subdirectory must supply rules for building sources it contributes
RVMSIS/%.o: ../RVMSIS/%.c
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -mcmodel=medany -msmall-data-limit=8 -mno-save-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common  -g -DDEBUG=3 -I"C:\Users\86135\Desktop\WearableGasDetect\CH582F\CH582F\Ld" -I"C:\Users\86135\Desktop\WearableGasDetect\CH582F\CH582F\Profile\include" -I"C:\Users\86135\Desktop\WearableGasDetect\CH582F\CH582F\HAL\include" -I"C:\Users\86135\Desktop\WearableGasDetect\CH582F\CH582F\LIB" -I"C:\Users\86135\Desktop\WearableGasDetect\CH582F\CH582F\Startup" -I"C:\Users\86135\Desktop\WearableGasDetect\CH582F\CH582F\RVMSIS" -I"C:\Users\86135\Desktop\WearableGasDetect\CH582F\CH582F\StdPeriphDriver\inc" -I"C:\Users\86135\Desktop\WearableGasDetect\CH582F\CH582F\user\inc" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

