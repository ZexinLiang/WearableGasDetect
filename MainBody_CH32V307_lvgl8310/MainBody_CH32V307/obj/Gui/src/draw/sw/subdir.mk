################################################################################
# MRS Version: 2.1.0
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Gui/src/draw/sw/lv_draw_sw.c \
../Gui/src/draw/sw/lv_draw_sw_arc.c \
../Gui/src/draw/sw/lv_draw_sw_blend.c \
../Gui/src/draw/sw/lv_draw_sw_dither.c \
../Gui/src/draw/sw/lv_draw_sw_gradient.c \
../Gui/src/draw/sw/lv_draw_sw_img.c \
../Gui/src/draw/sw/lv_draw_sw_layer.c \
../Gui/src/draw/sw/lv_draw_sw_letter.c \
../Gui/src/draw/sw/lv_draw_sw_line.c \
../Gui/src/draw/sw/lv_draw_sw_polygon.c \
../Gui/src/draw/sw/lv_draw_sw_rect.c \
../Gui/src/draw/sw/lv_draw_sw_transform.c 

C_DEPS += \
./Gui/src/draw/sw/lv_draw_sw.d \
./Gui/src/draw/sw/lv_draw_sw_arc.d \
./Gui/src/draw/sw/lv_draw_sw_blend.d \
./Gui/src/draw/sw/lv_draw_sw_dither.d \
./Gui/src/draw/sw/lv_draw_sw_gradient.d \
./Gui/src/draw/sw/lv_draw_sw_img.d \
./Gui/src/draw/sw/lv_draw_sw_layer.d \
./Gui/src/draw/sw/lv_draw_sw_letter.d \
./Gui/src/draw/sw/lv_draw_sw_line.d \
./Gui/src/draw/sw/lv_draw_sw_polygon.d \
./Gui/src/draw/sw/lv_draw_sw_rect.d \
./Gui/src/draw/sw/lv_draw_sw_transform.d 

OBJS += \
./Gui/src/draw/sw/lv_draw_sw.o \
./Gui/src/draw/sw/lv_draw_sw_arc.o \
./Gui/src/draw/sw/lv_draw_sw_blend.o \
./Gui/src/draw/sw/lv_draw_sw_dither.o \
./Gui/src/draw/sw/lv_draw_sw_gradient.o \
./Gui/src/draw/sw/lv_draw_sw_img.o \
./Gui/src/draw/sw/lv_draw_sw_layer.o \
./Gui/src/draw/sw/lv_draw_sw_letter.o \
./Gui/src/draw/sw/lv_draw_sw_line.o \
./Gui/src/draw/sw/lv_draw_sw_polygon.o \
./Gui/src/draw/sw/lv_draw_sw_rect.o \
./Gui/src/draw/sw/lv_draw_sw_transform.o 



# Each subdirectory must supply rules for building sources it contributes
Gui/src/draw/sw/%.o: ../Gui/src/draw/sw/%.c
	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -fmax-errors=20 -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized -g -I"c:/Users/86135/Desktop/WearableGasDetect/MainBody_CH32V307_lvgl8310/MainBody_CH32V307/Debug" -I"c:/Users/86135/Desktop/WearableGasDetect/MainBody_CH32V307_lvgl8310/MainBody_CH32V307/Gui" -I"c:/Users/86135/Desktop/WearableGasDetect/MainBody_CH32V307_lvgl8310/MainBody_CH32V307/Core" -I"c:/Users/86135/Desktop/WearableGasDetect/MainBody_CH32V307_lvgl8310/MainBody_CH32V307/User" -I"c:/Users/86135/Desktop/WearableGasDetect/MainBody_CH32V307_lvgl8310/MainBody_CH32V307/Peripheral/inc" -I"c:/Users/86135/Desktop/WearableGasDetect/MainBody_CH32V307_lvgl8310/MainBody_CH32V307/Gui/custom" -I"c:/Users/86135/Desktop/WearableGasDetect/MainBody_CH32V307_lvgl8310/MainBody_CH32V307/Gui/generated" -I"c:/Users/86135/Desktop/WearableGasDetect/MainBody_CH32V307_lvgl8310/MainBody_CH32V307/Gui/generated/guider_customer_fonts" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
