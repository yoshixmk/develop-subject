#include "LimitSwitch.h"

namespace Hardware {
LimitSwitch::LimitSwitch(int aGpioPin) {
	mGpioPin = aGpioPin;
	gpioSetMode(mGpioPin, PI_INPUT);
	gpioWrite(mGpioPin, 0);
}

bool LimitSwitch::readLevel() {
	bool level = gpioRead(mGpioPin);

	return level;
}
}  // namespace Hardware
