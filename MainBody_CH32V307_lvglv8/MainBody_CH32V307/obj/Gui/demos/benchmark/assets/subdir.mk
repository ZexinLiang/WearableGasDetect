################################################################################
# MRS Version: 1.9.2
# 自动生成的文件。不要编辑！
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


# Each subdirectory must supply rules for building sources it contributes
Gui/demos/benchmark/assets/%.o: ../Gui/demos/benchmark/assets/%.c
	@	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"C:\Users\86135\Desktop\WearableGasDetect\MainBody_CH32V307\MainBody_CH32V307\Debug" -I"C:\Users\86135\Desktop\WearableGasDetect\MainBody_CH32V307\MainBody_CH32V307\Gui" -I"C:\Users\86135\Desktop\WearableGasDetect\MainBody_CH32V307\MainBody_CH32V307\Core" -I"C:\Users\86135\Desktop\WearableGasDetect\MainBody_CH32V307\MainBody_CH32V307\User" -I"C:\Users\86135\Desktop\WearableGasDetect\MainBody_CH32V307\MainBody_CH32V307\Peripheral\inc" -I"C:\Users\86135\Desktop\WearableGasDetect\MainBody_CH32V307\MainBody_CH32V307\Gui\demos" -I"C:\Users\86135\Desktop\WearableGasDetect\MainBody_CH32V307\MainBody_CH32V307\Gui\demos\widgets" -I"C:\Users\86135\Desktop\WearableGasDetect\MainBody_CH32V307\MainBody_CH32V307\Gui\src" -I"C:\Users\86135\Desktop\WearableGasDetect\MainBody_CH32V307\MainBody_CH32V307\Gui\porting" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

