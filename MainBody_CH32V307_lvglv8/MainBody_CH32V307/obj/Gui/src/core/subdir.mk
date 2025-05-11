################################################################################
# MRS Version: 1.9.2
# 自动生成的文件。不要编辑！
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Gui/src/core/lv_disp.c \
../Gui/src/core/lv_event.c \
../Gui/src/core/lv_group.c \
../Gui/src/core/lv_indev.c \
../Gui/src/core/lv_indev_scroll.c \
../Gui/src/core/lv_obj.c \
../Gui/src/core/lv_obj_class.c \
../Gui/src/core/lv_obj_draw.c \
../Gui/src/core/lv_obj_pos.c \
../Gui/src/core/lv_obj_scroll.c \
../Gui/src/core/lv_obj_style.c \
../Gui/src/core/lv_obj_style_gen.c \
../Gui/src/core/lv_obj_tree.c \
../Gui/src/core/lv_refr.c \
../Gui/src/core/lv_theme.c 

OBJS += \
./Gui/src/core/lv_disp.o \
./Gui/src/core/lv_event.o \
./Gui/src/core/lv_group.o \
./Gui/src/core/lv_indev.o \
./Gui/src/core/lv_indev_scroll.o \
./Gui/src/core/lv_obj.o \
./Gui/src/core/lv_obj_class.o \
./Gui/src/core/lv_obj_draw.o \
./Gui/src/core/lv_obj_pos.o \
./Gui/src/core/lv_obj_scroll.o \
./Gui/src/core/lv_obj_style.o \
./Gui/src/core/lv_obj_style_gen.o \
./Gui/src/core/lv_obj_tree.o \
./Gui/src/core/lv_refr.o \
./Gui/src/core/lv_theme.o 

C_DEPS += \
./Gui/src/core/lv_disp.d \
./Gui/src/core/lv_event.d \
./Gui/src/core/lv_group.d \
./Gui/src/core/lv_indev.d \
./Gui/src/core/lv_indev_scroll.d \
./Gui/src/core/lv_obj.d \
./Gui/src/core/lv_obj_class.d \
./Gui/src/core/lv_obj_draw.d \
./Gui/src/core/lv_obj_pos.d \
./Gui/src/core/lv_obj_scroll.d \
./Gui/src/core/lv_obj_style.d \
./Gui/src/core/lv_obj_style_gen.d \
./Gui/src/core/lv_obj_tree.d \
./Gui/src/core/lv_refr.d \
./Gui/src/core/lv_theme.d 


# Each subdirectory must supply rules for building sources it contributes
Gui/src/core/%.o: ../Gui/src/core/%.c
	@	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"C:\Users\86135\Desktop\WearableGasDetect\MainBody_CH32V307\MainBody_CH32V307\Debug" -I"C:\Users\86135\Desktop\WearableGasDetect\MainBody_CH32V307\MainBody_CH32V307\Gui" -I"C:\Users\86135\Desktop\WearableGasDetect\MainBody_CH32V307\MainBody_CH32V307\Core" -I"C:\Users\86135\Desktop\WearableGasDetect\MainBody_CH32V307\MainBody_CH32V307\User" -I"C:\Users\86135\Desktop\WearableGasDetect\MainBody_CH32V307\MainBody_CH32V307\Peripheral\inc" -I"C:\Users\86135\Desktop\WearableGasDetect\MainBody_CH32V307\MainBody_CH32V307\Gui\demos" -I"C:\Users\86135\Desktop\WearableGasDetect\MainBody_CH32V307\MainBody_CH32V307\Gui\demos\widgets" -I"C:\Users\86135\Desktop\WearableGasDetect\MainBody_CH32V307\MainBody_CH32V307\Gui\src" -I"C:\Users\86135\Desktop\WearableGasDetect\MainBody_CH32V307\MainBody_CH32V307\Gui\porting" -I"C:\Users\86135\Desktop\WearableGasDetect\MainBody_CH32V307\MainBody_CH32V307\Gui\custom" -I"C:\Users\86135\Desktop\WearableGasDetect\MainBody_CH32V307\MainBody_CH32V307\Gui\generated" -I"C:\Users\86135\Desktop\WearableGasDetect\MainBody_CH32V307\MainBody_CH32V307\Gui\generated\guider_customer_fonts" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

