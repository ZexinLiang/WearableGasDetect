################################################################################
# MRS Version: 2.1.0
# Automatically-generated file. Do not edit!
################################################################################
-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include User/subdir.mk
-include Startup/subdir.mk
-include Peripheral/src/subdir.mk
-include Gui/lvgl_app/src/lv_ex_widgets/lv_ex_win/subdir.mk
-include Gui/lvgl_app/src/lv_ex_widgets/lv_ex_tileview/subdir.mk
-include Gui/lvgl_app/src/lv_ex_widgets/lv_ex_textarea/subdir.mk
-include Gui/lvgl_app/src/lv_ex_widgets/lv_ex_tabview/subdir.mk
-include Gui/lvgl_app/src/lv_ex_widgets/lv_ex_table/subdir.mk
-include Gui/lvgl_app/src/lv_ex_widgets/lv_ex_switch/subdir.mk
-include Gui/lvgl_app/src/lv_ex_widgets/lv_ex_spinner/subdir.mk
-include Gui/lvgl_app/src/lv_ex_widgets/lv_ex_spinbox/subdir.mk
-include Gui/lvgl_app/src/lv_ex_widgets/lv_ex_slider/subdir.mk
-include Gui/lvgl_app/src/lv_ex_widgets/lv_ex_roller/subdir.mk
-include Gui/lvgl_app/src/lv_ex_widgets/lv_ex_page/subdir.mk
-include Gui/lvgl_app/src/lv_ex_widgets/lv_ex_objmask/subdir.mk
-include Gui/lvgl_app/src/lv_ex_widgets/lv_ex_obj/subdir.mk
-include Gui/lvgl_app/src/lv_ex_widgets/lv_ex_msgbox/subdir.mk
-include Gui/lvgl_app/src/lv_ex_widgets/lv_ex_list/subdir.mk
-include Gui/lvgl_app/src/lv_ex_widgets/lv_ex_linemeter/subdir.mk
-include Gui/lvgl_app/src/lv_ex_widgets/lv_ex_line/subdir.mk
-include Gui/lvgl_app/src/lv_ex_widgets/lv_ex_led/subdir.mk
-include Gui/lvgl_app/src/lv_ex_widgets/lv_ex_label/subdir.mk
-include Gui/lvgl_app/src/lv_ex_widgets/lv_ex_keyboard/subdir.mk
-include Gui/lvgl_app/src/lv_ex_widgets/lv_ex_imgbtn/subdir.mk
-include Gui/lvgl_app/src/lv_ex_widgets/lv_ex_img/subdir.mk
-include Gui/lvgl_app/src/lv_ex_widgets/lv_ex_gauge/subdir.mk
-include Gui/lvgl_app/src/lv_ex_widgets/lv_ex_dropdown/subdir.mk
-include Gui/lvgl_app/src/lv_ex_widgets/lv_ex_cpicker/subdir.mk
-include Gui/lvgl_app/src/lv_ex_widgets/lv_ex_cont/subdir.mk
-include Gui/lvgl_app/src/lv_ex_widgets/lv_ex_checkbox/subdir.mk
-include Gui/lvgl_app/src/lv_ex_widgets/lv_ex_chart/subdir.mk
-include Gui/lvgl_app/src/lv_ex_widgets/lv_ex_canvas/subdir.mk
-include Gui/lvgl_app/src/lv_ex_widgets/lv_ex_calendar/subdir.mk
-include Gui/lvgl_app/src/lv_ex_widgets/lv_ex_btnmatrix/subdir.mk
-include Gui/lvgl_app/src/lv_ex_widgets/lv_ex_btn/subdir.mk
-include Gui/lvgl_app/src/lv_ex_widgets/lv_ex_bar/subdir.mk
-include Gui/lvgl_app/src/lv_ex_widgets/lv_ex_arc/subdir.mk
-include Gui/lvgl_app/src/lv_ex_style/subdir.mk
-include Gui/lvgl_app/src/lv_ex_get_started/subdir.mk
-include Gui/lvgl_app/src/lv_demo_widgets/subdir.mk
-include Gui/lvgl_app/src/lv_demo_stress/subdir.mk
-include Gui/lvgl_app/src/lv_demo_printer/images/subdir.mk
-include Gui/lvgl_app/src/lv_demo_printer/subdir.mk
-include Gui/lvgl_app/src/lv_demo_music/assets/subdir.mk
-include Gui/lvgl_app/src/lv_demo_music/subdir.mk
-include Gui/lvgl_app/src/lv_demo_keypad_encoder/subdir.mk
-include Gui/lvgl_app/src/lv_demo_benchmark/subdir.mk
-include Gui/lvgl_app/src/assets/subdir.mk
-include Gui/lvgl/tests/lv_test_widgets/subdir.mk
-include Gui/lvgl/tests/lv_test_fonts/subdir.mk
-include Gui/lvgl/tests/lv_test_core/subdir.mk
-include Gui/lvgl/tests/subdir.mk
-include Gui/lvgl/src/lv_widgets/subdir.mk
-include Gui/lvgl/src/lv_themes/subdir.mk
-include Gui/lvgl/src/lv_misc/subdir.mk
-include Gui/lvgl/src/lv_hal/subdir.mk
-include Gui/lvgl/src/lv_gpu/subdir.mk
-include Gui/lvgl/src/lv_font/subdir.mk
-include Gui/lvgl/src/lv_draw/subdir.mk
-include Gui/lvgl/src/lv_core/subdir.mk
-include Gui/lvgl/examples/porting/subdir.mk
-include Debug/subdir.mk
-include Core/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
SECONDARY_FLASH += \
MainBody_CH32V307.hex \

SECONDARY_LIST += \
MainBody_CH32V307.lst \

SECONDARY_SIZE += \
MainBody_CH32V307.siz \


# All Target
all: 
	$(MAKE) --no-print-directory main-build 

main-build: MainBody_CH32V307.elf secondary-outputs

# Tool invocations
MainBody_CH32V307.elf: $(OBJS) $(USER_OBJS)
	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -fmax-errors=20 -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized -g -T "c:/Users/86135/Desktop/WearableGasDetect/MainBody_CH32V307_lvgl8310/MainBody_CH32V307/Ld/Link.ld" -nostartfiles -Xlinker --gc-sections -Wl,-Map,"MainBody_CH32V307.map" --specs=nano.specs --specs=nosys.specs -o "MainBody_CH32V307.elf" $(OBJS) $(USER_OBJS) $(LIBS)
MainBody_CH32V307.hex: MainBody_CH32V307.elf
	@	riscv-none-embed-objcopy -O ihex "MainBody_CH32V307.elf" "MainBody_CH32V307.hex"
MainBody_CH32V307.lst: MainBody_CH32V307.elf
	@	riscv-none-embed-objdump --all-headers --demangle --disassemble -M xw "MainBody_CH32V307.elf" > "MainBody_CH32V307.lst"
MainBody_CH32V307.siz: MainBody_CH32V307.elf
	riscv-none-embed-size --format=berkeley "MainBody_CH32V307.elf"

# Other Targets
clean:
	-$(RM) $(OBJS)$(SECONDARY_FLASH)$(SECONDARY_LIST)$(SECONDARY_SIZE)$(S_DEPS)$(S_UPPER_DEPS)$(ASM_DEPS)$(ASM_UPPER_DEPS)$(C_DEPS) MainBody_CH32V307.elf

secondary-outputs: $(SECONDARY_FLASH) $(SECONDARY_LIST) $(SECONDARY_SIZE)

.PHONY: all clean dependents

-include ../makefile.targets