################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Color/ColorExtraction.cpp \
../Color/HockeyTableMasking.cpp \
../Color/Labeling.cpp \
../Color/Masking.cpp \
../Color/PerspectiveTransformation.cpp \
../Color/RobotSideHockeyTableMasking.cpp \
../Color/TwoImageSynthesis.cpp 

OBJS += \
./Color/ColorExtraction.o \
./Color/HockeyTableMasking.o \
./Color/Labeling.o \
./Color/Masking.o \
./Color/PerspectiveTransformation.o \
./Color/RobotSideHockeyTableMasking.o \
./Color/TwoImageSynthesis.o 

CPP_DEPS += \
./Color/ColorExtraction.d \
./Color/HockeyTableMasking.d \
./Color/Labeling.d \
./Color/Masking.d \
./Color/PerspectiveTransformation.d \
./Color/RobotSideHockeyTableMasking.d \
./Color/TwoImageSynthesis.d 


# Each subdirectory must supply rules for building sources it contributes
Color/%.o: ../Color/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	arm-linux-gnueabihf-g++ -I"C:\Users\miyawaki\Documents\Github\develop-subject\pr-equipment" -I"C:\dev\pigpio-master" -I"C:\dev\opencv-2.4.11\include" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


