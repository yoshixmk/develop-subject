#include "Photomicrosensor.h"

namespace Hardware
{
Photomicrosensor::Photomicrosensor(int aGpioPin)
{
	this->gpioPin=aGpioPin;

	gpioSetMode(this->gpioPin, PI_INPUT);
	gpioWrite(this->gpioPin,0);
}

bool Photomicrosensor::readLevel()
{
	bool level=gpioRead(gpioPin);

	return level;
}
}  // namespace Hardware
