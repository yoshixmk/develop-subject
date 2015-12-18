#include "PhotoelectricSensor.h"

namespace Hardware {
PhotoelectricSensor::PhotoelectricSensor(int aGpioPin) {
	mGpioPin = aGpioPin;

	gpioSetMode(mGpioPin, PI_INPUT);
	gpioWrite(mGpioPin, 0);
}

bool PhotoelectricSensor::readLevel() {
	bool level = gpioRead(mGpioPin);

	return level;
}
}  // namespace Hardware
