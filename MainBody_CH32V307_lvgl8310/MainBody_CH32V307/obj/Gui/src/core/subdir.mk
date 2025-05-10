################################################################################
# MRS Version: 2.1.0
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Gui/src/core/lv_disp.c \
../Gui/src/core/lv_event.c \
../Gui/src/core/lv_group.c \
../Gui/src/core/lv_indev.c \
../Gui/src/core/lv_indev_scroll.c \
../Gui/src/core/lv_obj.c \
../Gui/src/core/lv_obj_class.c \
../Gui/src/core/lv_obj_draw.c \
../Gui/src/core/lv_obj_pos.c \
../Gui/src/core/lv_obj_scroll.c \
../Gui/src/core/lv_obj_style.c \
../Gui/src/core/lv_obj_style_gen.c \
../Gui/src/core/lv_obj_tree.c \
../Gui/src/core/lv_refr.c \
../Gui/src/core/lv_theme.c 

C_DEPS += \
./Gui/src/core/lv_disp.d \
./Gui/src/core/lv_event.d \
./Gui/src/core/lv_group.d \
./Gui/src/core/lv_indev.d \
./Gui/src/core/lv_indev_scroll.d \
./Gui/src/core/lv_obj.d \
./Gui/src/core/lv_obj_class.d \
./Gui/src/core/lv_obj_draw.d \
./Gui/src/core/lv_obj_pos.d \
./Gui/src/core/lv_obj_scroll.d \
./Gui/src/core/lv_obj_style.d \
./Gui/src/core/lv_obj_style_gen.d \
./Gui/src/core/lv_obj_tree.d \
./Gui/src/core/lv_refr.d \
./Gui/src/core/lv_theme.d 

OBJS += \
./Gui/src/core/lv_disp.o \
./Gui/src/core/lv_event.o \
./Gui/src/core/lv_group.o \
./Gui/src/core/lv_indev.o \
./Gui/src/core/lv_indev_scroll.o \
./Gui/src/core/lv_obj.o \
./Gui/src/core/lv_obj_class.o \
./Gui/src/core/lv_obj_draw.o \
./Gui/src/core/lv_obj_pos.o \
./Gui/src/core/lv_obj_scroll.o \
./Gui/src/core/lv_obj_style.o \
./Gui/src/core/lv_obj_style_gen.o \
./Gui/src/core/lv_obj_tree.o \
./Gui/src/core/lv_refr.o \
./Gui/src/core/lv_theme.o 



# Each subdirectory must supply rules for building sources it contributes
Gui/src/core/%.o: ../Gui/src/core/%.c
	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -fmax-errors=20 -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized -g -I"c:/Users/86135/Desktop/WearableGasDetect/MainBody_CH32V307_lvgl8310/MainBody_CH32V307/Debug" -I"c:/Users/86135/Desktop/WearableGasDetect/MainBody_CH32V307_lvgl8310/MainBody_CH32V307/Gui" -I"c:/Users/86135/Desktop/WearableGasDetect/MainBody_CH32V307_lvgl8310/MainBody_CH32V307/Core" -I"c:/Users/86135/Desktop/WearableGasDetect/MainBody_CH32V307_lvgl8310/MainBody_CH32V307/User" -I"c:/Users/86135/Desktop/WearableGasDetect/MainBody_CH32V307_lvgl8310/MainBody_CH32V307/Peripheral/inc" -I"c:/Users/86135/Desktop/WearableGasDetect/MainBody_CH32V307_lvgl8310/MainBody_CH32V307/Gui/custom" -I"c:/Users/86135/Desktop/WearableGasDetect/MainBody_CH32V307_lvgl8310/MainBody_CH32V307/Gui/generated" -I"c:/Users/86135/Desktop/WearableGasDetect/MainBody_CH32V307_lvgl8310/MainBody_CH32V307/Gui/generated/guider_customer_fonts" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
