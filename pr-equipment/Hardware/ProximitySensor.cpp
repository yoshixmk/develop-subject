#include "ProximitySensor.h"

namespace Hardware
{
ProximitySensor::ProximitySensor(int aGpioPin)
{
	this->gpioPin=aGpioPin;
	gpioSetMode(this->gpioPin, PI_INPUT);
	gpioWrite(gpioPin,0);
}

bool ProximitySensor::readLevel()
{
	bool level=gpioRead(gpioPin);

	return level;
}
}  // namespace Hardware
