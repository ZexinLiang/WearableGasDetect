################################################################################
# MRS Version: 1.9.2
# 自动生成的文件。不要编辑！
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include user/src/subdir.mk
-include StdPeriphDriver/subdir.mk
-include Startup/subdir.mk
-include RVMSIS/subdir.mk
-include Profile/subdir.mk
-include HAL/subdir.mk
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
MainBoard_CH582.hex \

SECONDARY_LIST += \
MainBoard_CH582.lst \

SECONDARY_SIZE += \
MainBoard_CH582.siz \


# 所有目标
all: MainBoard_CH582.elf secondary-outputs

# 工具调用
MainBoard_CH582.elf: $(OBJS) $(USER_OBJS)
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -mcmodel=medany -msmall-data-limit=8 -mno-save-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common  -g -T "../Ld/Link.ld" -nostartfiles -Xlinker --gc-sections -L"../" -L"C:\Users\86135\Desktop\WearableGasDetect\MainBoard_CH582\MainBoard_CH582\LIB" -L"../StdPeriphDriver" -Xlinker --print-memory-usage -Wl,-Map,"MainBoard_CH582.map" --specs=nano.specs --specs=nosys.specs -o "MainBoard_CH582.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@	@
MainBoard_CH582.hex: MainBoard_CH582.elf
	@	riscv-none-embed-objcopy -O ihex "MainBoard_CH582.elf"  "MainBoard_CH582.hex"
	@	@
MainBoard_CH582.lst: MainBoard_CH582.elf
	@	riscv-none-embed-objdump --source --all-headers --demangle --line-numbers --wide "MainBoard_CH582.elf" > "MainBoard_CH582.lst"
	@	@
MainBoard_CH582.siz: MainBoard_CH582.elf
	@	riscv-none-embed-size --format=berkeley "MainBoard_CH582.elf"
	@	@
# 其他目标
clean:
	-$(RM) $(ASM_UPPER_DEPS)$(OBJS)$(SECONDARY_FLASH)$(SECONDARY_LIST)$(SECONDARY_SIZE)$(ASM_DEPS)$(S_DEPS)$(S_UPPER_DEPS)$(C_DEPS) MainBoard_CH582.elf
	-@
secondary-outputs: $(SECONDARY_FLASH) $(SECONDARY_LIST) $(SECONDARY_SIZE)

.PHONY: all clean dependents

-include ../makefile.targets
