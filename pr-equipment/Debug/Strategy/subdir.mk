################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Strategy/AnomalyDetection.cpp \
../Strategy/Coordinate.cpp \
../Strategy/DefenseStrategy.cpp \
../Strategy/FrameCoordinate.cpp \
../Strategy/FrequencySwitching.cpp \
../Strategy/Locus.cpp \
../Strategy/MalletCoordinate.cpp \
../Strategy/OffenseDefenseStrategy.cpp \
../Strategy/OffenseStrategy.cpp \
../Strategy/OriginRetrun.cpp \
../Strategy/PackCoordinate.cpp \
../Strategy/RandomPositionCoordinate.cpp \
../Strategy/RobotAction.cpp \
../Strategy/Strategy.cpp 

OBJS += \
./Strategy/AnomalyDetection.o \
./Strategy/Coordinate.o \
./Strategy/DefenseStrategy.o \
./Strategy/FrameCoordinate.o \
./Strategy/FrequencySwitching.o \
./Strategy/Locus.o \
./Strategy/MalletCoordinate.o \
./Strategy/OffenseDefenseStrategy.o \
./Strategy/OffenseStrategy.o \
./Strategy/OriginRetrun.o \
./Strategy/PackCoordinate.o \
./Strategy/RandomPositionCoordinate.o \
./Strategy/RobotAction.o \
./Strategy/Strategy.o 

CPP_DEPS += \
./Strategy/AnomalyDetection.d \
./Strategy/Coordinate.d \
./Strategy/DefenseStrategy.d \
./Strategy/FrameCoordinate.d \
./Strategy/FrequencySwitching.d \
./Strategy/Locus.d \
./Strategy/MalletCoordinate.d \
./Strategy/OffenseDefenseStrategy.d \
./Strategy/OffenseStrategy.d \
./Strategy/OriginRetrun.d \
./Strategy/PackCoordinate.d \
./Strategy/RandomPositionCoordinate.d \
./Strategy/RobotAction.d \
./Strategy/Strategy.d 


# Each subdirectory must supply rules for building sources it contributes
Strategy/%.o: ../Strategy/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	arm-linux-gnueabihf-g++ -I"C:\Users\miyawaki\Documents\Github\develop-subject\pr-equipment" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


