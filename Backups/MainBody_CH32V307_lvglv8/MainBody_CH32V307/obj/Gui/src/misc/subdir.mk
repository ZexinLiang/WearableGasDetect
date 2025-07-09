################################################################################
# MRS Version: 1.9.2
# 自动生成的文件。不要编辑！
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Gui/src/misc/lv_anim.c \
../Gui/src/misc/lv_anim_timeline.c \
../Gui/src/misc/lv_area.c \
../Gui/src/misc/lv_async.c \
../Gui/src/misc/lv_bidi.c \
../Gui/src/misc/lv_color.c \
../Gui/src/misc/lv_fs.c \
../Gui/src/misc/lv_gc.c \
../Gui/src/misc/lv_ll.c \
../Gui/src/misc/lv_log.c \
../Gui/src/misc/lv_lru.c \
../Gui/src/misc/lv_math.c \
../Gui/src/misc/lv_mem.c \
../Gui/src/misc/lv_printf.c \
../Gui/src/misc/lv_style.c \
../Gui/src/misc/lv_style_gen.c \
../Gui/src/misc/lv_templ.c \
../Gui/src/misc/lv_timer.c \
../Gui/src/misc/lv_tlsf.c \
../Gui/src/misc/lv_txt.c \
../Gui/src/misc/lv_txt_ap.c \
../Gui/src/misc/lv_utils.c 

OBJS += \
./Gui/src/misc/lv_anim.o \
./Gui/src/misc/lv_anim_timeline.o \
./Gui/src/misc/lv_area.o \
./Gui/src/misc/lv_async.o \
./Gui/src/misc/lv_bidi.o \
./Gui/src/misc/lv_color.o \
./Gui/src/misc/lv_fs.o \
./Gui/src/misc/lv_gc.o \
./Gui/src/misc/lv_ll.o \
./Gui/src/misc/lv_log.o \
./Gui/src/misc/lv_lru.o \
./Gui/src/misc/lv_math.o \
./Gui/src/misc/lv_mem.o \
./Gui/src/misc/lv_printf.o \
./Gui/src/misc/lv_style.o \
./Gui/src/misc/lv_style_gen.o \
./Gui/src/misc/lv_templ.o \
./Gui/src/misc/lv_timer.o \
./Gui/src/misc/lv_tlsf.o \
./Gui/src/misc/lv_txt.o \
./Gui/src/misc/lv_txt_ap.o \
./Gui/src/misc/lv_utils.o 

C_DEPS += \
./Gui/src/misc/lv_anim.d \
./Gui/src/misc/lv_anim_timeline.d \
./Gui/src/misc/lv_area.d \
./Gui/src/misc/lv_async.d \
./Gui/src/misc/lv_bidi.d \
./Gui/src/misc/lv_color.d \
./Gui/src/misc/lv_fs.d \
./Gui/src/misc/lv_gc.d \
./Gui/src/misc/lv_ll.d \
./Gui/src/misc/lv_log.d \
./Gui/src/misc/lv_lru.d \
./Gui/src/misc/lv_math.d \
./Gui/src/misc/lv_mem.d \
./Gui/src/misc/lv_printf.d \
./Gui/src/misc/lv_style.d \
./Gui/src/misc/lv_style_gen.d \
./Gui/src/misc/lv_templ.d \
./Gui/src/misc/lv_timer.d \
./Gui/src/misc/lv_tlsf.d \
./Gui/src/misc/lv_txt.d \
./Gui/src/misc/lv_txt_ap.d \
./Gui/src/misc/lv_utils.d 


# Each subdirectory must supply rules for building sources it contributes
Gui/src/misc/%.o: ../Gui/src/misc/%.c
	@	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"C:\Users\86135\Desktop\WearableGasDetect\MainBody_CH32V307\MainBody_CH32V307\Debug" -I"C:\Users\86135\Desktop\WearableGasDetect\MainBody_CH32V307\MainBody_CH32V307\Gui" -I"C:\Users\86135\Desktop\WearableGasDetect\MainBody_CH32V307\MainBody_CH32V307\Core" -I"C:\Users\86135\Desktop\WearableGasDetect\MainBody_CH32V307\MainBody_CH32V307\User" -I"C:\Users\86135\Desktop\WearableGasDetect\MainBody_CH32V307\MainBody_CH32V307\Peripheral\inc" -I"C:\Users\86135\Desktop\WearableGasDetect\MainBody_CH32V307\MainBody_CH32V307\Gui\demos" -I"C:\Users\86135\Desktop\WearableGasDetect\MainBody_CH32V307\MainBody_CH32V307\Gui\demos\widgets" -I"C:\Users\86135\Desktop\WearableGasDetect\MainBody_CH32V307\MainBody_CH32V307\Gui\src" -I"C:\Users\86135\Desktop\WearableGasDetect\MainBody_CH32V307\MainBody_CH32V307\Gui\porting" -I"C:\Users\86135\Desktop\WearableGasDetect\MainBody_CH32V307\MainBody_CH32V307\Gui\custom" -I"C:\Users\86135\Desktop\WearableGasDetect\MainBody_CH32V307\MainBody_CH32V307\Gui\generated" -I"C:\Users\86135\Desktop\WearableGasDetect\MainBody_CH32V307\MainBody_CH32V307\Gui\generated\guider_customer_fonts" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

