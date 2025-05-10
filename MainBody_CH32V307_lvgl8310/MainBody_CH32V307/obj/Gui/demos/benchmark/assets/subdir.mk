################################################################################
# MRS Version: 2.1.0
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Gui/demos/benchmark/assets/img_benchmark_cogwheel_alpha16.c \
../Gui/demos/benchmark/assets/img_benchmark_cogwheel_argb.c \
../Gui/demos/benchmark/assets/img_benchmark_cogwheel_chroma_keyed.c \
../Gui/demos/benchmark/assets/img_benchmark_cogwheel_indexed16.c \
../Gui/demos/benchmark/assets/img_benchmark_cogwheel_rgb.c \
../Gui/demos/benchmark/assets/img_benchmark_cogwheel_rgb565a8.c \
../Gui/demos/benchmark/assets/lv_font_bechmark_montserrat_12_compr_az.c.c \
../Gui/demos/benchmark/assets/lv_font_bechmark_montserrat_16_compr_az.c.c \
../Gui/demos/benchmark/assets/lv_font_bechmark_montserrat_28_compr_az.c.c 

C_DEPS += \
./Gui/demos/benchmark/assets/img_benchmark_cogwheel_alpha16.d \
./Gui/demos/benchmark/assets/img_benchmark_cogwheel_argb.d \
./Gui/demos/benchmark/assets/img_benchmark_cogwheel_chroma_keyed.d \
./Gui/demos/benchmark/assets/img_benchmark_cogwheel_indexed16.d \
./Gui/demos/benchmark/assets/img_benchmark_cogwheel_rgb.d \
./Gui/demos/benchmark/assets/img_benchmark_cogwheel_rgb565a8.d \
./Gui/demos/benchmark/assets/lv_font_bechmark_montserrat_12_compr_az.c.d \
./Gui/demos/benchmark/assets/lv_font_bechmark_montserrat_16_compr_az.c.d \
./Gui/demos/benchmark/assets/lv_font_bechmark_montserrat_28_compr_az.c.d 

OBJS += \
./Gui/demos/benchmark/assets/img_benchmark_cogwheel_alpha16.o \
./Gui/demos/benchmark/assets/img_benchmark_cogwheel_argb.o \
./Gui/demos/benchmark/assets/img_benchmark_cogwheel_chroma_keyed.o \
./Gui/demos/benchmark/assets/img_benchmark_cogwheel_indexed16.o \
./Gui/demos/benchmark/assets/img_benchmark_cogwheel_rgb.o \
./Gui/demos/benchmark/assets/img_benchmark_cogwheel_rgb565a8.o \
./Gui/demos/benchmark/assets/lv_font_bechmark_montserrat_12_compr_az.c.o \
./Gui/demos/benchmark/assets/lv_font_bechmark_montserrat_16_compr_az.c.o \
./Gui/demos/benchmark/assets/lv_font_bechmark_montserrat_28_compr_az.c.o 



# Each subdirectory must supply rules for building sources it contributes
Gui/demos/benchmark/assets/%.o: ../Gui/demos/benchmark/assets/%.c
	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -fmax-errors=20 -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized -g -I"c:/Users/86135/Desktop/WearableGasDetect/MainBody_CH32V307_lvgl8310/MainBody_CH32V307/Debug" -I"c:/Users/86135/Desktop/WearableGasDetect/MainBody_CH32V307_lvgl8310/MainBody_CH32V307/Gui" -I"c:/Users/86135/Desktop/WearableGasDetect/MainBody_CH32V307_lvgl8310/MainBody_CH32V307/Core" -I"c:/Users/86135/Desktop/WearableGasDetect/MainBody_CH32V307_lvgl8310/MainBody_CH32V307/User" -I"c:/Users/86135/Desktop/WearableGasDetect/MainBody_CH32V307_lvgl8310/MainBody_CH32V307/Peripheral/inc" -I"c:/Users/86135/Desktop/WearableGasDetect/MainBody_CH32V307_lvgl8310/MainBody_CH32V307/Gui/custom" -I"c:/Users/86135/Desktop/WearableGasDetect/MainBody_CH32V307_lvgl8310/MainBody_CH32V307/Gui/generated" -I"c:/Users/86135/Desktop/WearableGasDetect/MainBody_CH32V307_lvgl8310/MainBody_CH32V307/Gui/generated/guider_customer_fonts" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
