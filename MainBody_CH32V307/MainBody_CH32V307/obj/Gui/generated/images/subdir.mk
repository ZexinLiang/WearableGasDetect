################################################################################
# MRS Version: 1.9.2
# 自动生成的文件。不要编辑！
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Gui/generated/images/_1_alpha_320x240.c \
../Gui/generated/images/_2_alpha_100x100.c \
../Gui/generated/images/_58DC9A2F81E0F053C85B9185A7294362_alpha_213x102.c \
../Gui/generated/images/_C0C04F424616476844A271F0D7E2BB87_alpha_143x76.c \
../Gui/generated/images/_wch_alpha_143x76.c \
../Gui/generated/images/screen_1_animimg_12.c \
../Gui/generated/images/screen_1_animimg_1wch.c 

OBJS += \
./Gui/generated/images/_1_alpha_320x240.o \
./Gui/generated/images/_2_alpha_100x100.o \
./Gui/generated/images/_58DC9A2F81E0F053C85B9185A7294362_alpha_213x102.o \
./Gui/generated/images/_C0C04F424616476844A271F0D7E2BB87_alpha_143x76.o \
./Gui/generated/images/_wch_alpha_143x76.o \
./Gui/generated/images/screen_1_animimg_12.o \
./Gui/generated/images/screen_1_animimg_1wch.o 

C_DEPS += \
./Gui/generated/images/_1_alpha_320x240.d \
./Gui/generated/images/_2_alpha_100x100.d \
./Gui/generated/images/_58DC9A2F81E0F053C85B9185A7294362_alpha_213x102.d \
./Gui/generated/images/_C0C04F424616476844A271F0D7E2BB87_alpha_143x76.d \
./Gui/generated/images/_wch_alpha_143x76.d \
./Gui/generated/images/screen_1_animimg_12.d \
./Gui/generated/images/screen_1_animimg_1wch.d 


# Each subdirectory must supply rules for building sources it contributes
Gui/generated/images/%.o: ../Gui/generated/images/%.c
	@	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"C:\Users\86135\Desktop\WearableGasDetect\MainBody_CH32V307\MainBody_CH32V307\Debug" -I"C:\Users\86135\Desktop\WearableGasDetect\MainBody_CH32V307\MainBody_CH32V307\Gui" -I"C:\Users\86135\Desktop\WearableGasDetect\MainBody_CH32V307\MainBody_CH32V307\Core" -I"C:\Users\86135\Desktop\WearableGasDetect\MainBody_CH32V307\MainBody_CH32V307\User" -I"C:\Users\86135\Desktop\WearableGasDetect\MainBody_CH32V307\MainBody_CH32V307\Peripheral\inc" -I"C:\Users\86135\Desktop\WearableGasDetect\MainBody_CH32V307\MainBody_CH32V307\Gui\demos" -I"C:\Users\86135\Desktop\WearableGasDetect\MainBody_CH32V307\MainBody_CH32V307\Gui\demos\widgets" -I"C:\Users\86135\Desktop\WearableGasDetect\MainBody_CH32V307\MainBody_CH32V307\Gui\src" -I"C:\Users\86135\Desktop\WearableGasDetect\MainBody_CH32V307\MainBody_CH32V307\Gui\porting" -I"C:\Users\86135\Desktop\WearableGasDetect\MainBody_CH32V307\MainBody_CH32V307\Gui\custom" -I"C:\Users\86135\Desktop\WearableGasDetect\MainBody_CH32V307\MainBody_CH32V307\Gui\generated" -I"C:\Users\86135\Desktop\WearableGasDetect\MainBody_CH32V307\MainBody_CH32V307\Gui\generated\guider_customer_fonts" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

