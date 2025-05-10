################################################################################
# MRS Version: 1.9.2
# 自动生成的文件。不要编辑！
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


# Each subdirectory must supply rules for building sources it contributes
Gui/lvgl/src/lv_draw/%.o: ../Gui/lvgl/src/lv_draw/%.c
	@	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"C:\Users\86135\Desktop\WearableGasDetect\MainBody_CH32V307\MainBody_CH32V307\Debug" -I"C:\Users\86135\Desktop\WearableGasDetect\MainBody_CH32V307\MainBody_CH32V307\Gui" -I"C:\Users\86135\Desktop\WearableGasDetect\MainBody_CH32V307\MainBody_CH32V307\Gui\lvgl" -I"C:\Users\86135\Desktop\WearableGasDetect\MainBody_CH32V307\MainBody_CH32V307\Gui\lvgl_app\src\lv_demo_widgets" -I"C:\Users\86135\Desktop\WearableGasDetect\MainBody_CH32V307\MainBody_CH32V307\Gui\lvgl_app" -I"C:\Users\86135\Desktop\WearableGasDetect\MainBody_CH32V307\MainBody_CH32V307\Gui\lvgl\examples\porting" -I"C:\Users\86135\Desktop\WearableGasDetect\MainBody_CH32V307\MainBody_CH32V307\Gui\lvgl\src\lv_core" -I"C:\Users\86135\Desktop\WearableGasDetect\MainBody_CH32V307\MainBody_CH32V307\Gui\lvgl\src\lv_draw" -I"C:\Users\86135\Desktop\WearableGasDetect\MainBody_CH32V307\MainBody_CH32V307\Gui\lvgl\src\lv_font" -I"C:\Users\86135\Desktop\WearableGasDetect\MainBody_CH32V307\MainBody_CH32V307\Gui\lvgl\src\lv_gpu" -I"C:\Users\86135\Desktop\WearableGasDetect\MainBody_CH32V307\MainBody_CH32V307\Gui\lvgl\src\lv_hal" -I"C:\Users\86135\Desktop\WearableGasDetect\MainBody_CH32V307\MainBody_CH32V307\Gui\lvgl\src\lv_misc" -I"C:\Users\86135\Desktop\WearableGasDetect\MainBody_CH32V307\MainBody_CH32V307\Gui\lvgl\src\lv_themes" -I"C:\Users\86135\Desktop\WearableGasDetect\MainBody_CH32V307\MainBody_CH32V307\Gui\lvgl\src\lv_widgets" -I"C:\Users\86135\Desktop\WearableGasDetect\MainBody_CH32V307\MainBody_CH32V307\Core" -I"C:\Users\86135\Desktop\WearableGasDetect\MainBody_CH32V307\MainBody_CH32V307\User" -I"C:\Users\86135\Desktop\WearableGasDetect\MainBody_CH32V307\MainBody_CH32V307\Peripheral\inc" -I"C:\Users\86135\Desktop\WearableGasDetect\MainBody_CH32V307\MainBody_CH32V307\Gui\custom" -I"C:\Users\86135\Desktop\WearableGasDetect\MainBody_CH32V307\MainBody_CH32V307\Gui\generated" -I"C:\Users\86135\Desktop\WearableGasDetect\MainBody_CH32V307\MainBody_CH32V307\Gui\generated\guider_customer_fonts" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

