################################################################################
# MRS Version: 2.1.0
# Automatically-generated file. Do not edit!
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
CH582F.hex \

SECONDARY_LIST += \
CH582F.lst \

SECONDARY_SIZE += \
CH582F.siz \


# All Target
all: 
	$(MAKE) --no-print-directory main-build 

main-build: CH582F.elf secondary-outputs

# Tool invocations
CH582F.elf: $(OBJS) $(USER_OBJS)
	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -mcmodel=medany -msmall-data-limit=8 -mno-save-restore -fmax-errors=20 -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -g -T "c:\Users\86135\Desktop\WearableGasDetect\CH582F_Peri\CH582F\Ld\Link.ld" -nostartfiles -Xlinker --gc-sections -L"c:\Users\86135\Desktop\WearableGasDetect\CH582F_Peri\CH582F" -L"c:\Users\86135\Desktop\WearableGasDetect\CH582F_Peri\CH582F\StdPeriphDriver" -L"c:/Users/86135/Desktop/WearableGasDetect/CH582F_Peri/CH582F/LIB" -Xlinker --print-memory-usage -Wl,-Map,"CH582F.map" --specs=nano.specs --specs=nosys.specs -o "CH582F.elf" $(OBJS) $(USER_OBJS) $(LIBS)
CH582F.hex: CH582F.elf
	@	riscv-none-embed-objcopy -O ihex "CH582F.elf" "CH582F.hex"
CH582F.lst: CH582F.elf
	@	riscv-none-embed-objdump --source --all-headers --demangle --line-numbers --wide "CH582F.elf" > "CH582F.lst"
CH582F.siz: CH582F.elf
	riscv-none-embed-size --format=berkeley "CH582F.elf"

# Other Targets
clean:
	-$(RM) $(OBJS)$(SECONDARY_FLASH)$(SECONDARY_LIST)$(SECONDARY_SIZE)$(S_DEPS)$(S_UPPER_DEPS)$(ASM_DEPS)$(ASM_UPPER_DEPS)$(C_DEPS) CH582F.elf

secondary-outputs: $(SECONDARY_FLASH) $(SECONDARY_LIST) $(SECONDARY_SIZE)

.PHONY: all clean dependents

-include ../makefile.targets