#include "RaspberryPiSignal.h"

namespace Hardware {
RaspberryPiSignal::RaspberryPiSignal(int aGpioPin) {
	mGpioPin = aGpioPin;
	gpioSetMode(mGpioPin, PI_INPUT);
	gpioWrite(mGpioPin, 0);
}

bool RaspberryPiSignal::readLevel() {
	bool level = gpioRead(mGpioPin);

	return level;
}
}  // namespace Hardware
