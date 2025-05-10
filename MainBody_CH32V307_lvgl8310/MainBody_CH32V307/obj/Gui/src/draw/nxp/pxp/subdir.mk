################################################################################
# MRS Version: 2.1.0
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Gui/src/draw/nxp/pxp/lv_draw_pxp.c \
../Gui/src/draw/nxp/pxp/lv_draw_pxp_blend.c \
../Gui/src/draw/nxp/pxp/lv_gpu_nxp_pxp.c \
../Gui/src/draw/nxp/pxp/lv_gpu_nxp_pxp_osa.c 

C_DEPS += \
./Gui/src/draw/nxp/pxp/lv_draw_pxp.d \
./Gui/src/draw/nxp/pxp/lv_draw_pxp_blend.d \
./Gui/src/draw/nxp/pxp/lv_gpu_nxp_pxp.d \
./Gui/src/draw/nxp/pxp/lv_gpu_nxp_pxp_osa.d 

OBJS += \
./Gui/src/draw/nxp/pxp/lv_draw_pxp.o \
./Gui/src/draw/nxp/pxp/lv_draw_pxp_blend.o \
./Gui/src/draw/nxp/pxp/lv_gpu_nxp_pxp.o \
./Gui/src/draw/nxp/pxp/lv_gpu_nxp_pxp_osa.o 



# Each subdirectory must supply rules for building sources it contributes
Gui/src/draw/nxp/pxp/%.o: ../Gui/src/draw/nxp/pxp/%.c
	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -fmax-errors=20 -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized -g -I"c:/Users/86135/Desktop/WearableGasDetect/MainBody_CH32V307_lvgl8310/MainBody_CH32V307/Debug" -I"c:/Users/86135/Desktop/WearableGasDetect/MainBody_CH32V307_lvgl8310/MainBody_CH32V307/Gui" -I"c:/Users/86135/Desktop/WearableGasDetect/MainBody_CH32V307_lvgl8310/MainBody_CH32V307/Core" -I"c:/Users/86135/Desktop/WearableGasDetect/MainBody_CH32V307_lvgl8310/MainBody_CH32V307/User" -I"c:/Users/86135/Desktop/WearableGasDetect/MainBody_CH32V307_lvgl8310/MainBody_CH32V307/Peripheral/inc" -I"c:/Users/86135/Desktop/WearableGasDetect/MainBody_CH32V307_lvgl8310/MainBody_CH32V307/Gui/custom" -I"c:/Users/86135/Desktop/WearableGasDetect/MainBody_CH32V307_lvgl8310/MainBody_CH32V307/Gui/generated" -I"c:/Users/86135/Desktop/WearableGasDetect/MainBody_CH32V307_lvgl8310/MainBody_CH32V307/Gui/generated/guider_customer_fonts" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
