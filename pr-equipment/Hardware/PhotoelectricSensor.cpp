#include "PhotoelectricSensor.h"

namespace Hardware
{
PhotoelectricSensor::PhotoelectricSensor(int aGpioPin)
{
	this->gpioPin=aGpioPin;

	gpioSetMode(this->gpioPin, PI_INPUT);
	gpioWrite(this->gpioPin,0);
}

bool PhotoelectricSensor::readLevel()
{
	bool level=gpioRead(gpioPin);

	return level;
}
}  // namespace Hardware
