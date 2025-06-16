################################################################################
# MRS Version: 2.1.0
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Gui/generated/guider_fonts/lv_font_montserratMedium_12.c \
../Gui/generated/guider_fonts/lv_font_montserratMedium_17.c \
../Gui/generated/guider_fonts/lv_font_montserratMedium_32.c \
../Gui/generated/guider_fonts/lv_font_montserratMedium_8.c 

C_DEPS += \
./Gui/generated/guider_fonts/lv_font_montserratMedium_12.d \
./Gui/generated/guider_fonts/lv_font_montserratMedium_17.d \
./Gui/generated/guider_fonts/lv_font_montserratMedium_32.d \
./Gui/generated/guider_fonts/lv_font_montserratMedium_8.d 

OBJS += \
./Gui/generated/guider_fonts/lv_font_montserratMedium_12.o \
./Gui/generated/guider_fonts/lv_font_montserratMedium_17.o \
./Gui/generated/guider_fonts/lv_font_montserratMedium_32.o \
./Gui/generated/guider_fonts/lv_font_montserratMedium_8.o 



# Each subdirectory must supply rules for building sources it contributes
Gui/generated/guider_fonts/%.o: ../Gui/generated/guider_fonts/%.c
	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -fmax-errors=20 -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized -g -I"c:/Users/86135/Desktop/WearableGasDetect/MainBody_CH32V307Backup/MainBody_CH32V307/Debug" -I"c:/Users/86135/Desktop/WearableGasDetect/MainBody_CH32V307Backup/MainBody_CH32V307/Gui" -I"c:/Users/86135/Desktop/WearableGasDetect/MainBody_CH32V307Backup/MainBody_CH32V307/Gui/lvgl" -I"c:/Users/86135/Desktop/WearableGasDetect/MainBody_CH32V307Backup/MainBody_CH32V307/Gui/lvgl_app/src/lv_demo_widgets" -I"c:/Users/86135/Desktop/WearableGasDetect/MainBody_CH32V307Backup/MainBody_CH32V307/Gui/lvgl_app" -I"c:/Users/86135/Desktop/WearableGasDetect/MainBody_CH32V307Backup/MainBody_CH32V307/Gui/lvgl/examples/porting" -I"c:/Users/86135/Desktop/WearableGasDetect/MainBody_CH32V307Backup/MainBody_CH32V307/Gui/lvgl/src/lv_core" -I"c:/Users/86135/Desktop/WearableGasDetect/MainBody_CH32V307Backup/MainBody_CH32V307/Gui/lvgl/src/lv_draw" -I"c:/Users/86135/Desktop/WearableGasDetect/MainBody_CH32V307Backup/MainBody_CH32V307/Gui/lvgl/src/lv_font" -I"c:/Users/86135/Desktop/WearableGasDetect/MainBody_CH32V307Backup/MainBody_CH32V307/Gui/lvgl/src/lv_gpu" -I"c:/Users/86135/Desktop/WearableGasDetect/MainBody_CH32V307Backup/MainBody_CH32V307/Gui/lvgl/src/lv_hal" -I"c:/Users/86135/Desktop/WearableGasDetect/MainBody_CH32V307Backup/MainBody_CH32V307/Gui/lvgl/src/lv_misc" -I"c:/Users/86135/Desktop/WearableGasDetect/MainBody_CH32V307Backup/MainBody_CH32V307/Gui/lvgl/src/lv_themes" -I"c:/Users/86135/Desktop/WearableGasDetect/MainBody_CH32V307Backup/MainBody_CH32V307/Gui/lvgl/src/lv_widgets" -I"c:/Users/86135/Desktop/WearableGasDetect/MainBody_CH32V307Backup/MainBody_CH32V307/Core" -I"c:/Users/86135/Desktop/WearableGasDetect/MainBody_CH32V307Backup/MainBody_CH32V307/User" -I"c:/Users/86135/Desktop/WearableGasDetect/MainBody_CH32V307Backup/MainBody_CH32V307/Peripheral/inc" -I"c:/Users/86135/Desktop/WearableGasDetect/MainBody_CH32V307Backup/MainBody_CH32V307/Gui/custom" -I"c:/Users/86135/Desktop/WearableGasDetect/MainBody_CH32V307Backup/MainBody_CH32V307/Gui/generated" -I"c:/Users/86135/Desktop/WearableGasDetect/MainBody_CH32V307Backup/MainBody_CH32V307/Gui/generated/guider_customer_fonts" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
