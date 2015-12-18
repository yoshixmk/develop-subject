#ifndef HARDWARE_MOTOR_DRIVER_H
#define HARDWARE_MOTOR_DRIVER_H

#include <pigpio.h>

namespace Hardware {
class MotorDriver {
private:
	int mPulseGpioPin;

	int mCwCcwGpioPin;

public:
	MotorDriver(int aPulseGpioPin, int aCwCcwGpioPin);

	~MotorDriver();

	void output();

	void stopOutput();

	void setPulse(int aFrequency);

	void setCwCcw(bool aHOrL);

};

}  // namespace Hardware
#endif
