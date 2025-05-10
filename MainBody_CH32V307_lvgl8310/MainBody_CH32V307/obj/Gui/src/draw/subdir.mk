################################################################################
# MRS Version: 2.1.0
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Gui/src/draw/lv_draw.c \
../Gui/src/draw/lv_draw_arc.c \
../Gui/src/draw/lv_draw_img.c \
../Gui/src/draw/lv_draw_label.c \
../Gui/src/draw/lv_draw_layer.c \
../Gui/src/draw/lv_draw_line.c \
../Gui/src/draw/lv_draw_mask.c \
../Gui/src/draw/lv_draw_rect.c \
../Gui/src/draw/lv_draw_transform.c \
../Gui/src/draw/lv_draw_triangle.c \
../Gui/src/draw/lv_img_buf.c \
../Gui/src/draw/lv_img_cache.c \
../Gui/src/draw/lv_img_decoder.c 

C_DEPS += \
./Gui/src/draw/lv_draw.d \
./Gui/src/draw/lv_draw_arc.d \
./Gui/src/draw/lv_draw_img.d \
./Gui/src/draw/lv_draw_label.d \
./Gui/src/draw/lv_draw_layer.d \
./Gui/src/draw/lv_draw_line.d \
./Gui/src/draw/lv_draw_mask.d \
./Gui/src/draw/lv_draw_rect.d \
./Gui/src/draw/lv_draw_transform.d \
./Gui/src/draw/lv_draw_triangle.d \
./Gui/src/draw/lv_img_buf.d \
./Gui/src/draw/lv_img_cache.d \
./Gui/src/draw/lv_img_decoder.d 

OBJS += \
./Gui/src/draw/lv_draw.o \
./Gui/src/draw/lv_draw_arc.o \
./Gui/src/draw/lv_draw_img.o \
./Gui/src/draw/lv_draw_label.o \
./Gui/src/draw/lv_draw_layer.o \
./Gui/src/draw/lv_draw_line.o \
./Gui/src/draw/lv_draw_mask.o \
./Gui/src/draw/lv_draw_rect.o \
./Gui/src/draw/lv_draw_transform.o \
./Gui/src/draw/lv_draw_triangle.o \
./Gui/src/draw/lv_img_buf.o \
./Gui/src/draw/lv_img_cache.o \
./Gui/src/draw/lv_img_decoder.o 



# Each subdirectory must supply rules for building sources it contributes
Gui/src/draw/%.o: ../Gui/src/draw/%.c
	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -fmax-errors=20 -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized -g -I"c:/Users/86135/Desktop/WearableGasDetect/MainBody_CH32V307_lvgl8310/MainBody_CH32V307/Debug" -I"c:/Users/86135/Desktop/WearableGasDetect/MainBody_CH32V307_lvgl8310/MainBody_CH32V307/Gui" -I"c:/Users/86135/Desktop/WearableGasDetect/MainBody_CH32V307_lvgl8310/MainBody_CH32V307/Core" -I"c:/Users/86135/Desktop/WearableGasDetect/MainBody_CH32V307_lvgl8310/MainBody_CH32V307/User" -I"c:/Users/86135/Desktop/WearableGasDetect/MainBody_CH32V307_lvgl8310/MainBody_CH32V307/Peripheral/inc" -I"c:/Users/86135/Desktop/WearableGasDetect/MainBody_CH32V307_lvgl8310/MainBody_CH32V307/Gui/custom" -I"c:/Users/86135/Desktop/WearableGasDetect/MainBody_CH32V307_lvgl8310/MainBody_CH32V307/Gui/generated" -I"c:/Users/86135/Desktop/WearableGasDetect/MainBody_CH32V307_lvgl8310/MainBody_CH32V307/Gui/generated/guider_customer_fonts" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
