################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Hardware/Camera.cpp \
../Hardware/LimitSwitch.cpp \
../Hardware/MotorDriver.cpp \
../Hardware/PhotoelectricSensor.cpp \
../Hardware/Photomicrosensor.cpp \
../Hardware/ProximitySensor.cpp \
../Hardware/PushSwitch.cpp \
../Hardware/RaspberryPiSignal.cpp \
../Hardware/Speaker.cpp \
../Hardware/Timer.cpp 

OBJS += \
./Hardware/Camera.o \
./Hardware/LimitSwitch.o \
./Hardware/MotorDriver.o \
./Hardware/PhotoelectricSensor.o \
./Hardware/Photomicrosensor.o \
./Hardware/ProximitySensor.o \
./Hardware/PushSwitch.o \
./Hardware/RaspberryPiSignal.o \
./Hardware/Speaker.o \
./Hardware/Timer.o 

CPP_DEPS += \
./Hardware/Camera.d \
./Hardware/LimitSwitch.d \
./Hardware/MotorDriver.d \
./Hardware/PhotoelectricSensor.d \
./Hardware/Photomicrosensor.d \
./Hardware/ProximitySensor.d \
./Hardware/PushSwitch.d \
./Hardware/RaspberryPiSignal.d \
./Hardware/Speaker.d \
./Hardware/Timer.d 


# Each subdirectory must supply rules for building sources it contributes
Hardware/%.o: ../Hardware/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	arm-linux-gnueabihf-g++ -I"C:\Users\miyawaki\Documents\Github\develop-subject\pr-equipment" -I"C:\dev\pigpio-master" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


