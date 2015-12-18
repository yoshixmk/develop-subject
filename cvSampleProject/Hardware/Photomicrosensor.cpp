#include "Photomicrosensor.h"

namespace Hardware {
Photomicrosensor::Photomicrosensor(int aGpioPin) {
	mGpioPin = aGpioPin;

	gpioSetMode(mGpioPin, PI_INPUT);
	gpioWrite(mGpioPin, 0);
}

bool Photomicrosensor::readLevel() {
	bool level = gpioRead(mGpioPin);

	return level;
}
}  // namespace Hardware
