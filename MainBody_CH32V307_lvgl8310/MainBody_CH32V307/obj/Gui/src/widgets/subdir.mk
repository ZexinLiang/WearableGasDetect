################################################################################
# MRS Version: 2.1.0
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Gui/src/widgets/lv_arc.c \
../Gui/src/widgets/lv_bar.c \
../Gui/src/widgets/lv_btn.c \
../Gui/src/widgets/lv_btnmatrix.c \
../Gui/src/widgets/lv_canvas.c \
../Gui/src/widgets/lv_checkbox.c \
../Gui/src/widgets/lv_dropdown.c \
../Gui/src/widgets/lv_img.c \
../Gui/src/widgets/lv_label.c \
../Gui/src/widgets/lv_line.c \
../Gui/src/widgets/lv_objx_templ.c \
../Gui/src/widgets/lv_roller.c \
../Gui/src/widgets/lv_slider.c \
../Gui/src/widgets/lv_switch.c \
../Gui/src/widgets/lv_table.c \
../Gui/src/widgets/lv_textarea.c 

C_DEPS += \
./Gui/src/widgets/lv_arc.d \
./Gui/src/widgets/lv_bar.d \
./Gui/src/widgets/lv_btn.d \
./Gui/src/widgets/lv_btnmatrix.d \
./Gui/src/widgets/lv_canvas.d \
./Gui/src/widgets/lv_checkbox.d \
./Gui/src/widgets/lv_dropdown.d \
./Gui/src/widgets/lv_img.d \
./Gui/src/widgets/lv_label.d \
./Gui/src/widgets/lv_line.d \
./Gui/src/widgets/lv_objx_templ.d \
./Gui/src/widgets/lv_roller.d \
./Gui/src/widgets/lv_slider.d \
./Gui/src/widgets/lv_switch.d \
./Gui/src/widgets/lv_table.d \
./Gui/src/widgets/lv_textarea.d 

OBJS += \
./Gui/src/widgets/lv_arc.o \
./Gui/src/widgets/lv_bar.o \
./Gui/src/widgets/lv_btn.o \
./Gui/src/widgets/lv_btnmatrix.o \
./Gui/src/widgets/lv_canvas.o \
./Gui/src/widgets/lv_checkbox.o \
./Gui/src/widgets/lv_dropdown.o \
./Gui/src/widgets/lv_img.o \
./Gui/src/widgets/lv_label.o \
./Gui/src/widgets/lv_line.o \
./Gui/src/widgets/lv_objx_templ.o \
./Gui/src/widgets/lv_roller.o \
./Gui/src/widgets/lv_slider.o \
./Gui/src/widgets/lv_switch.o \
./Gui/src/widgets/lv_table.o \
./Gui/src/widgets/lv_textarea.o 



# Each subdirectory must supply rules for building sources it contributes
Gui/src/widgets/%.o: ../Gui/src/widgets/%.c
	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -fmax-errors=20 -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized -g -I"c:/Users/86135/Desktop/WearableGasDetect/MainBody_CH32V307_lvgl8310/MainBody_CH32V307/Debug" -I"c:/Users/86135/Desktop/WearableGasDetect/MainBody_CH32V307_lvgl8310/MainBody_CH32V307/Gui" -I"c:/Users/86135/Desktop/WearableGasDetect/MainBody_CH32V307_lvgl8310/MainBody_CH32V307/Core" -I"c:/Users/86135/Desktop/WearableGasDetect/MainBody_CH32V307_lvgl8310/MainBody_CH32V307/User" -I"c:/Users/86135/Desktop/WearableGasDetect/MainBody_CH32V307_lvgl8310/MainBody_CH32V307/Peripheral/inc" -I"c:/Users/86135/Desktop/WearableGasDetect/MainBody_CH32V307_lvgl8310/MainBody_CH32V307/Gui/custom" -I"c:/Users/86135/Desktop/WearableGasDetect/MainBody_CH32V307_lvgl8310/MainBody_CH32V307/Gui/generated" -I"c:/Users/86135/Desktop/WearableGasDetect/MainBody_CH32V307_lvgl8310/MainBody_CH32V307/Gui/generated/guider_customer_fonts" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
