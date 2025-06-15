################################################################################
# MRS Version: 1.9.2
# 自动生成的文件。不要编辑！
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Gui/my_design/generated/events_init.c \
../Gui/my_design/generated/gui_guider.c \
../Gui/my_design/generated/setup_scr_screen.c \
../Gui/my_design/generated/setup_scr_screen_1.c \
../Gui/my_design/generated/setup_scr_screen_2.c \
../Gui/my_design/generated/setup_scr_screen_3.c 

OBJS += \
./Gui/my_design/generated/events_init.o \
./Gui/my_design/generated/gui_guider.o \
./Gui/my_design/generated/setup_scr_screen.o \
./Gui/my_design/generated/setup_scr_screen_1.o \
./Gui/my_design/generated/setup_scr_screen_2.o \
./Gui/my_design/generated/setup_scr_screen_3.o 

C_DEPS += \
./Gui/my_design/generated/events_init.d \
./Gui/my_design/generated/gui_guider.d \
./Gui/my_design/generated/setup_scr_screen.d \
./Gui/my_design/generated/setup_scr_screen_1.d \
./Gui/my_design/generated/setup_scr_screen_2.d \
./Gui/my_design/generated/setup_scr_screen_3.d 


# Each subdirectory must supply rules for building sources it contributes
Gui/my_design/generated/%.o: ../Gui/my_design/generated/%.c
	@	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"C:\Users\86135\Desktop\WearableGasDetect\MainBody_CH32V307_lvglv7\MainBody_CH32V307\Debug" -I"C:\Users\86135\Desktop\WearableGasDetect\MainBody_CH32V307_lvglv7\MainBody_CH32V307\Gui" -I"C:\Users\86135\Desktop\WearableGasDetect\MainBody_CH32V307_lvglv7\MainBody_CH32V307\Gui\lvgl" -I"C:\Users\86135\Desktop\WearableGasDetect\MainBody_CH32V307_lvglv7\MainBody_CH32V307\Gui\lvgl_app\src\lv_demo_widgets" -I"C:\Users\86135\Desktop\WearableGasDetect\MainBody_CH32V307_lvglv7\MainBody_CH32V307\Gui\lvgl_app" -I"C:\Users\86135\Desktop\WearableGasDetect\MainBody_CH32V307_lvglv7\MainBody_CH32V307\Gui\lvgl\examples\porting" -I"C:\Users\86135\Desktop\WearableGasDetect\MainBody_CH32V307_lvglv7\MainBody_CH32V307\Gui\lvgl\src\lv_core" -I"C:\Users\86135\Desktop\WearableGasDetect\MainBody_CH32V307_lvglv7\MainBody_CH32V307\Gui\lvgl\src\lv_draw" -I"C:\Users\86135\Desktop\WearableGasDetect\MainBody_CH32V307_lvglv7\MainBody_CH32V307\Gui\lvgl\src\lv_font" -I"C:\Users\86135\Desktop\WearableGasDetect\MainBody_CH32V307_lvglv7\MainBody_CH32V307\Gui\lvgl\src\lv_gpu" -I"C:\Users\86135\Desktop\WearableGasDetect\MainBody_CH32V307_lvglv7\MainBody_CH32V307\Gui\lvgl\src\lv_hal" -I"C:\Users\86135\Desktop\WearableGasDetect\MainBody_CH32V307_lvglv7\MainBody_CH32V307\Gui\lvgl\src\lv_misc" -I"C:\Users\86135\Desktop\WearableGasDetect\MainBody_CH32V307_lvglv7\MainBody_CH32V307\Gui\lvgl\src\lv_themes" -I"C:\Users\86135\Desktop\WearableGasDetect\MainBody_CH32V307_lvglv7\MainBody_CH32V307\Gui\lvgl\src\lv_widgets" -I"C:\Users\86135\Desktop\WearableGasDetect\MainBody_CH32V307_lvglv7\MainBody_CH32V307\Core" -I"C:\Users\86135\Desktop\WearableGasDetect\MainBody_CH32V307_lvglv7\MainBody_CH32V307\User" -I"C:\Users\86135\Desktop\WearableGasDetect\MainBody_CH32V307_lvglv7\MainBody_CH32V307\Peripheral\inc" -I"C:\Users\86135\Desktop\WearableGasDetect\MainBody_CH32V307_lvglv7\MainBody_CH32V307\Gui\my_design\generated" -I"C:\Users\86135\Desktop\WearableGasDetect\MainBody_CH32V307_lvglv7\MainBody_CH32V307\Gui\my_design\generated\guider_customer_fonts" -I"C:\Users\86135\Desktop\WearableGasDetect\MainBody_CH32V307_lvglv7\MainBody_CH32V307\Gui\my_design\custom" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

