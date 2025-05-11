################################################################################
# MRS Version: 1.9.2
# �Զ����ɵ��ļ�����Ҫ�༭��
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Gui/lvgl/src/lv_themes/lv_theme.c \
../Gui/lvgl/src/lv_themes/lv_theme_empty.c \
../Gui/lvgl/src/lv_themes/lv_theme_material.c \
../Gui/lvgl/src/lv_themes/lv_theme_mono.c \
../Gui/lvgl/src/lv_themes/lv_theme_template.c 

OBJS += \
./Gui/lvgl/src/lv_themes/lv_theme.o \
./Gui/lvgl/src/lv_themes/lv_theme_empty.o \
./Gui/lvgl/src/lv_themes/lv_theme_material.o \
./Gui/lvgl/src/lv_themes/lv_theme_mono.o \
./Gui/lvgl/src/lv_themes/lv_theme_template.o 

C_DEPS += \
./Gui/lvgl/src/lv_themes/lv_theme.d \
./Gui/lvgl/src/lv_themes/lv_theme_empty.d \
./Gui/lvgl/src/lv_themes/lv_theme_material.d \
./Gui/lvgl/src/lv_themes/lv_theme_mono.d \
./Gui/lvgl/src/lv_themes/lv_theme_template.d 


# Each subdirectory must supply rules for building sources it contributes
Gui/lvgl/src/lv_themes/%.o: ../Gui/lvgl/src/lv_themes/%.c
	@	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"C:\Users\86135\Desktop\WearableGasDetect\MainBody_CH32V307_lvglv7\MainBody_CH32V307\Debug" -I"C:\Users\86135\Desktop\WearableGasDetect\MainBody_CH32V307_lvglv7\MainBody_CH32V307\Gui" -I"C:\Users\86135\Desktop\WearableGasDetect\MainBody_CH32V307_lvglv7\MainBody_CH32V307\Gui\lvgl" -I"C:\Users\86135\Desktop\WearableGasDetect\MainBody_CH32V307_lvglv7\MainBody_CH32V307\Gui\lvgl_app\src\lv_demo_widgets" -I"C:\Users\86135\Desktop\WearableGasDetect\MainBody_CH32V307_lvglv7\MainBody_CH32V307\Gui\lvgl_app" -I"C:\Users\86135\Desktop\WearableGasDetect\MainBody_CH32V307_lvglv7\MainBody_CH32V307\Gui\lvgl\examples\porting" -I"C:\Users\86135\Desktop\WearableGasDetect\MainBody_CH32V307_lvglv7\MainBody_CH32V307\Gui\lvgl\src\lv_core" -I"C:\Users\86135\Desktop\WearableGasDetect\MainBody_CH32V307_lvglv7\MainBody_CH32V307\Gui\lvgl\src\lv_draw" -I"C:\Users\86135\Desktop\WearableGasDetect\MainBody_CH32V307_lvglv7\MainBody_CH32V307\Gui\lvgl\src\lv_font" -I"C:\Users\86135\Desktop\WearableGasDetect\MainBody_CH32V307_lvglv7\MainBody_CH32V307\Gui\lvgl\src\lv_gpu" -I"C:\Users\86135\Desktop\WearableGasDetect\MainBody_CH32V307_lvglv7\MainBody_CH32V307\Gui\lvgl\src\lv_hal" -I"C:\Users\86135\Desktop\WearableGasDetect\MainBody_CH32V307_lvglv7\MainBody_CH32V307\Gui\lvgl\src\lv_misc" -I"C:\Users\86135\Desktop\WearableGasDetect\MainBody_CH32V307_lvglv7\MainBody_CH32V307\Gui\lvgl\src\lv_themes" -I"C:\Users\86135\Desktop\WearableGasDetect\MainBody_CH32V307_lvglv7\MainBody_CH32V307\Gui\lvgl\src\lv_widgets" -I"C:\Users\86135\Desktop\WearableGasDetect\MainBody_CH32V307_lvglv7\MainBody_CH32V307\Core" -I"C:\Users\86135\Desktop\WearableGasDetect\MainBody_CH32V307_lvglv7\MainBody_CH32V307\User" -I"C:\Users\86135\Desktop\WearableGasDetect\MainBody_CH32V307_lvglv7\MainBody_CH32V307\Peripheral\inc" -I"C:\Users\86135\Desktop\WearableGasDetect\MainBody_CH32V307_lvglv7\MainBody_CH32V307\Gui\my_design\custom" -I"C:\Users\86135\Desktop\WearableGasDetect\MainBody_CH32V307_lvglv7\MainBody_CH32V307\Gui\my_design\generated\guider_customer_fonts" -I"C:\Users\86135\Desktop\WearableGasDetect\MainBody_CH32V307_lvglv7\MainBody_CH32V307\Gui\my_design\generated" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

