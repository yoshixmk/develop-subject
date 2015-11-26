################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../ShowWindow/Drawing.cpp \
../ShowWindow/Window.cpp \
../ShowWindow/WindowManagement.cpp 

OBJS += \
./ShowWindow/Drawing.o \
./ShowWindow/Window.o \
./ShowWindow/WindowManagement.o 

CPP_DEPS += \
./ShowWindow/Drawing.d \
./ShowWindow/Window.d \
./ShowWindow/WindowManagement.d 


# Each subdirectory must supply rules for building sources it contributes
ShowWindow/%.o: ../ShowWindow/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	arm-linux-gnueabihf-g++ -I"C:\dev\pigpio-master" -I"C:\Users\admin\workspace\pr_equipment" -I"C:\dev\opencv2.4.11\build\include" -I"C:\SysGCC\Raspberry\arm-linux-gnueabihf\include\c++\4.6" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


