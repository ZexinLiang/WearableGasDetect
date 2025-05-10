################################################################################
# MRS Version: 2.1.0
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Gui/examples/widgets/menu/lv_example_menu_1.c \
../Gui/examples/widgets/menu/lv_example_menu_2.c \
../Gui/examples/widgets/menu/lv_example_menu_3.c \
../Gui/examples/widgets/menu/lv_example_menu_4.c \
../Gui/examples/widgets/menu/lv_example_menu_5.c 

C_DEPS += \
./Gui/examples/widgets/menu/lv_example_menu_1.d \
./Gui/examples/widgets/menu/lv_example_menu_2.d \
./Gui/examples/widgets/menu/lv_example_menu_3.d \
./Gui/examples/widgets/menu/lv_example_menu_4.d \
./Gui/examples/widgets/menu/lv_example_menu_5.d 

OBJS += \
./Gui/examples/widgets/menu/lv_example_menu_1.o \
./Gui/examples/widgets/menu/lv_example_menu_2.o \
./Gui/examples/widgets/menu/lv_example_menu_3.o \
./Gui/examples/widgets/menu/lv_example_menu_4.o \
./Gui/examples/widgets/menu/lv_example_menu_5.o 



# Each subdirectory must supply rules for building sources it contributes
Gui/examples/widgets/menu/%.o: ../Gui/examples/widgets/menu/%.c
	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -fmax-errors=20 -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized -g -I"c:/Users/86135/Desktop/WearableGasDetect/MainBody_CH32V307_lvgl8310/MainBody_CH32V307/Debug" -I"c:/Users/86135/Desktop/WearableGasDetect/MainBody_CH32V307_lvgl8310/MainBody_CH32V307/Gui" -I"c:/Users/86135/Desktop/WearableGasDetect/MainBody_CH32V307_lvgl8310/MainBody_CH32V307/Core" -I"c:/Users/86135/Desktop/WearableGasDetect/MainBody_CH32V307_lvgl8310/MainBody_CH32V307/User" -I"c:/Users/86135/Desktop/WearableGasDetect/MainBody_CH32V307_lvgl8310/MainBody_CH32V307/Peripheral/inc" -I"c:/Users/86135/Desktop/WearableGasDetect/MainBody_CH32V307_lvgl8310/MainBody_CH32V307/Gui/custom" -I"c:/Users/86135/Desktop/WearableGasDetect/MainBody_CH32V307_lvgl8310/MainBody_CH32V307/Gui/generated" -I"c:/Users/86135/Desktop/WearableGasDetect/MainBody_CH32V307_lvgl8310/MainBody_CH32V307/Gui/generated/guider_customer_fonts" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
