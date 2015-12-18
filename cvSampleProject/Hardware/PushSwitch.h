#ifndef HARDWARE_PUSH_SWITCH_H
#define HARDWARE_PUSH_SWITCH_H

#include<pigpio.h>

namespace Hardware {
class PushSwitch {
private:
	int mGpioPin;

public:
	PushSwitch(int aGpioPin);
	bool readLevel();

};

}  // namespace Hardware
#endif
