################################################################################
# MRS Version: 1.9.2
# 自动生成的文件。不要编辑！
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Gui/my_design/generated/events_init.c \
../Gui/my_design/generated/gui_guider.c \
../Gui/my_design/generated/setup_scr_screen_alarmst.c \
../Gui/my_design/generated/setup_scr_screen_devicest.c \
../Gui/my_design/generated/setup_scr_screen_network.c \
../Gui/my_design/generated/setup_scr_screen_none.c \
../Gui/my_design/generated/setup_scr_screen_pwon.c \
../Gui/my_design/generated/setup_scr_screen_rtdata.c \
../Gui/my_design/generated/setup_scr_screen_settings.c \
../Gui/my_design/generated/setup_scr_screen_sub_device.c 

OBJS += \
./Gui/my_design/generated/events_init.o \
./Gui/my_design/generated/gui_guider.o \
./Gui/my_design/generated/setup_scr_screen_alarmst.o \
./Gui/my_design/generated/setup_scr_screen_devicest.o \
./Gui/my_design/generated/setup_scr_screen_network.o \
./Gui/my_design/generated/setup_scr_screen_none.o \
./Gui/my_design/generated/setup_scr_screen_pwon.o \
./Gui/my_design/generated/setup_scr_screen_rtdata.o \
./Gui/my_design/generated/setup_scr_screen_settings.o \
./Gui/my_design/generated/setup_scr_screen_sub_device.o 

C_DEPS += \
./Gui/my_design/generated/events_init.d \
./Gui/my_design/generated/gui_guider.d \
./Gui/my_design/generated/setup_scr_screen_alarmst.d \
./Gui/my_design/generated/setup_scr_screen_devicest.d \
./Gui/my_design/generated/setup_scr_screen_network.d \
./Gui/my_design/generated/setup_scr_screen_none.d \
./Gui/my_design/generated/setup_scr_screen_pwon.d \
./Gui/my_design/generated/setup_scr_screen_rtdata.d \
./Gui/my_design/generated/setup_scr_screen_settings.d \
./Gui/my_design/generated/setup_scr_screen_sub_device.d 


# Each subdirectory must supply rules for building sources it contributes
Gui/my_design/generated/%.o: ../Gui/my_design/generated/%.c
	@	@	riscv-none-elf-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"C:\Users\86135\Desktop\WearableGasDetect\MainBody_CH32V307_lvglv7\MainBody_CH32V307\Debug" -I"C:\Users\86135\Desktop\WearableGasDetect\MainBody_CH32V307_lvglv7\MainBody_CH32V307\Gui" -I"C:\Users\86135\Desktop\WearableGasDetect\MainBody_CH32V307_lvglv7\MainBody_CH32V307\Gui\lvgl" -I"C:\Users\86135\Desktop\WearableGasDetect\MainBody_CH32V307_lvglv7\MainBody_CH32V307\Gui\lvgl_app\src\lv_demo_widgets" -I"C:\Users\86135\Desktop\WearableGasDetect\MainBody_CH32V307_lvglv7\MainBody_CH32V307\Gui\lvgl_app" -I"C:\Users\86135\Desktop\WearableGasDetect\MainBody_CH32V307_lvglv7\MainBody_CH32V307\Gui\lvgl\examples\porting" -I"C:\Users\86135\Desktop\WearableGasDetect\MainBody_CH32V307_lvglv7\MainBody_CH32V307\Gui\lvgl\src\lv_core" -I"C:\Users\86135\Desktop\WearableGasDetect\MainBody_CH32V307_lvglv7\MainBody_CH32V307\Gui\lvgl\src\lv_draw" -I"C:\Users\86135\Desktop\WearableGasDetect\MainBody_CH32V307_lvglv7\MainBody_CH32V307\Gui\lvgl\src\lv_font" -I"C:\Users\86135\Desktop\WearableGasDetect\MainBody_CH32V307_lvglv7\MainBody_CH32V307\Gui\lvgl\src\lv_gpu" -I"C:\Users\86135\Desktop\WearableGasDetect\MainBody_CH32V307_lvglv7\MainBody_CH32V307\Gui\lvgl\src\lv_hal" -I"C:\Users\86135\Desktop\WearableGasDetect\MainBody_CH32V307_lvglv7\MainBody_CH32V307\Gui\lvgl\src\lv_misc" -I"C:\Users\86135\Desktop\WearableGasDetect\MainBody_CH32V307_lvglv7\MainBody_CH32V307\Gui\lvgl\src\lv_themes" -I"C:\Users\86135\Desktop\WearableGasDetect\MainBody_CH32V307_lvglv7\MainBody_CH32V307\Gui\lvgl\src\lv_widgets" -I"C:\Users\86135\Desktop\WearableGasDetect\MainBody_CH32V307_lvglv7\MainBody_CH32V307\Core" -I"C:\Users\86135\Desktop\WearableGasDetect\MainBody_CH32V307_lvglv7\MainBody_CH32V307\User" -I"C:\Users\86135\Desktop\WearableGasDetect\MainBody_CH32V307_lvglv7\MainBody_CH32V307\Peripheral\inc" -I"C:\Users\86135\Desktop\WearableGasDetect\MainBody_CH32V307_lvglv7\MainBody_CH32V307\Gui\my_design\generated" -I"C:\Users\86135\Desktop\WearableGasDetect\MainBody_CH32V307_lvglv7\MainBody_CH32V307\Gui\my_design\generated\guider_customer_fonts" -I"C:\Users\86135\Desktop\WearableGasDetect\MainBody_CH32V307_lvglv7\MainBody_CH32V307\Gui\my_design\custom" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

