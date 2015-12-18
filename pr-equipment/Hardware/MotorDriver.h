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

	int mFrequency;

	bool mIsHigh;

public:
	MotorDriver(int aPulseGpioPin, int aCwCcwGpioPin);

	~MotorDriver();

	void output(int aFrequency, bool aIsHigh);

};

}  // namespace Hardware
#endif
