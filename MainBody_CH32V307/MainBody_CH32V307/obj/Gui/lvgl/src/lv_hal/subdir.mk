################################################################################
# MRS Version: 1.9.2
# 自动生成的文件。不要编辑！
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Gui/lvgl/src/lv_hal/lv_hal_disp.c \
../Gui/lvgl/src/lv_hal/lv_hal_indev.c \
../Gui/lvgl/src/lv_hal/lv_hal_tick.c 

OBJS += \
./Gui/lvgl/src/lv_hal/lv_hal_disp.o \
./Gui/lvgl/src/lv_hal/lv_hal_indev.o \
./Gui/lvgl/src/lv_hal/lv_hal_tick.o 

C_DEPS += \
./Gui/lvgl/src/lv_hal/lv_hal_disp.d \
./Gui/lvgl/src/lv_hal/lv_hal_indev.d \
./Gui/lvgl/src/lv_hal/lv_hal_tick.d 


# Each subdirectory must supply rules for building sources it contributes
Gui/lvgl/src/lv_hal/%.o: ../Gui/lvgl/src/lv_hal/%.c
	@	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"C:\Users\86135\Desktop\WearableGasDetect\MainBody_CH32V307\MainBody_CH32V307\Debug" -I"C:\Users\86135\Desktop\WearableGasDetect\MainBody_CH32V307\MainBody_CH32V307\Gui" -I"C:\Users\86135\Desktop\WearableGasDetect\MainBody_CH32V307\MainBody_CH32V307\Gui\lvgl" -I"C:\Users\86135\Desktop\WearableGasDetect\MainBody_CH32V307\MainBody_CH32V307\Gui\lvgl_app\src\lv_demo_widgets" -I"C:\Users\86135\Desktop\WearableGasDetect\MainBody_CH32V307\MainBody_CH32V307\Gui\lvgl_app" -I"C:\Users\86135\Desktop\WearableGasDetect\MainBody_CH32V307\MainBody_CH32V307\Gui\lvgl\examples\porting" -I"C:\Users\86135\Desktop\WearableGasDetect\MainBody_CH32V307\MainBody_CH32V307\Gui\lvgl\src\lv_core" -I"C:\Users\86135\Desktop\WearableGasDetect\MainBody_CH32V307\MainBody_CH32V307\Gui\lvgl\src\lv_draw" -I"C:\Users\86135\Desktop\WearableGasDetect\MainBody_CH32V307\MainBody_CH32V307\Gui\lvgl\src\lv_font" -I"C:\Users\86135\Desktop\WearableGasDetect\MainBody_CH32V307\MainBody_CH32V307\Gui\lvgl\src\lv_gpu" -I"C:\Users\86135\Desktop\WearableGasDetect\MainBody_CH32V307\MainBody_CH32V307\Gui\lvgl\src\lv_hal" -I"C:\Users\86135\Desktop\WearableGasDetect\MainBody_CH32V307\MainBody_CH32V307\Gui\lvgl\src\lv_misc" -I"C:\Users\86135\Desktop\WearableGasDetect\MainBody_CH32V307\MainBody_CH32V307\Gui\lvgl\src\lv_themes" -I"C:\Users\86135\Desktop\WearableGasDetect\MainBody_CH32V307\MainBody_CH32V307\Gui\lvgl\src\lv_widgets" -I"C:\Users\86135\Desktop\WearableGasDetect\MainBody_CH32V307\MainBody_CH32V307\Core" -I"C:\Users\86135\Desktop\WearableGasDetect\MainBody_CH32V307\MainBody_CH32V307\User" -I"C:\Users\86135\Desktop\WearableGasDetect\MainBody_CH32V307\MainBody_CH32V307\Peripheral\inc" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

