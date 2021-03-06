################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Hardware/BGMSignal.cpp \
../Hardware/Camera.cpp \
../Hardware/LimitSwitch.cpp \
../Hardware/MotorDriver.cpp \
../Hardware/MotorDriverOri.cpp \
../Hardware/PhotoelectricSensor.cpp \
../Hardware/Photomicrosensor.cpp \
../Hardware/ProximitySensor.cpp \
../Hardware/PushSwitch.cpp \
../Hardware/RaspberryPiSignal.cpp \
../Hardware/Serial.cpp \
../Hardware/Speaker.cpp \
../Hardware/Timer.cpp 

OBJS += \
./Hardware/BGMSignal.o \
./Hardware/Camera.o \
./Hardware/LimitSwitch.o \
./Hardware/MotorDriver.o \
./Hardware/MotorDriverOri.o \
./Hardware/PhotoelectricSensor.o \
./Hardware/Photomicrosensor.o \
./Hardware/ProximitySensor.o \
./Hardware/PushSwitch.o \
./Hardware/RaspberryPiSignal.o \
./Hardware/Serial.o \
./Hardware/Speaker.o \
./Hardware/Timer.o 

CPP_DEPS += \
./Hardware/BGMSignal.d \
./Hardware/Camera.d \
./Hardware/LimitSwitch.d \
./Hardware/MotorDriver.d \
./Hardware/MotorDriverOri.d \
./Hardware/PhotoelectricSensor.d \
./Hardware/Photomicrosensor.d \
./Hardware/ProximitySensor.d \
./Hardware/PushSwitch.d \
./Hardware/RaspberryPiSignal.d \
./Hardware/Serial.d \
./Hardware/Speaker.d \
./Hardware/Timer.d 


# Each subdirectory must supply rules for building sources it contributes
Hardware/%.o: ../Hardware/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	arm-linux-gnueabihf-g++ -I"C:\Users\miyawaki\Documents\Github\develop-subject\pr-equipment" -I"\\raspberrypi\pi\usr\local\include" -I"C:\dev\pigpio-master" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


