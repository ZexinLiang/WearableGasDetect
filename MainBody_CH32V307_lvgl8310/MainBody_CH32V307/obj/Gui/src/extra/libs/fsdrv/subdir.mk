################################################################################
# MRS Version: 2.1.0
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Gui/src/extra/libs/fsdrv/lv_fs_fatfs.c \
../Gui/src/extra/libs/fsdrv/lv_fs_posix.c \
../Gui/src/extra/libs/fsdrv/lv_fs_stdio.c \
../Gui/src/extra/libs/fsdrv/lv_fs_win32.c 

C_DEPS += \
./Gui/src/extra/libs/fsdrv/lv_fs_fatfs.d \
./Gui/src/extra/libs/fsdrv/lv_fs_posix.d \
./Gui/src/extra/libs/fsdrv/lv_fs_stdio.d \
./Gui/src/extra/libs/fsdrv/lv_fs_win32.d 

OBJS += \
./Gui/src/extra/libs/fsdrv/lv_fs_fatfs.o \
./Gui/src/extra/libs/fsdrv/lv_fs_posix.o \
./Gui/src/extra/libs/fsdrv/lv_fs_stdio.o \
./Gui/src/extra/libs/fsdrv/lv_fs_win32.o 



# Each subdirectory must supply rules for building sources it contributes
Gui/src/extra/libs/fsdrv/%.o: ../Gui/src/extra/libs/fsdrv/%.c
	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -fmax-errors=20 -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized -g -I"c:/Users/86135/Desktop/WearableGasDetect/MainBody_CH32V307_lvgl8310/MainBody_CH32V307/Debug" -I"c:/Users/86135/Desktop/WearableGasDetect/MainBody_CH32V307_lvgl8310/MainBody_CH32V307/Gui" -I"c:/Users/86135/Desktop/WearableGasDetect/MainBody_CH32V307_lvgl8310/MainBody_CH32V307/Core" -I"c:/Users/86135/Desktop/WearableGasDetect/MainBody_CH32V307_lvgl8310/MainBody_CH32V307/User" -I"c:/Users/86135/Desktop/WearableGasDetect/MainBody_CH32V307_lvgl8310/MainBody_CH32V307/Peripheral/inc" -I"c:/Users/86135/Desktop/WearableGasDetect/MainBody_CH32V307_lvgl8310/MainBody_CH32V307/Gui/custom" -I"c:/Users/86135/Desktop/WearableGasDetect/MainBody_CH32V307_lvgl8310/MainBody_CH32V307/Gui/generated" -I"c:/Users/86135/Desktop/WearableGasDetect/MainBody_CH32V307_lvgl8310/MainBody_CH32V307/Gui/generated/guider_customer_fonts" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
