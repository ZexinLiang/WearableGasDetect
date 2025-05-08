################################################################################
# MRS Version: 1.9.2
# 自动生成的文件。不要编辑！
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Gui/lvgl_app/src/lv_ex_style/lv_ex_style_1.c \
../Gui/lvgl_app/src/lv_ex_style/lv_ex_style_10.c \
../Gui/lvgl_app/src/lv_ex_style/lv_ex_style_11.c \
../Gui/lvgl_app/src/lv_ex_style/lv_ex_style_2.c \
../Gui/lvgl_app/src/lv_ex_style/lv_ex_style_3.c \
../Gui/lvgl_app/src/lv_ex_style/lv_ex_style_4.c \
../Gui/lvgl_app/src/lv_ex_style/lv_ex_style_5.c \
../Gui/lvgl_app/src/lv_ex_style/lv_ex_style_6.c \
../Gui/lvgl_app/src/lv_ex_style/lv_ex_style_7.c \
../Gui/lvgl_app/src/lv_ex_style/lv_ex_style_8.c \
../Gui/lvgl_app/src/lv_ex_style/lv_ex_style_9.c 

OBJS += \
./Gui/lvgl_app/src/lv_ex_style/lv_ex_style_1.o \
./Gui/lvgl_app/src/lv_ex_style/lv_ex_style_10.o \
./Gui/lvgl_app/src/lv_ex_style/lv_ex_style_11.o \
./Gui/lvgl_app/src/lv_ex_style/lv_ex_style_2.o \
./Gui/lvgl_app/src/lv_ex_style/lv_ex_style_3.o \
./Gui/lvgl_app/src/lv_ex_style/lv_ex_style_4.o \
./Gui/lvgl_app/src/lv_ex_style/lv_ex_style_5.o \
./Gui/lvgl_app/src/lv_ex_style/lv_ex_style_6.o \
./Gui/lvgl_app/src/lv_ex_style/lv_ex_style_7.o \
./Gui/lvgl_app/src/lv_ex_style/lv_ex_style_8.o \
./Gui/lvgl_app/src/lv_ex_style/lv_ex_style_9.o 

C_DEPS += \
./Gui/lvgl_app/src/lv_ex_style/lv_ex_style_1.d \
./Gui/lvgl_app/src/lv_ex_style/lv_ex_style_10.d \
./Gui/lvgl_app/src/lv_ex_style/lv_ex_style_11.d \
./Gui/lvgl_app/src/lv_ex_style/lv_ex_style_2.d \
./Gui/lvgl_app/src/lv_ex_style/lv_ex_style_3.d \
./Gui/lvgl_app/src/lv_ex_style/lv_ex_style_4.d \
./Gui/lvgl_app/src/lv_ex_style/lv_ex_style_5.d \
./Gui/lvgl_app/src/lv_ex_style/lv_ex_style_6.d \
./Gui/lvgl_app/src/lv_ex_style/lv_ex_style_7.d \
./Gui/lvgl_app/src/lv_ex_style/lv_ex_style_8.d \
./Gui/lvgl_app/src/lv_ex_style/lv_ex_style_9.d 


# Each subdirectory must supply rules for building sources it contributes
Gui/lvgl_app/src/lv_ex_style/%.o: ../Gui/lvgl_app/src/lv_ex_style/%.c
	@	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"C:\Users\86135\Desktop\WearableGasDetect\MainBody_CH32V307\MainBody_CH32V307\Debug" -I"C:\Users\86135\Desktop\WearableGasDetect\MainBody_CH32V307\MainBody_CH32V307\Gui" -I"C:\Users\86135\Desktop\WearableGasDetect\MainBody_CH32V307\MainBody_CH32V307\Gui\lvgl" -I"C:\Users\86135\Desktop\WearableGasDetect\MainBody_CH32V307\MainBody_CH32V307\Gui\lvgl_app\src\lv_demo_widgets" -I"C:\Users\86135\Desktop\WearableGasDetect\MainBody_CH32V307\MainBody_CH32V307\Gui\lvgl_app" -I"C:\Users\86135\Desktop\WearableGasDetect\MainBody_CH32V307\MainBody_CH32V307\Gui\lvgl\examples\porting" -I"C:\Users\86135\Desktop\WearableGasDetect\MainBody_CH32V307\MainBody_CH32V307\Gui\lvgl\src\lv_core" -I"C:\Users\86135\Desktop\WearableGasDetect\MainBody_CH32V307\MainBody_CH32V307\Gui\lvgl\src\lv_draw" -I"C:\Users\86135\Desktop\WearableGasDetect\MainBody_CH32V307\MainBody_CH32V307\Gui\lvgl\src\lv_font" -I"C:\Users\86135\Desktop\WearableGasDetect\MainBody_CH32V307\MainBody_CH32V307\Gui\lvgl\src\lv_gpu" -I"C:\Users\86135\Desktop\WearableGasDetect\MainBody_CH32V307\MainBody_CH32V307\Gui\lvgl\src\lv_hal" -I"C:\Users\86135\Desktop\WearableGasDetect\MainBody_CH32V307\MainBody_CH32V307\Gui\lvgl\src\lv_misc" -I"C:\Users\86135\Desktop\WearableGasDetect\MainBody_CH32V307\MainBody_CH32V307\Gui\lvgl\src\lv_themes" -I"C:\Users\86135\Desktop\WearableGasDetect\MainBody_CH32V307\MainBody_CH32V307\Gui\lvgl\src\lv_widgets" -I"C:\Users\86135\Desktop\WearableGasDetect\MainBody_CH32V307\MainBody_CH32V307\Core" -I"C:\Users\86135\Desktop\WearableGasDetect\MainBody_CH32V307\MainBody_CH32V307\User" -I"C:\Users\86135\Desktop\WearableGasDetect\MainBody_CH32V307\MainBody_CH32V307\Peripheral\inc" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

