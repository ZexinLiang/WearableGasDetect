################################################################################
# MRS Version: 1.9.2
# 自动生成的文件。不要编辑！
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../StdPeriphDriver/CH58x_adc.c \
../StdPeriphDriver/CH58x_clk.c \
../StdPeriphDriver/CH58x_flash.c \
../StdPeriphDriver/CH58x_gpio.c \
../StdPeriphDriver/CH58x_i2c.c \
../StdPeriphDriver/CH58x_pwr.c \
../StdPeriphDriver/CH58x_spi1.c \
../StdPeriphDriver/CH58x_sys.c \
../StdPeriphDriver/CH58x_uart0.c \
../StdPeriphDriver/CH58x_uart1.c \
../StdPeriphDriver/CH58x_usb2dev.c \
../StdPeriphDriver/CH58x_usb2hostBase.c \
../StdPeriphDriver/CH58x_usb2hostClass.c 

OBJS += \
./StdPeriphDriver/CH58x_adc.o \
./StdPeriphDriver/CH58x_clk.o \
./StdPeriphDriver/CH58x_flash.o \
./StdPeriphDriver/CH58x_gpio.o \
./StdPeriphDriver/CH58x_i2c.o \
./StdPeriphDriver/CH58x_pwr.o \
./StdPeriphDriver/CH58x_spi1.o \
./StdPeriphDriver/CH58x_sys.o \
./StdPeriphDriver/CH58x_uart0.o \
./StdPeriphDriver/CH58x_uart1.o \
./StdPeriphDriver/CH58x_usb2dev.o \
./StdPeriphDriver/CH58x_usb2hostBase.o \
./StdPeriphDriver/CH58x_usb2hostClass.o 

C_DEPS += \
./StdPeriphDriver/CH58x_adc.d \
./StdPeriphDriver/CH58x_clk.d \
./StdPeriphDriver/CH58x_flash.d \
./StdPeriphDriver/CH58x_gpio.d \
./StdPeriphDriver/CH58x_i2c.d \
./StdPeriphDriver/CH58x_pwr.d \
./StdPeriphDriver/CH58x_spi1.d \
./StdPeriphDriver/CH58x_sys.d \
./StdPeriphDriver/CH58x_uart0.d \
./StdPeriphDriver/CH58x_uart1.d \
./StdPeriphDriver/CH58x_usb2dev.d \
./StdPeriphDriver/CH58x_usb2hostBase.d \
./StdPeriphDriver/CH58x_usb2hostClass.d 


# Each subdirectory must supply rules for building sources it contributes
StdPeriphDriver/%.o: ../StdPeriphDriver/%.c
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -mcmodel=medany -msmall-data-limit=8 -mno-save-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common  -g -DDEBUG=1 -I"C:\Users\86135\Desktop\WearableGasDetect\CH582F\CH582F\Ld" -I"C:\Users\86135\Desktop\WearableGasDetect\CH582F\CH582F\Profile\include" -I"C:\Users\86135\Desktop\WearableGasDetect\CH582F\CH582F\HAL\include" -I"C:\Users\86135\Desktop\WearableGasDetect\CH582F\CH582F\LIB" -I"C:\Users\86135\Desktop\WearableGasDetect\CH582F\CH582F\Startup" -I"C:\Users\86135\Desktop\WearableGasDetect\CH582F\CH582F\RVMSIS" -I"C:\Users\86135\Desktop\WearableGasDetect\CH582F\CH582F\StdPeriphDriver\inc" -I"C:\Users\86135\Desktop\WearableGasDetect\CH582F\CH582F\user\inc" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

