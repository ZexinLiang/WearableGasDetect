################################################################################
# MRS Version: 2.1.0
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Gui/lvgl/src/lv_misc/lv_anim.c \
../Gui/lvgl/src/lv_misc/lv_area.c \
../Gui/lvgl/src/lv_misc/lv_async.c \
../Gui/lvgl/src/lv_misc/lv_bidi.c \
../Gui/lvgl/src/lv_misc/lv_color.c \
../Gui/lvgl/src/lv_misc/lv_debug.c \
../Gui/lvgl/src/lv_misc/lv_fs.c \
../Gui/lvgl/src/lv_misc/lv_gc.c \
../Gui/lvgl/src/lv_misc/lv_ll.c \
../Gui/lvgl/src/lv_misc/lv_log.c \
../Gui/lvgl/src/lv_misc/lv_math.c \
../Gui/lvgl/src/lv_misc/lv_mem.c \
../Gui/lvgl/src/lv_misc/lv_printf.c \
../Gui/lvgl/src/lv_misc/lv_task.c \
../Gui/lvgl/src/lv_misc/lv_templ.c \
../Gui/lvgl/src/lv_misc/lv_txt.c \
../Gui/lvgl/src/lv_misc/lv_txt_ap.c \
../Gui/lvgl/src/lv_misc/lv_utils.c 

C_DEPS += \
./Gui/lvgl/src/lv_misc/lv_anim.d \
./Gui/lvgl/src/lv_misc/lv_area.d \
./Gui/lvgl/src/lv_misc/lv_async.d \
./Gui/lvgl/src/lv_misc/lv_bidi.d \
./Gui/lvgl/src/lv_misc/lv_color.d \
./Gui/lvgl/src/lv_misc/lv_debug.d \
./Gui/lvgl/src/lv_misc/lv_fs.d \
./Gui/lvgl/src/lv_misc/lv_gc.d \
./Gui/lvgl/src/lv_misc/lv_ll.d \
./Gui/lvgl/src/lv_misc/lv_log.d \
./Gui/lvgl/src/lv_misc/lv_math.d \
./Gui/lvgl/src/lv_misc/lv_mem.d \
./Gui/lvgl/src/lv_misc/lv_printf.d \
./Gui/lvgl/src/lv_misc/lv_task.d \
./Gui/lvgl/src/lv_misc/lv_templ.d \
./Gui/lvgl/src/lv_misc/lv_txt.d \
./Gui/lvgl/src/lv_misc/lv_txt_ap.d \
./Gui/lvgl/src/lv_misc/lv_utils.d 

OBJS += \
./Gui/lvgl/src/lv_misc/lv_anim.o \
./Gui/lvgl/src/lv_misc/lv_area.o \
./Gui/lvgl/src/lv_misc/lv_async.o \
./Gui/lvgl/src/lv_misc/lv_bidi.o \
./Gui/lvgl/src/lv_misc/lv_color.o \
./Gui/lvgl/src/lv_misc/lv_debug.o \
./Gui/lvgl/src/lv_misc/lv_fs.o \
./Gui/lvgl/src/lv_misc/lv_gc.o \
./Gui/lvgl/src/lv_misc/lv_ll.o \
./Gui/lvgl/src/lv_misc/lv_log.o \
./Gui/lvgl/src/lv_misc/lv_math.o \
./Gui/lvgl/src/lv_misc/lv_mem.o \
./Gui/lvgl/src/lv_misc/lv_printf.o \
./Gui/lvgl/src/lv_misc/lv_task.o \
./Gui/lvgl/src/lv_misc/lv_templ.o \
./Gui/lvgl/src/lv_misc/lv_txt.o \
./Gui/lvgl/src/lv_misc/lv_txt_ap.o \
./Gui/lvgl/src/lv_misc/lv_utils.o 



# Each subdirectory must supply rules for building sources it contributes
Gui/lvgl/src/lv_misc/%.o: ../Gui/lvgl/src/lv_misc/%.c
	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -fmax-errors=20 -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized -g -I"c:/Users/86135/Desktop/WearableGasDetect/MainBody_CH32V307_lvgl8310/MainBody_CH32V307/Debug" -I"c:/Users/86135/Desktop/WearableGasDetect/MainBody_CH32V307_lvgl8310/MainBody_CH32V307/Gui" -I"c:/Users/86135/Desktop/WearableGasDetect/MainBody_CH32V307_lvgl8310/MainBody_CH32V307/Gui/lvgl" -I"c:/Users/86135/Desktop/WearableGasDetect/MainBody_CH32V307_lvgl8310/MainBody_CH32V307/Gui/lvgl_app/src/lv_demo_widgets" -I"c:/Users/86135/Desktop/WearableGasDetect/MainBody_CH32V307_lvgl8310/MainBody_CH32V307/Gui/lvgl_app" -I"c:/Users/86135/Desktop/WearableGasDetect/MainBody_CH32V307_lvgl8310/MainBody_CH32V307/Gui/lvgl/examples/porting" -I"c:/Users/86135/Desktop/WearableGasDetect/MainBody_CH32V307_lvgl8310/MainBody_CH32V307/Gui/lvgl/src/lv_core" -I"c:/Users/86135/Desktop/WearableGasDetect/MainBody_CH32V307_lvgl8310/MainBody_CH32V307/Gui/lvgl/src/lv_draw" -I"c:/Users/86135/Desktop/WearableGasDetect/MainBody_CH32V307_lvgl8310/MainBody_CH32V307/Gui/lvgl/src/lv_font" -I"c:/Users/86135/Desktop/WearableGasDetect/MainBody_CH32V307_lvgl8310/MainBody_CH32V307/Gui/lvgl/src/lv_gpu" -I"c:/Users/86135/Desktop/WearableGasDetect/MainBody_CH32V307_lvgl8310/MainBody_CH32V307/Gui/lvgl/src/lv_hal" -I"c:/Users/86135/Desktop/WearableGasDetect/MainBody_CH32V307_lvgl8310/MainBody_CH32V307/Gui/lvgl/src/lv_misc" -I"c:/Users/86135/Desktop/WearableGasDetect/MainBody_CH32V307_lvgl8310/MainBody_CH32V307/Gui/lvgl/src/lv_themes" -I"c:/Users/86135/Desktop/WearableGasDetect/MainBody_CH32V307_lvgl8310/MainBody_CH32V307/Gui/lvgl/src/lv_widgets" -I"c:/Users/86135/Desktop/WearableGasDetect/MainBody_CH32V307_lvgl8310/MainBody_CH32V307/Core" -I"c:/Users/86135/Desktop/WearableGasDetect/MainBody_CH32V307_lvgl8310/MainBody_CH32V307/User" -I"c:/Users/86135/Desktop/WearableGasDetect/MainBody_CH32V307_lvgl8310/MainBody_CH32V307/Peripheral/inc" -I"c:/Users/86135/Desktop/WearableGasDetect/MainBody_CH32V307_lvgl8310/MainBody_CH32V307/Gui/custom" -I"c:/Users/86135/Desktop/WearableGasDetect/MainBody_CH32V307_lvgl8310/MainBody_CH32V307/Gui/generated" -I"c:/Users/86135/Desktop/WearableGasDetect/MainBody_CH32V307_lvgl8310/MainBody_CH32V307/Gui/generated/guider_customer_fonts" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
