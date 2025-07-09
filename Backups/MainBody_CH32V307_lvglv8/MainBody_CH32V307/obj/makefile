################################################################################
# MRS Version: 1.9.2
# 自动生成的文件。不要编辑！
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include User/subdir.mk
-include Startup/subdir.mk
-include Peripheral/src/subdir.mk
-include Gui/src/widgets/subdir.mk
-include Gui/src/misc/subdir.mk
-include Gui/src/hal/subdir.mk
-include Gui/src/font/subdir.mk
-include Gui/src/extra/widgets/win/subdir.mk
-include Gui/src/extra/widgets/tileview/subdir.mk
-include Gui/src/extra/widgets/tabview/subdir.mk
-include Gui/src/extra/widgets/spinner/subdir.mk
-include Gui/src/extra/widgets/spinbox/subdir.mk
-include Gui/src/extra/widgets/span/subdir.mk
-include Gui/src/extra/widgets/msgbox/subdir.mk
-include Gui/src/extra/widgets/meter/subdir.mk
-include Gui/src/extra/widgets/menu/subdir.mk
-include Gui/src/extra/widgets/list/subdir.mk
-include Gui/src/extra/widgets/led/subdir.mk
-include Gui/src/extra/widgets/keyboard/subdir.mk
-include Gui/src/extra/widgets/imgbtn/subdir.mk
-include Gui/src/extra/widgets/colorwheel/subdir.mk
-include Gui/src/extra/widgets/chart/subdir.mk
-include Gui/src/extra/widgets/calendar/subdir.mk
-include Gui/src/extra/widgets/animimg/subdir.mk
-include Gui/src/extra/themes/mono/subdir.mk
-include Gui/src/extra/themes/default/subdir.mk
-include Gui/src/extra/themes/basic/subdir.mk
-include Gui/src/extra/others/snapshot/subdir.mk
-include Gui/src/extra/others/msg/subdir.mk
-include Gui/src/extra/others/monkey/subdir.mk
-include Gui/src/extra/others/imgfont/subdir.mk
-include Gui/src/extra/others/ime/subdir.mk
-include Gui/src/extra/others/gridnav/subdir.mk
-include Gui/src/extra/others/fragment/subdir.mk
-include Gui/src/extra/libs/sjpg/subdir.mk
-include Gui/src/extra/libs/rlottie/subdir.mk
-include Gui/src/extra/libs/qrcode/subdir.mk
-include Gui/src/extra/libs/png/subdir.mk
-include Gui/src/extra/libs/gif/subdir.mk
-include Gui/src/extra/libs/fsdrv/subdir.mk
-include Gui/src/extra/libs/freetype/subdir.mk
-include Gui/src/extra/libs/ffmpeg/subdir.mk
-include Gui/src/extra/libs/bmp/subdir.mk
-include Gui/src/extra/layouts/grid/subdir.mk
-include Gui/src/extra/layouts/flex/subdir.mk
-include Gui/src/extra/subdir.mk
-include Gui/src/draw/swm341_dma2d/subdir.mk
-include Gui/src/draw/sw/subdir.mk
-include Gui/src/draw/stm32_dma2d/subdir.mk
-include Gui/src/draw/sdl/subdir.mk
-include Gui/src/draw/renesas/subdir.mk
-include Gui/src/draw/nxp/vglite/subdir.mk
-include Gui/src/draw/nxp/pxp/subdir.mk
-include Gui/src/draw/arm2d/subdir.mk
-include Gui/src/draw/subdir.mk
-include Gui/src/core/subdir.mk
-include Gui/porting/subdir.mk
-include Gui/generated/images/subdir.mk
-include Gui/generated/guider_fonts/subdir.mk
-include Gui/generated/subdir.mk
-include Gui/demos/widgets/assets/subdir.mk
-include Gui/demos/widgets/subdir.mk
-include Gui/custom/subdir.mk
-include Debug/subdir.mk
-include Core/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
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


# 所有目标
all: MainBody_CH32V307.elf secondary-outputs

# 工具调用
MainBody_CH32V307.elf: $(OBJS) $(USER_OBJS)
	@	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -T "C:\Users\86135\Desktop\WearableGasDetect\MainBody_CH32V307\MainBody_CH32V307\Ld\Link.ld" -nostartfiles -Xlinker --gc-sections -Wl,-Map,"MainBody_CH32V307.map" --specs=nano.specs --specs=nosys.specs -o "MainBody_CH32V307.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@	@
MainBody_CH32V307.hex: MainBody_CH32V307.elf
	@	riscv-none-embed-objcopy -O ihex "MainBody_CH32V307.elf"  "MainBody_CH32V307.hex"
	@	@
MainBody_CH32V307.lst: MainBody_CH32V307.elf
	@	riscv-none-embed-objdump --all-headers --demangle --disassemble -M xw "MainBody_CH32V307.elf" > "MainBody_CH32V307.lst"
	@	@
MainBody_CH32V307.siz: MainBody_CH32V307.elf
	@	riscv-none-embed-size --format=berkeley "MainBody_CH32V307.elf"
	@	@
# 其他目标
clean:
	-$(RM) $(ASM_UPPER_DEPS)$(OBJS)$(SECONDARY_FLASH)$(SECONDARY_LIST)$(SECONDARY_SIZE)$(ASM_DEPS)$(S_DEPS)$(S_UPPER_DEPS)$(C_DEPS) MainBody_CH32V307.elf
	-@
secondary-outputs: $(SECONDARY_FLASH) $(SECONDARY_LIST) $(SECONDARY_SIZE)

.PHONY: all clean dependents

-include ../makefile.targets
