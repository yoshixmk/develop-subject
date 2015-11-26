################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Color/ColorExtraction.cpp \
../Color/HockeyTableMasking.cpp \
../Color/Labeling.cpp \
../Color/Masking.cpp \
../Color/RobotSideHockeyTableMasking.cpp \
../Color/TwoImageSynthesis.cpp 

OBJS += \
./Color/ColorExtraction.o \
./Color/HockeyTableMasking.o \
./Color/Labeling.o \
./Color/Masking.o \
./Color/RobotSideHockeyTableMasking.o \
./Color/TwoImageSynthesis.o 

CPP_DEPS += \
./Color/ColorExtraction.d \
./Color/HockeyTableMasking.d \
./Color/Labeling.d \
./Color/Masking.d \
./Color/RobotSideHockeyTableMasking.d \
./Color/TwoImageSynthesis.d 


# Each subdirectory must supply rules for building sources it contributes
Color/%.o: ../Color/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	arm-linux-gnueabihf-g++ -I"C:\dev\pigpio-master" -I"C:\Users\admin\workspace\pr_equipment" -I"C:\dev\opencv2.4.11\build\include" -I"C:\SysGCC\Raspberry\arm-linux-gnueabihf\include\c++\4.6" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


