################################################################################
# MRS Version: 2.1.0
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Gui/lvgl/src/lv_draw/lv_draw_arc.c \
../Gui/lvgl/src/lv_draw/lv_draw_blend.c \
../Gui/lvgl/src/lv_draw/lv_draw_img.c \
../Gui/lvgl/src/lv_draw/lv_draw_label.c \
../Gui/lvgl/src/lv_draw/lv_draw_line.c \
../Gui/lvgl/src/lv_draw/lv_draw_mask.c \
../Gui/lvgl/src/lv_draw/lv_draw_rect.c \
../Gui/lvgl/src/lv_draw/lv_draw_triangle.c \
../Gui/lvgl/src/lv_draw/lv_img_buf.c \
../Gui/lvgl/src/lv_draw/lv_img_cache.c \
../Gui/lvgl/src/lv_draw/lv_img_decoder.c 

C_DEPS += \
./Gui/lvgl/src/lv_draw/lv_draw_arc.d \
./Gui/lvgl/src/lv_draw/lv_draw_blend.d \
./Gui/lvgl/src/lv_draw/lv_draw_img.d \
./Gui/lvgl/src/lv_draw/lv_draw_label.d \
./Gui/lvgl/src/lv_draw/lv_draw_line.d \
./Gui/lvgl/src/lv_draw/lv_draw_mask.d \
./Gui/lvgl/src/lv_draw/lv_draw_rect.d \
./Gui/lvgl/src/lv_draw/lv_draw_triangle.d \
./Gui/lvgl/src/lv_draw/lv_img_buf.d \
./Gui/lvgl/src/lv_draw/lv_img_cache.d \
./Gui/lvgl/src/lv_draw/lv_img_decoder.d 

OBJS += \
./Gui/lvgl/src/lv_draw/lv_draw_arc.o \
./Gui/lvgl/src/lv_draw/lv_draw_blend.o \
./Gui/lvgl/src/lv_draw/lv_draw_img.o \
./Gui/lvgl/src/lv_draw/lv_draw_label.o \
./Gui/lvgl/src/lv_draw/lv_draw_line.o \
./Gui/lvgl/src/lv_draw/lv_draw_mask.o \
./Gui/lvgl/src/lv_draw/lv_draw_rect.o \
./Gui/lvgl/src/lv_draw/lv_draw_triangle.o \
./Gui/lvgl/src/lv_draw/lv_img_buf.o \
./Gui/lvgl/src/lv_draw/lv_img_cache.o \
./Gui/lvgl/src/lv_draw/lv_img_decoder.o 



# Each subdirectory must supply rules for building sources it contributes
Gui/lvgl/src/lv_draw/%.o: ../Gui/lvgl/src/lv_draw/%.c
	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -fmax-errors=20 -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized -g -I"c:/Users/86135/Desktop/WearableGasDetect/MainBody_CH32V307Backup/MainBody_CH32V307/Debug" -I"c:/Users/86135/Desktop/WearableGasDetect/MainBody_CH32V307Backup/MainBody_CH32V307/Gui" -I"c:/Users/86135/Desktop/WearableGasDetect/MainBody_CH32V307Backup/MainBody_CH32V307/Gui/lvgl" -I"c:/Users/86135/Desktop/WearableGasDetect/MainBody_CH32V307Backup/MainBody_CH32V307/Gui/lvgl_app/src/lv_demo_widgets" -I"c:/Users/86135/Desktop/WearableGasDetect/MainBody_CH32V307Backup/MainBody_CH32V307/Gui/lvgl_app" -I"c:/Users/86135/Desktop/WearableGasDetect/MainBody_CH32V307Backup/MainBody_CH32V307/Gui/lvgl/examples/porting" -I"c:/Users/86135/Desktop/WearableGasDetect/MainBody_CH32V307Backup/MainBody_CH32V307/Gui/lvgl/src/lv_core" -I"c:/Users/86135/Desktop/WearableGasDetect/MainBody_CH32V307Backup/MainBody_CH32V307/Gui/lvgl/src/lv_draw" -I"c:/Users/86135/Desktop/WearableGasDetect/MainBody_CH32V307Backup/MainBody_CH32V307/Gui/lvgl/src/lv_font" -I"c:/Users/86135/Desktop/WearableGasDetect/MainBody_CH32V307Backup/MainBody_CH32V307/Gui/lvgl/src/lv_gpu" -I"c:/Users/86135/Desktop/WearableGasDetect/MainBody_CH32V307Backup/MainBody_CH32V307/Gui/lvgl/src/lv_hal" -I"c:/Users/86135/Desktop/WearableGasDetect/MainBody_CH32V307Backup/MainBody_CH32V307/Gui/lvgl/src/lv_misc" -I"c:/Users/86135/Desktop/WearableGasDetect/MainBody_CH32V307Backup/MainBody_CH32V307/Gui/lvgl/src/lv_themes" -I"c:/Users/86135/Desktop/WearableGasDetect/MainBody_CH32V307Backup/MainBody_CH32V307/Gui/lvgl/src/lv_widgets" -I"c:/Users/86135/Desktop/WearableGasDetect/MainBody_CH32V307Backup/MainBody_CH32V307/Core" -I"c:/Users/86135/Desktop/WearableGasDetect/MainBody_CH32V307Backup/MainBody_CH32V307/User" -I"c:/Users/86135/Desktop/WearableGasDetect/MainBody_CH32V307Backup/MainBody_CH32V307/Peripheral/inc" -I"c:/Users/86135/Desktop/WearableGasDetect/MainBody_CH32V307Backup/MainBody_CH32V307/Gui/custom" -I"c:/Users/86135/Desktop/WearableGasDetect/MainBody_CH32V307Backup/MainBody_CH32V307/Gui/generated" -I"c:/Users/86135/Desktop/WearableGasDetect/MainBody_CH32V307Backup/MainBody_CH32V307/Gui/generated/guider_customer_fonts" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
