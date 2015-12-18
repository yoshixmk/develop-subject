#include "MotorDriver.h"

namespace Hardware
{
MotorDriver::MotorDriver(int aPulseGpioPin, int aCwCcwGpioPin)
{
	mPulseGpioPin=aPulseGpioPin;
	gpioSetMode(mPulseGpioPin, PI_OUTPUT);
	gpioHardwarePWM(mPulseGpioPin, 0, 500000);
	mFrequency = 0;

	mCwCcwGpioPin = aCwCcwGpioPin;
	gpioSetMode(mCwCcwGpioPin, PI_OUTPUT);
	gpioWrite(mCwCcwGpioPin, 0);
	mIsHigh = false;//0
}

MotorDriver::~MotorDriver()
{

}

void MotorDriver::output(int aFrequency, bool aIsHigh)
{
	if(mFrequency != aFrequency){
		gpioHardwarePWM(mPulseGpioPin, aFrequency, 500000);
		mFrequency = aFrequency;
	}
	if(mIsHigh != aIsHigh){
		gpioWrite(mCwCcwGpioPin, aIsHigh);
		mIsHigh = aIsHigh;
	}
}

}  // namespace Hardware
