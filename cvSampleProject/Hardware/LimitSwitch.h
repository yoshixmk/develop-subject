#ifndef HARDWARE_LIMIT_SWITCH_H
#define HARDWARE_LIMIT_SWITCH_H

#include<pigpio.h>

namespace Hardware {
class LimitSwitch {
private:
	int mGpioPin;

public:
	LimitSwitch(int aGpioPin);
	bool readLevel();

};

}  // namespace Hardware
#endif
