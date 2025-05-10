################################################################################
# MRS Version: 2.1.0
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Gui/lvgl/src/lv_hal/lv_hal_disp.c \
../Gui/lvgl/src/lv_hal/lv_hal_indev.c \
../Gui/lvgl/src/lv_hal/lv_hal_tick.c 

C_DEPS += \
./Gui/lvgl/src/lv_hal/lv_hal_disp.d \
./Gui/lvgl/src/lv_hal/lv_hal_indev.d \
./Gui/lvgl/src/lv_hal/lv_hal_tick.d 

OBJS += \
./Gui/lvgl/src/lv_hal/lv_hal_disp.o \
./Gui/lvgl/src/lv_hal/lv_hal_indev.o \
./Gui/lvgl/src/lv_hal/lv_hal_tick.o 



# Each subdirectory must supply rules for building sources it contributes
Gui/lvgl/src/lv_hal/%.o: ../Gui/lvgl/src/lv_hal/%.c
	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -fmax-errors=20 -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized -g -I"c:/Users/86135/Desktop/WearableGasDetect/MainBody_CH32V307_lvgl8310/MainBody_CH32V307/Debug" -I"c:/Users/86135/Desktop/WearableGasDetect/MainBody_CH32V307_lvgl8310/MainBody_CH32V307/Gui" -I"c:/Users/86135/Desktop/WearableGasDetect/MainBody_CH32V307_lvgl8310/MainBody_CH32V307/Gui/lvgl" -I"c:/Users/86135/Desktop/WearableGasDetect/MainBody_CH32V307_lvgl8310/MainBody_CH32V307/Gui/lvgl_app/src/lv_demo_widgets" -I"c:/Users/86135/Desktop/WearableGasDetect/MainBody_CH32V307_lvgl8310/MainBody_CH32V307/Gui/lvgl_app" -I"c:/Users/86135/Desktop/WearableGasDetect/MainBody_CH32V307_lvgl8310/MainBody_CH32V307/Gui/lvgl/examples/porting" -I"c:/Users/86135/Desktop/WearableGasDetect/MainBody_CH32V307_lvgl8310/MainBody_CH32V307/Gui/lvgl/src/lv_core" -I"c:/Users/86135/Desktop/WearableGasDetect/MainBody_CH32V307_lvgl8310/MainBody_CH32V307/Gui/lvgl/src/lv_draw" -I"c:/Users/86135/Desktop/WearableGasDetect/MainBody_CH32V307_lvgl8310/MainBody_CH32V307/Gui/lvgl/src/lv_font" -I"c:/Users/86135/Desktop/WearableGasDetect/MainBody_CH32V307_lvgl8310/MainBody_CH32V307/Gui/lvgl/src/lv_gpu" -I"c:/Users/86135/Desktop/WearableGasDetect/MainBody_CH32V307_lvgl8310/MainBody_CH32V307/Gui/lvgl/src/lv_hal" -I"c:/Users/86135/Desktop/WearableGasDetect/MainBody_CH32V307_lvgl8310/MainBody_CH32V307/Gui/lvgl/src/lv_misc" -I"c:/Users/86135/Desktop/WearableGasDetect/MainBody_CH32V307_lvgl8310/MainBody_CH32V307/Gui/lvgl/src/lv_themes" -I"c:/Users/86135/Desktop/WearableGasDetect/MainBody_CH32V307_lvgl8310/MainBody_CH32V307/Gui/lvgl/src/lv_widgets" -I"c:/Users/86135/Desktop/WearableGasDetect/MainBody_CH32V307_lvgl8310/MainBody_CH32V307/Core" -I"c:/Users/86135/Desktop/WearableGasDetect/MainBody_CH32V307_lvgl8310/MainBody_CH32V307/User" -I"c:/Users/86135/Desktop/WearableGasDetect/MainBody_CH32V307_lvgl8310/MainBody_CH32V307/Peripheral/inc" -I"c:/Users/86135/Desktop/WearableGasDetect/MainBody_CH32V307_lvgl8310/MainBody_CH32V307/Gui/custom" -I"c:/Users/86135/Desktop/WearableGasDetect/MainBody_CH32V307_lvgl8310/MainBody_CH32V307/Gui/generated" -I"c:/Users/86135/Desktop/WearableGasDetect/MainBody_CH32V307_lvgl8310/MainBody_CH32V307/Gui/generated/guider_customer_fonts" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
