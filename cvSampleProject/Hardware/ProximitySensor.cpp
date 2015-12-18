#include "ProximitySensor.h"

namespace Hardware {
ProximitySensor::ProximitySensor(int aGpioPin) {
	mGpioPin = aGpioPin;
	gpioSetMode(mGpioPin, PI_INPUT);
	gpioWrite(mGpioPin, 0);
}

bool ProximitySensor::readLevel() {
	bool level = gpioRead(mGpioPin);

	return level;
}
}  // namespace Hardware
