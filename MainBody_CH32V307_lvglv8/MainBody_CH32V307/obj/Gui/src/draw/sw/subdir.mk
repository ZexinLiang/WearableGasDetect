################################################################################
# MRS Version: 1.9.2
# 自动生成的文件。不要编辑！
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


# Each subdirectory must supply rules for building sources it contributes
Gui/src/draw/sw/%.o: ../Gui/src/draw/sw/%.c
	@	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"C:\Users\86135\Desktop\WearableGasDetect\MainBody_CH32V307\MainBody_CH32V307\Debug" -I"C:\Users\86135\Desktop\WearableGasDetect\MainBody_CH32V307\MainBody_CH32V307\Gui" -I"C:\Users\86135\Desktop\WearableGasDetect\MainBody_CH32V307\MainBody_CH32V307\Core" -I"C:\Users\86135\Desktop\WearableGasDetect\MainBody_CH32V307\MainBody_CH32V307\User" -I"C:\Users\86135\Desktop\WearableGasDetect\MainBody_CH32V307\MainBody_CH32V307\Peripheral\inc" -I"C:\Users\86135\Desktop\WearableGasDetect\MainBody_CH32V307\MainBody_CH32V307\Gui\demos" -I"C:\Users\86135\Desktop\WearableGasDetect\MainBody_CH32V307\MainBody_CH32V307\Gui\demos\widgets" -I"C:\Users\86135\Desktop\WearableGasDetect\MainBody_CH32V307\MainBody_CH32V307\Gui\src" -I"C:\Users\86135\Desktop\WearableGasDetect\MainBody_CH32V307\MainBody_CH32V307\Gui\porting" -I"C:\Users\86135\Desktop\WearableGasDetect\MainBody_CH32V307\MainBody_CH32V307\Gui\custom" -I"C:\Users\86135\Desktop\WearableGasDetect\MainBody_CH32V307\MainBody_CH32V307\Gui\generated" -I"C:\Users\86135\Desktop\WearableGasDetect\MainBody_CH32V307\MainBody_CH32V307\Gui\generated\guider_customer_fonts" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

