################################################################################
# MRS Version: 1.9.2
# 自动生成的文件。不要编辑！
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Gui/src/draw/nxp/vglite/lv_draw_vglite.c \
../Gui/src/draw/nxp/vglite/lv_draw_vglite_arc.c \
../Gui/src/draw/nxp/vglite/lv_draw_vglite_blend.c \
../Gui/src/draw/nxp/vglite/lv_draw_vglite_line.c \
../Gui/src/draw/nxp/vglite/lv_draw_vglite_rect.c \
../Gui/src/draw/nxp/vglite/lv_vglite_buf.c \
../Gui/src/draw/nxp/vglite/lv_vglite_utils.c 

OBJS += \
./Gui/src/draw/nxp/vglite/lv_draw_vglite.o \
./Gui/src/draw/nxp/vglite/lv_draw_vglite_arc.o \
./Gui/src/draw/nxp/vglite/lv_draw_vglite_blend.o \
./Gui/src/draw/nxp/vglite/lv_draw_vglite_line.o \
./Gui/src/draw/nxp/vglite/lv_draw_vglite_rect.o \
./Gui/src/draw/nxp/vglite/lv_vglite_buf.o \
./Gui/src/draw/nxp/vglite/lv_vglite_utils.o 

C_DEPS += \
./Gui/src/draw/nxp/vglite/lv_draw_vglite.d \
./Gui/src/draw/nxp/vglite/lv_draw_vglite_arc.d \
./Gui/src/draw/nxp/vglite/lv_draw_vglite_blend.d \
./Gui/src/draw/nxp/vglite/lv_draw_vglite_line.d \
./Gui/src/draw/nxp/vglite/lv_draw_vglite_rect.d \
./Gui/src/draw/nxp/vglite/lv_vglite_buf.d \
./Gui/src/draw/nxp/vglite/lv_vglite_utils.d 


# Each subdirectory must supply rules for building sources it contributes
Gui/src/draw/nxp/vglite/%.o: ../Gui/src/draw/nxp/vglite/%.c
	@	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"C:\Users\86135\Desktop\WearableGasDetect\MainBody_CH32V307\MainBody_CH32V307\Debug" -I"C:\Users\86135\Desktop\WearableGasDetect\MainBody_CH32V307\MainBody_CH32V307\Gui" -I"C:\Users\86135\Desktop\WearableGasDetect\MainBody_CH32V307\MainBody_CH32V307\Core" -I"C:\Users\86135\Desktop\WearableGasDetect\MainBody_CH32V307\MainBody_CH32V307\User" -I"C:\Users\86135\Desktop\WearableGasDetect\MainBody_CH32V307\MainBody_CH32V307\Peripheral\inc" -I"C:\Users\86135\Desktop\WearableGasDetect\MainBody_CH32V307\MainBody_CH32V307\Gui\demos" -I"C:\Users\86135\Desktop\WearableGasDetect\MainBody_CH32V307\MainBody_CH32V307\Gui\demos\widgets" -I"C:\Users\86135\Desktop\WearableGasDetect\MainBody_CH32V307\MainBody_CH32V307\Gui\src" -I"C:\Users\86135\Desktop\WearableGasDetect\MainBody_CH32V307\MainBody_CH32V307\Gui\porting" -I"C:\Users\86135\Desktop\WearableGasDetect\MainBody_CH32V307\MainBody_CH32V307\Gui\custom" -I"C:\Users\86135\Desktop\WearableGasDetect\MainBody_CH32V307\MainBody_CH32V307\Gui\generated" -I"C:\Users\86135\Desktop\WearableGasDetect\MainBody_CH32V307\MainBody_CH32V307\Gui\generated\guider_customer_fonts" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

