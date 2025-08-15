################################################################################
# MRS Version: 1.9.2
# 自动生成的文件。不要编辑！
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Gui/lvgl/src/lv_misc/lv_anim.c \
../Gui/lvgl/src/lv_misc/lv_area.c \
../Gui/lvgl/src/lv_misc/lv_async.c \
../Gui/lvgl/src/lv_misc/lv_bidi.c \
../Gui/lvgl/src/lv_misc/lv_color.c \
../Gui/lvgl/src/lv_misc/lv_debug.c \
../Gui/lvgl/src/lv_misc/lv_fs.c \
../Gui/lvgl/src/lv_misc/lv_gc.c \
../Gui/lvgl/src/lv_misc/lv_ll.c \
../Gui/lvgl/src/lv_misc/lv_log.c \
../Gui/lvgl/src/lv_misc/lv_math.c \
../Gui/lvgl/src/lv_misc/lv_mem.c \
../Gui/lvgl/src/lv_misc/lv_printf.c \
../Gui/lvgl/src/lv_misc/lv_task.c \
../Gui/lvgl/src/lv_misc/lv_templ.c \
../Gui/lvgl/src/lv_misc/lv_txt.c \
../Gui/lvgl/src/lv_misc/lv_txt_ap.c \
../Gui/lvgl/src/lv_misc/lv_utils.c 

OBJS += \
./Gui/lvgl/src/lv_misc/lv_anim.o \
./Gui/lvgl/src/lv_misc/lv_area.o \
./Gui/lvgl/src/lv_misc/lv_async.o \
./Gui/lvgl/src/lv_misc/lv_bidi.o \
./Gui/lvgl/src/lv_misc/lv_color.o \
./Gui/lvgl/src/lv_misc/lv_debug.o \
./Gui/lvgl/src/lv_misc/lv_fs.o \
./Gui/lvgl/src/lv_misc/lv_gc.o \
./Gui/lvgl/src/lv_misc/lv_ll.o \
./Gui/lvgl/src/lv_misc/lv_log.o \
./Gui/lvgl/src/lv_misc/lv_math.o \
./Gui/lvgl/src/lv_misc/lv_mem.o \
./Gui/lvgl/src/lv_misc/lv_printf.o \
./Gui/lvgl/src/lv_misc/lv_task.o \
./Gui/lvgl/src/lv_misc/lv_templ.o \
./Gui/lvgl/src/lv_misc/lv_txt.o \
./Gui/lvgl/src/lv_misc/lv_txt_ap.o \
./Gui/lvgl/src/lv_misc/lv_utils.o 

C_DEPS += \
./Gui/lvgl/src/lv_misc/lv_anim.d \
./Gui/lvgl/src/lv_misc/lv_area.d \
./Gui/lvgl/src/lv_misc/lv_async.d \
./Gui/lvgl/src/lv_misc/lv_bidi.d \
./Gui/lvgl/src/lv_misc/lv_color.d \
./Gui/lvgl/src/lv_misc/lv_debug.d \
./Gui/lvgl/src/lv_misc/lv_fs.d \
./Gui/lvgl/src/lv_misc/lv_gc.d \
./Gui/lvgl/src/lv_misc/lv_ll.d \
./Gui/lvgl/src/lv_misc/lv_log.d \
./Gui/lvgl/src/lv_misc/lv_math.d \
./Gui/lvgl/src/lv_misc/lv_mem.d \
./Gui/lvgl/src/lv_misc/lv_printf.d \
./Gui/lvgl/src/lv_misc/lv_task.d \
./Gui/lvgl/src/lv_misc/lv_templ.d \
./Gui/lvgl/src/lv_misc/lv_txt.d \
./Gui/lvgl/src/lv_misc/lv_txt_ap.d \
./Gui/lvgl/src/lv_misc/lv_utils.d 


# Each subdirectory must supply rules for building sources it contributes
Gui/lvgl/src/lv_misc/%.o: ../Gui/lvgl/src/lv_misc/%.c
	@	@	riscv-none-elf-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"C:\Users\86135\Desktop\WearableGasDetect\MainBody_CH32V307_lvglv7\MainBody_CH32V307\Debug" -I"C:\Users\86135\Desktop\WearableGasDetect\MainBody_CH32V307_lvglv7\MainBody_CH32V307\Gui" -I"C:\Users\86135\Desktop\WearableGasDetect\MainBody_CH32V307_lvglv7\MainBody_CH32V307\Gui\lvgl" -I"C:\Users\86135\Desktop\WearableGasDetect\MainBody_CH32V307_lvglv7\MainBody_CH32V307\Gui\lvgl_app\src\lv_demo_widgets" -I"C:\Users\86135\Desktop\WearableGasDetect\MainBody_CH32V307_lvglv7\MainBody_CH32V307\Gui\lvgl_app" -I"C:\Users\86135\Desktop\WearableGasDetect\MainBody_CH32V307_lvglv7\MainBody_CH32V307\Gui\lvgl\examples\porting" -I"C:\Users\86135\Desktop\WearableGasDetect\MainBody_CH32V307_lvglv7\MainBody_CH32V307\Gui\lvgl\src\lv_core" -I"C:\Users\86135\Desktop\WearableGasDetect\MainBody_CH32V307_lvglv7\MainBody_CH32V307\Gui\lvgl\src\lv_draw" -I"C:\Users\86135\Desktop\WearableGasDetect\MainBody_CH32V307_lvglv7\MainBody_CH32V307\Gui\lvgl\src\lv_font" -I"C:\Users\86135\Desktop\WearableGasDetect\MainBody_CH32V307_lvglv7\MainBody_CH32V307\Gui\lvgl\src\lv_gpu" -I"C:\Users\86135\Desktop\WearableGasDetect\MainBody_CH32V307_lvglv7\MainBody_CH32V307\Gui\lvgl\src\lv_hal" -I"C:\Users\86135\Desktop\WearableGasDetect\MainBody_CH32V307_lvglv7\MainBody_CH32V307\Gui\lvgl\src\lv_misc" -I"C:\Users\86135\Desktop\WearableGasDetect\MainBody_CH32V307_lvglv7\MainBody_CH32V307\Gui\lvgl\src\lv_themes" -I"C:\Users\86135\Desktop\WearableGasDetect\MainBody_CH32V307_lvglv7\MainBody_CH32V307\Gui\lvgl\src\lv_widgets" -I"C:\Users\86135\Desktop\WearableGasDetect\MainBody_CH32V307_lvglv7\MainBody_CH32V307\Core" -I"C:\Users\86135\Desktop\WearableGasDetect\MainBody_CH32V307_lvglv7\MainBody_CH32V307\User" -I"C:\Users\86135\Desktop\WearableGasDetect\MainBody_CH32V307_lvglv7\MainBody_CH32V307\Peripheral\inc" -I"C:\Users\86135\Desktop\WearableGasDetect\MainBody_CH32V307_lvglv7\MainBody_CH32V307\Gui\my_design\generated" -I"C:\Users\86135\Desktop\WearableGasDetect\MainBody_CH32V307_lvglv7\MainBody_CH32V307\Gui\my_design\generated\guider_customer_fonts" -I"C:\Users\86135\Desktop\WearableGasDetect\MainBody_CH32V307_lvglv7\MainBody_CH32V307\Gui\my_design\custom" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

