################################################################################
# MRS Version: 2.1.0
# Automatically-generated file. Do not edit!
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

C_DEPS += \
./Gui/src/draw/nxp/vglite/lv_draw_vglite.d \
./Gui/src/draw/nxp/vglite/lv_draw_vglite_arc.d \
./Gui/src/draw/nxp/vglite/lv_draw_vglite_blend.d \
./Gui/src/draw/nxp/vglite/lv_draw_vglite_line.d \
./Gui/src/draw/nxp/vglite/lv_draw_vglite_rect.d \
./Gui/src/draw/nxp/vglite/lv_vglite_buf.d \
./Gui/src/draw/nxp/vglite/lv_vglite_utils.d 

OBJS += \
./Gui/src/draw/nxp/vglite/lv_draw_vglite.o \
./Gui/src/draw/nxp/vglite/lv_draw_vglite_arc.o \
./Gui/src/draw/nxp/vglite/lv_draw_vglite_blend.o \
./Gui/src/draw/nxp/vglite/lv_draw_vglite_line.o \
./Gui/src/draw/nxp/vglite/lv_draw_vglite_rect.o \
./Gui/src/draw/nxp/vglite/lv_vglite_buf.o \
./Gui/src/draw/nxp/vglite/lv_vglite_utils.o 



# Each subdirectory must supply rules for building sources it contributes
Gui/src/draw/nxp/vglite/%.o: ../Gui/src/draw/nxp/vglite/%.c
	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -fmax-errors=20 -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized -g -I"c:/Users/86135/Desktop/WearableGasDetect/MainBody_CH32V307_lvgl8310/MainBody_CH32V307/Debug" -I"c:/Users/86135/Desktop/WearableGasDetect/MainBody_CH32V307_lvgl8310/MainBody_CH32V307/Gui" -I"c:/Users/86135/Desktop/WearableGasDetect/MainBody_CH32V307_lvgl8310/MainBody_CH32V307/Core" -I"c:/Users/86135/Desktop/WearableGasDetect/MainBody_CH32V307_lvgl8310/MainBody_CH32V307/User" -I"c:/Users/86135/Desktop/WearableGasDetect/MainBody_CH32V307_lvgl8310/MainBody_CH32V307/Peripheral/inc" -I"c:/Users/86135/Desktop/WearableGasDetect/MainBody_CH32V307_lvgl8310/MainBody_CH32V307/Gui/custom" -I"c:/Users/86135/Desktop/WearableGasDetect/MainBody_CH32V307_lvgl8310/MainBody_CH32V307/Gui/generated" -I"c:/Users/86135/Desktop/WearableGasDetect/MainBody_CH32V307_lvgl8310/MainBody_CH32V307/Gui/generated/guider_customer_fonts" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
