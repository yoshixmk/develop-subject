################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Hardware/BGMSignal.cpp \
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
./Hardware/BGMSignal.o \
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
./Hardware/BGMSignal.d \
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
	arm-linux-gnueabihf-g++ -I"C:\dev\pigpio-master" -I"C:\Users\admin\workspace\pr_equipment" -I"C:\dev\opencv2.4.11\build\include" -I"C:\SysGCC\Raspberry\arm-linux-gnueabihf\include\c++\4.6" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


