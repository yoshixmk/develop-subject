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
-include .metadata/.plugins/org.eclipse.cdt.make.core/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: pr-equipment

# Tool invocations
pr-equipment: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: Cross G++ Linker'
	arm-linux-gnueabihf-g++ -L"C:\Users\yoshihiro\Documents\GitHub\develop-subject\pr-equipment\Debug\Libraries\pigpio-master" -L"C:\dev\opencv-2.4.11\lib" -Xlinker -rpath-link=\\raspberrypi\pi\lib\arm-linux-gnueabihf -Xlinker -rpath-link=\\raspberrypi\pi\usr\lib -Xlinker -rpath-link=\\raspberrypi\pi\usr\lib\arm-linux-gnueabihf -o "pr-equipment" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(C++_DEPS)$(OBJS)$(C_DEPS)$(CC_DEPS)$(CPP_DEPS)$(EXECUTABLES)$(CXX_DEPS)$(C_UPPER_DEPS) pr-equipment
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
