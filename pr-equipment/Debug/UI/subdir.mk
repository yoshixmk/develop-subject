################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../UI/RobotMovement.cpp \
../UI/Sound.cpp 

OBJS += \
./UI/RobotMovement.o \
./UI/Sound.o 

CPP_DEPS += \
./UI/RobotMovement.d \
./UI/Sound.d 


# Each subdirectory must supply rules for building sources it contributes
UI/%.o: ../UI/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	arm-linux-gnueabihf-g++ -I"C:\Users\miyawaki\Documents\Github\develop-subject\pr-equipment" -I"\\raspberrypi\pi\usr\local\include" -I"C:\dev\pigpio-master" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


