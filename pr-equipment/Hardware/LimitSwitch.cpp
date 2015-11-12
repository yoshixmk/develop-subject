#include "LimitSwitch.h"

namespace Hardware
{
LimitSwitch::LimitSwitch(int aGpioPin)
{
	this->gpioPin=aGpioPin;
	gpioSetMode(this->gpioPin, PI_INPUT);
	gpioWrite(gpioPin,0);
}

bool LimitSwitch::readLevel()
{
	bool level=gpioRead(gpioPin);

	return level;
}
}  // namespace Hardware
