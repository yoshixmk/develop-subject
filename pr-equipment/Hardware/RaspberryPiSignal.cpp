#include "RaspberryPiSignal.h"

namespace Hardware
{
RaspberryPiSignal::RaspberryPiSignal(int aGpioPin)
{
	this->gpioPin=aGpioPin;
	gpioSetMode(this->gpioPin, PI_INPUT);
	gpioWrite(gpioPin,0);
}

bool RaspberryPiSignal::readLevel()
{
	bool level=gpioRead(gpioPin);

	return level;
}
}  // namespace Hardware
