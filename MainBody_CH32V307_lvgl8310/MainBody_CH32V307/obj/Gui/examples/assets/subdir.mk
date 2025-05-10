################################################################################
# MRS Version: 2.1.0
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Gui/examples/assets/animimg001.c \
../Gui/examples/assets/animimg002.c \
../Gui/examples/assets/animimg003.c \
../Gui/examples/assets/img_caret_down.c \
../Gui/examples/assets/img_cogwheel_alpha16.c \
../Gui/examples/assets/img_cogwheel_argb.c \
../Gui/examples/assets/img_cogwheel_chroma_keyed.c \
../Gui/examples/assets/img_cogwheel_indexed16.c \
../Gui/examples/assets/img_cogwheel_rgb.c \
../Gui/examples/assets/img_hand.c \
../Gui/examples/assets/img_skew_strip.c \
../Gui/examples/assets/img_star.c \
../Gui/examples/assets/imgbtn_left.c \
../Gui/examples/assets/imgbtn_mid.c \
../Gui/examples/assets/imgbtn_right.c 

C_DEPS += \
./Gui/examples/assets/animimg001.d \
./Gui/examples/assets/animimg002.d \
./Gui/examples/assets/animimg003.d \
./Gui/examples/assets/img_caret_down.d \
./Gui/examples/assets/img_cogwheel_alpha16.d \
./Gui/examples/assets/img_cogwheel_argb.d \
./Gui/examples/assets/img_cogwheel_chroma_keyed.d \
./Gui/examples/assets/img_cogwheel_indexed16.d \
./Gui/examples/assets/img_cogwheel_rgb.d \
./Gui/examples/assets/img_hand.d \
./Gui/examples/assets/img_skew_strip.d \
./Gui/examples/assets/img_star.d \
./Gui/examples/assets/imgbtn_left.d \
./Gui/examples/assets/imgbtn_mid.d \
./Gui/examples/assets/imgbtn_right.d 

OBJS += \
./Gui/examples/assets/animimg001.o \
./Gui/examples/assets/animimg002.o \
./Gui/examples/assets/animimg003.o \
./Gui/examples/assets/img_caret_down.o \
./Gui/examples/assets/img_cogwheel_alpha16.o \
./Gui/examples/assets/img_cogwheel_argb.o \
./Gui/examples/assets/img_cogwheel_chroma_keyed.o \
./Gui/examples/assets/img_cogwheel_indexed16.o \
./Gui/examples/assets/img_cogwheel_rgb.o \
./Gui/examples/assets/img_hand.o \
./Gui/examples/assets/img_skew_strip.o \
./Gui/examples/assets/img_star.o \
./Gui/examples/assets/imgbtn_left.o \
./Gui/examples/assets/imgbtn_mid.o \
./Gui/examples/assets/imgbtn_right.o 



# Each subdirectory must supply rules for building sources it contributes
Gui/examples/assets/%.o: ../Gui/examples/assets/%.c
	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -fmax-errors=20 -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized -g -I"c:/Users/86135/Desktop/WearableGasDetect/MainBody_CH32V307_lvgl8310/MainBody_CH32V307/Debug" -I"c:/Users/86135/Desktop/WearableGasDetect/MainBody_CH32V307_lvgl8310/MainBody_CH32V307/Gui" -I"c:/Users/86135/Desktop/WearableGasDetect/MainBody_CH32V307_lvgl8310/MainBody_CH32V307/Core" -I"c:/Users/86135/Desktop/WearableGasDetect/MainBody_CH32V307_lvgl8310/MainBody_CH32V307/User" -I"c:/Users/86135/Desktop/WearableGasDetect/MainBody_CH32V307_lvgl8310/MainBody_CH32V307/Peripheral/inc" -I"c:/Users/86135/Desktop/WearableGasDetect/MainBody_CH32V307_lvgl8310/MainBody_CH32V307/Gui/custom" -I"c:/Users/86135/Desktop/WearableGasDetect/MainBody_CH32V307_lvgl8310/MainBody_CH32V307/Gui/generated" -I"c:/Users/86135/Desktop/WearableGasDetect/MainBody_CH32V307_lvgl8310/MainBody_CH32V307/Gui/generated/guider_customer_fonts" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
