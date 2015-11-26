################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include UI/subdir.mk
-include Test/subdir.mk
-include Strategy/subdir.mk
-include ShowWindow/subdir.mk
-include Hardware/subdir.mk
-include Color/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: pr_equipment

# Tool invocations
pr_equipment: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: Cross G++ Linker'
	arm-linux-gnueabihf-g++ -L"C:\dev\pigpio-master" -L"\\RASP-ENDO\pi\home\pi\opencv-2.4.11\build\lib" -Xlinker -rpath-link=\\RASP-ENDO\pi\usr\lib\arm-linux-gnueabihf -Xlinker -rpath-link=\\RASP-ENDO\pi\usr\lib\ -Xlinker -rpath-link=\\RASP-ENDO\pi\lib\arm-linux-gnueabihf -o "pr_equipment" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(CC_DEPS)$(C++_DEPS)$(EXECUTABLES)$(OBJS)$(C_UPPER_DEPS)$(CXX_DEPS)$(C_DEPS)$(CPP_DEPS) pr_equipment
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
