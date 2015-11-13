#ifndef HARDWARE_MOTOR_DRIVER_H
#define HARDWARE_MOTOR_DRIVER_H

#include <pigpio.h>

namespace Hardware
{
class MotorDriver
{
private:
	int mPulseGpioPin;

	int mCwCcwGpioPin;

	void stopOutput();


public:
	MotorDriver(int aPulseGpioPin, int aCwCcwGpioPin);

	void output();

	void setPulse(int aFrequency);

	void setCwCcw(bool aHOrL);

};

}  // namespace Hardware
#endif
