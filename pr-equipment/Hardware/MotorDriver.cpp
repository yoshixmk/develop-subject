#include "MotorDriver.h"

namespace Hardware
{
MotorDriver::MotorDriver(int aPulseGpioPin, int aCwCcwGpioPin)
{
	mPulseGpioPin=aPulseGpioPin;
	gpioSetMode(mPulseGpioPin, PI_OUTPUT);

	mCwCcwGpioPin = aCwCcwGpioPin;
	gpioSetMode(mCwCcwGpioPin, PI_OUTPUT);
	gpioWrite(mCwCcwGpioPin, 0);
}

void MotorDriver::output()
{
	gpioPWM(mPulseGpioPin, 128);
}

void MotorDriver::setPulse(int aFrequency)
{
	//設定はパルスを止める
	gpioPWM(mPulseGpioPin, 0);
	if(gpioGetPWMfrequency(mPulseGpioPin) != aFrequency){
		gpioSetPWMfrequency(mPulseGpioPin, aFrequency);
	}
}

void MotorDriver::setCwCcw(bool aHOrL)
{
	//設定はパルスを止める
	gpioPWM(mPulseGpioPin, 0);
	if(gpioRead(mCwCcwGpioPin) != aHOrL){
		gpioWrite(mCwCcwGpioPin, aHOrL);
	}
}

void MotorDriver::stopOutput()
{
	gpioPWM(mPulseGpioPin, 0);
}

}  // namespace Hardware
