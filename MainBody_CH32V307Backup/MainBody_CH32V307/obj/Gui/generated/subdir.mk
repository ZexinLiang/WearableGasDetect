################################################################################
# MRS Version: 2.1.0
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Gui/generated/events_init.c \
../Gui/generated/gui_guider.c \
../Gui/generated/setup_scr_screen_alarmst.c \
../Gui/generated/setup_scr_screen_devicest.c \
../Gui/generated/setup_scr_screen_network.c \
../Gui/generated/setup_scr_screen_none.c \
../Gui/generated/setup_scr_screen_pwon.c \
../Gui/generated/setup_scr_screen_rtdata.c \
../Gui/generated/setup_scr_screen_settings.c \
../Gui/generated/setup_scr_screen_sub_device.c 

C_DEPS += \
./Gui/generated/events_init.d \
./Gui/generated/gui_guider.d \
./Gui/generated/setup_scr_screen_alarmst.d \
./Gui/generated/setup_scr_screen_devicest.d \
./Gui/generated/setup_scr_screen_network.d \
./Gui/generated/setup_scr_screen_none.d \
./Gui/generated/setup_scr_screen_pwon.d \
./Gui/generated/setup_scr_screen_rtdata.d \
./Gui/generated/setup_scr_screen_settings.d \
./Gui/generated/setup_scr_screen_sub_device.d 

OBJS += \
./Gui/generated/events_init.o \
./Gui/generated/gui_guider.o \
./Gui/generated/setup_scr_screen_alarmst.o \
./Gui/generated/setup_scr_screen_devicest.o \
./Gui/generated/setup_scr_screen_network.o \
./Gui/generated/setup_scr_screen_none.o \
./Gui/generated/setup_scr_screen_pwon.o \
./Gui/generated/setup_scr_screen_rtdata.o \
./Gui/generated/setup_scr_screen_settings.o \
./Gui/generated/setup_scr_screen_sub_device.o 



# Each subdirectory must supply rules for building sources it contributes
Gui/generated/%.o: ../Gui/generated/%.c
	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -fmax-errors=20 -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized -g -I"c:/Users/86135/Desktop/WearableGasDetect/MainBody_CH32V307Backup/MainBody_CH32V307/Debug" -I"c:/Users/86135/Desktop/WearableGasDetect/MainBody_CH32V307Backup/MainBody_CH32V307/Gui" -I"c:/Users/86135/Desktop/WearableGasDetect/MainBody_CH32V307Backup/MainBody_CH32V307/Gui/lvgl" -I"c:/Users/86135/Desktop/WearableGasDetect/MainBody_CH32V307Backup/MainBody_CH32V307/Gui/lvgl_app/src/lv_demo_widgets" -I"c:/Users/86135/Desktop/WearableGasDetect/MainBody_CH32V307Backup/MainBody_CH32V307/Gui/lvgl_app" -I"c:/Users/86135/Desktop/WearableGasDetect/MainBody_CH32V307Backup/MainBody_CH32V307/Gui/lvgl/examples/porting" -I"c:/Users/86135/Desktop/WearableGasDetect/MainBody_CH32V307Backup/MainBody_CH32V307/Gui/lvgl/src/lv_core" -I"c:/Users/86135/Desktop/WearableGasDetect/MainBody_CH32V307Backup/MainBody_CH32V307/Gui/lvgl/src/lv_draw" -I"c:/Users/86135/Desktop/WearableGasDetect/MainBody_CH32V307Backup/MainBody_CH32V307/Gui/lvgl/src/lv_font" -I"c:/Users/86135/Desktop/WearableGasDetect/MainBody_CH32V307Backup/MainBody_CH32V307/Gui/lvgl/src/lv_gpu" -I"c:/Users/86135/Desktop/WearableGasDetect/MainBody_CH32V307Backup/MainBody_CH32V307/Gui/lvgl/src/lv_hal" -I"c:/Users/86135/Desktop/WearableGasDetect/MainBody_CH32V307Backup/MainBody_CH32V307/Gui/lvgl/src/lv_misc" -I"c:/Users/86135/Desktop/WearableGasDetect/MainBody_CH32V307Backup/MainBody_CH32V307/Gui/lvgl/src/lv_themes" -I"c:/Users/86135/Desktop/WearableGasDetect/MainBody_CH32V307Backup/MainBody_CH32V307/Gui/lvgl/src/lv_widgets" -I"c:/Users/86135/Desktop/WearableGasDetect/MainBody_CH32V307Backup/MainBody_CH32V307/Core" -I"c:/Users/86135/Desktop/WearableGasDetect/MainBody_CH32V307Backup/MainBody_CH32V307/User" -I"c:/Users/86135/Desktop/WearableGasDetect/MainBody_CH32V307Backup/MainBody_CH32V307/Peripheral/inc" -I"c:/Users/86135/Desktop/WearableGasDetect/MainBody_CH32V307Backup/MainBody_CH32V307/Gui/custom" -I"c:/Users/86135/Desktop/WearableGasDetect/MainBody_CH32V307Backup/MainBody_CH32V307/Gui/generated" -I"c:/Users/86135/Desktop/WearableGasDetect/MainBody_CH32V307Backup/MainBody_CH32V307/Gui/generated/guider_customer_fonts" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
