################################################################################
# MRS Version: 1.9.2
# 自动生成的文件。不要编辑！
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Gui/src/draw/sdl/lv_draw_sdl.c \
../Gui/src/draw/sdl/lv_draw_sdl_arc.c \
../Gui/src/draw/sdl/lv_draw_sdl_bg.c \
../Gui/src/draw/sdl/lv_draw_sdl_composite.c \
../Gui/src/draw/sdl/lv_draw_sdl_img.c \
../Gui/src/draw/sdl/lv_draw_sdl_label.c \
../Gui/src/draw/sdl/lv_draw_sdl_layer.c \
../Gui/src/draw/sdl/lv_draw_sdl_line.c \
../Gui/src/draw/sdl/lv_draw_sdl_mask.c \
../Gui/src/draw/sdl/lv_draw_sdl_polygon.c \
../Gui/src/draw/sdl/lv_draw_sdl_rect.c \
../Gui/src/draw/sdl/lv_draw_sdl_stack_blur.c \
../Gui/src/draw/sdl/lv_draw_sdl_texture_cache.c \
../Gui/src/draw/sdl/lv_draw_sdl_utils.c 

OBJS += \
./Gui/src/draw/sdl/lv_draw_sdl.o \
./Gui/src/draw/sdl/lv_draw_sdl_arc.o \
./Gui/src/draw/sdl/lv_draw_sdl_bg.o \
./Gui/src/draw/sdl/lv_draw_sdl_composite.o \
./Gui/src/draw/sdl/lv_draw_sdl_img.o \
./Gui/src/draw/sdl/lv_draw_sdl_label.o \
./Gui/src/draw/sdl/lv_draw_sdl_layer.o \
./Gui/src/draw/sdl/lv_draw_sdl_line.o \
./Gui/src/draw/sdl/lv_draw_sdl_mask.o \
./Gui/src/draw/sdl/lv_draw_sdl_polygon.o \
./Gui/src/draw/sdl/lv_draw_sdl_rect.o \
./Gui/src/draw/sdl/lv_draw_sdl_stack_blur.o \
./Gui/src/draw/sdl/lv_draw_sdl_texture_cache.o \
./Gui/src/draw/sdl/lv_draw_sdl_utils.o 

C_DEPS += \
./Gui/src/draw/sdl/lv_draw_sdl.d \
./Gui/src/draw/sdl/lv_draw_sdl_arc.d \
./Gui/src/draw/sdl/lv_draw_sdl_bg.d \
./Gui/src/draw/sdl/lv_draw_sdl_composite.d \
./Gui/src/draw/sdl/lv_draw_sdl_img.d \
./Gui/src/draw/sdl/lv_draw_sdl_label.d \
./Gui/src/draw/sdl/lv_draw_sdl_layer.d \
./Gui/src/draw/sdl/lv_draw_sdl_line.d \
./Gui/src/draw/sdl/lv_draw_sdl_mask.d \
./Gui/src/draw/sdl/lv_draw_sdl_polygon.d \
./Gui/src/draw/sdl/lv_draw_sdl_rect.d \
./Gui/src/draw/sdl/lv_draw_sdl_stack_blur.d \
./Gui/src/draw/sdl/lv_draw_sdl_texture_cache.d \
./Gui/src/draw/sdl/lv_draw_sdl_utils.d 


# Each subdirectory must supply rules for building sources it contributes
Gui/src/draw/sdl/%.o: ../Gui/src/draw/sdl/%.c
	@	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"C:\Users\86135\Desktop\WearableGasDetect\MainBody_CH32V307\MainBody_CH32V307\Debug" -I"C:\Users\86135\Desktop\WearableGasDetect\MainBody_CH32V307\MainBody_CH32V307\Gui" -I"C:\Users\86135\Desktop\WearableGasDetect\MainBody_CH32V307\MainBody_CH32V307\Core" -I"C:\Users\86135\Desktop\WearableGasDetect\MainBody_CH32V307\MainBody_CH32V307\User" -I"C:\Users\86135\Desktop\WearableGasDetect\MainBody_CH32V307\MainBody_CH32V307\Peripheral\inc" -I"C:\Users\86135\Desktop\WearableGasDetect\MainBody_CH32V307\MainBody_CH32V307\Gui\demos" -I"C:\Users\86135\Desktop\WearableGasDetect\MainBody_CH32V307\MainBody_CH32V307\Gui\demos\widgets" -I"C:\Users\86135\Desktop\WearableGasDetect\MainBody_CH32V307\MainBody_CH32V307\Gui\src" -I"C:\Users\86135\Desktop\WearableGasDetect\MainBody_CH32V307\MainBody_CH32V307\Gui\porting" -I"C:\Users\86135\Desktop\WearableGasDetect\MainBody_CH32V307\MainBody_CH32V307\Gui\custom" -I"C:\Users\86135\Desktop\WearableGasDetect\MainBody_CH32V307\MainBody_CH32V307\Gui\generated" -I"C:\Users\86135\Desktop\WearableGasDetect\MainBody_CH32V307\MainBody_CH32V307\Gui\generated\guider_customer_fonts" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

