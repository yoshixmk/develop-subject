################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../UI/Intelligent.cpp \
../UI/Mode.cpp \
../UI/PackSpeed.cpp \
../UI/PlayMode.cpp \
../UI/SettingMode.cpp \
../UI/Sound.cpp \
../UI/UI.cpp 

OBJS += \
./UI/Intelligent.o \
./UI/Mode.o \
./UI/PackSpeed.o \
./UI/PlayMode.o \
./UI/SettingMode.o \
./UI/Sound.o \
./UI/UI.o 

CPP_DEPS += \
./UI/Intelligent.d \
./UI/Mode.d \
./UI/PackSpeed.d \
./UI/PlayMode.d \
./UI/SettingMode.d \
./UI/Sound.d \
./UI/UI.d 


# Each subdirectory must supply rules for building sources it contributes
UI/%.o: ../UI/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	arm-linux-gnueabihf-g++ -I"C:\Users\miyawaki\Documents\Github\develop-subject\pr-equipment" -I"C:\dev\pigpio-master" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


