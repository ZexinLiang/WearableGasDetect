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
CH582F.hex \

SECONDARY_LIST += \
CH582F.lst \

SECONDARY_SIZE += \
CH582F.siz \


# 所有目标
all: CH582F.elf secondary-outputs

# 工具调用
CH582F.elf: $(OBJS) $(USER_OBJS)
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -mcmodel=medany -msmall-data-limit=8 -mno-save-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common  -g -T "../Ld/Link.ld" -nostartfiles -Xlinker --gc-sections -L"../" -L"../StdPeriphDriver" -L"C:\Users\86135\Desktop\WearableGasDetect\CH582F\CH582F\LIB" -Xlinker --print-memory-usage -Wl,-Map,"CH582F.map" --specs=nano.specs -u _printf_float --specs=nosys.specs -o "CH582F.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@	@
CH582F.hex: CH582F.elf
	@	riscv-none-embed-objcopy -O ihex "CH582F.elf"  "CH582F.hex"
	@	@
CH582F.lst: CH582F.elf
	@	riscv-none-embed-objdump --source --all-headers --demangle --line-numbers --wide "CH582F.elf" > "CH582F.lst"
	@	@
CH582F.siz: CH582F.elf
	@	riscv-none-embed-size --format=berkeley "CH582F.elf"
	@	@
# 其他目标
clean:
	-$(RM) $(ASM_UPPER_DEPS)$(OBJS)$(SECONDARY_FLASH)$(SECONDARY_LIST)$(SECONDARY_SIZE)$(ASM_DEPS)$(S_DEPS)$(S_UPPER_DEPS)$(C_DEPS) CH582F.elf
	-@
secondary-outputs: $(SECONDARY_FLASH) $(SECONDARY_LIST) $(SECONDARY_SIZE)

.PHONY: all clean dependents

-include ../makefile.targets
