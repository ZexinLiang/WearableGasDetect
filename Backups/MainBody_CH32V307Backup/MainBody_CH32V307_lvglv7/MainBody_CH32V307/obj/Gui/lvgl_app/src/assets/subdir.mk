################################################################################
# MRS Version: 1.9.2
# 自动生成的文件。不要编辑！
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Gui/lvgl_app/src/assets/img_cogwheel_alpha16.c \
../Gui/lvgl_app/src/assets/img_cogwheel_argb.c \
../Gui/lvgl_app/src/assets/img_cogwheel_chroma_keyed.c \
../Gui/lvgl_app/src/assets/img_cogwheel_indexed16.c \
../Gui/lvgl_app/src/assets/img_cogwheel_rgb.c \
../Gui/lvgl_app/src/assets/img_hand.c \
../Gui/lvgl_app/src/assets/lv_font_montserrat_12_compr_az.c \
../Gui/lvgl_app/src/assets/lv_font_montserrat_16_compr_az.c \
../Gui/lvgl_app/src/assets/lv_font_montserrat_28_compr_az.c 

OBJS += \
./Gui/lvgl_app/src/assets/img_cogwheel_alpha16.o \
./Gui/lvgl_app/src/assets/img_cogwheel_argb.o \
./Gui/lvgl_app/src/assets/img_cogwheel_chroma_keyed.o \
./Gui/lvgl_app/src/assets/img_cogwheel_indexed16.o \
./Gui/lvgl_app/src/assets/img_cogwheel_rgb.o \
./Gui/lvgl_app/src/assets/img_hand.o \
./Gui/lvgl_app/src/assets/lv_font_montserrat_12_compr_az.o \
./Gui/lvgl_app/src/assets/lv_font_montserrat_16_compr_az.o \
./Gui/lvgl_app/src/assets/lv_font_montserrat_28_compr_az.o 

C_DEPS += \
./Gui/lvgl_app/src/assets/img_cogwheel_alpha16.d \
./Gui/lvgl_app/src/assets/img_cogwheel_argb.d \
./Gui/lvgl_app/src/assets/img_cogwheel_chroma_keyed.d \
./Gui/lvgl_app/src/assets/img_cogwheel_indexed16.d \
./Gui/lvgl_app/src/assets/img_cogwheel_rgb.d \
./Gui/lvgl_app/src/assets/img_hand.d \
./Gui/lvgl_app/src/assets/lv_font_montserrat_12_compr_az.d \
./Gui/lvgl_app/src/assets/lv_font_montserrat_16_compr_az.d \
./Gui/lvgl_app/src/assets/lv_font_montserrat_28_compr_az.d 


# Each subdirectory must supply rules for building sources it contributes
Gui/lvgl_app/src/assets/%.o: ../Gui/lvgl_app/src/assets/%.c
	@	@	riscv-none-elf-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"C:\Users\86135\Desktop\WearableGasDetect\MainBody_CH32V307_lvglv7\MainBody_CH32V307\Debug" -I"C:\Users\86135\Desktop\WearableGasDetect\MainBody_CH32V307_lvglv7\MainBody_CH32V307\Gui" -I"C:\Users\86135\Desktop\WearableGasDetect\MainBody_CH32V307_lvglv7\MainBody_CH32V307\Gui\lvgl" -I"C:\Users\86135\Desktop\WearableGasDetect\MainBody_CH32V307_lvglv7\MainBody_CH32V307\Gui\lvgl_app\src\lv_demo_widgets" -I"C:\Users\86135\Desktop\WearableGasDetect\MainBody_CH32V307_lvglv7\MainBody_CH32V307\Gui\lvgl_app" -I"C:\Users\86135\Desktop\WearableGasDetect\MainBody_CH32V307_lvglv7\MainBody_CH32V307\Gui\lvgl\examples\porting" -I"C:\Users\86135\Desktop\WearableGasDetect\MainBody_CH32V307_lvglv7\MainBody_CH32V307\Gui\lvgl\src\lv_core" -I"C:\Users\86135\Desktop\WearableGasDetect\MainBody_CH32V307_lvglv7\MainBody_CH32V307\Gui\lvgl\src\lv_draw" -I"C:\Users\86135\Desktop\WearableGasDetect\MainBody_CH32V307_lvglv7\MainBody_CH32V307\Gui\lvgl\src\lv_font" -I"C:\Users\86135\Desktop\WearableGasDetect\MainBody_CH32V307_lvglv7\MainBody_CH32V307\Gui\lvgl\src\lv_gpu" -I"C:\Users\86135\Desktop\WearableGasDetect\MainBody_CH32V307_lvglv7\MainBody_CH32V307\Gui\lvgl\src\lv_hal" -I"C:\Users\86135\Desktop\WearableGasDetect\MainBody_CH32V307_lvglv7\MainBody_CH32V307\Gui\lvgl\src\lv_misc" -I"C:\Users\86135\Desktop\WearableGasDetect\MainBody_CH32V307_lvglv7\MainBody_CH32V307\Gui\lvgl\src\lv_themes" -I"C:\Users\86135\Desktop\WearableGasDetect\MainBody_CH32V307_lvglv7\MainBody_CH32V307\Gui\lvgl\src\lv_widgets" -I"C:\Users\86135\Desktop\WearableGasDetect\MainBody_CH32V307_lvglv7\MainBody_CH32V307\Core" -I"C:\Users\86135\Desktop\WearableGasDetect\MainBody_CH32V307_lvglv7\MainBody_CH32V307\User" -I"C:\Users\86135\Desktop\WearableGasDetect\MainBody_CH32V307_lvglv7\MainBody_CH32V307\Peripheral\inc" -I"C:\Users\86135\Desktop\WearableGasDetect\MainBody_CH32V307_lvglv7\MainBody_CH32V307\Gui\my_design\generated" -I"C:\Users\86135\Desktop\WearableGasDetect\MainBody_CH32V307_lvglv7\MainBody_CH32V307\Gui\my_design\generated\guider_customer_fonts" -I"C:\Users\86135\Desktop\WearableGasDetect\MainBody_CH32V307_lvglv7\MainBody_CH32V307\Gui\my_design\custom" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

