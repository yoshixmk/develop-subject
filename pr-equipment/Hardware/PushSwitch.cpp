#include "PushSwitch.h"

namespace Hardware
{
PushSwitch::PushSwitch(int aGpioPin)
{
	this->gpioPin=aGpioPin;

	gpioSetMode(this->gpioPin, PI_INPUT);
	gpioWrite(gpioPin,0);
}

bool PushSwitch::readLevel()
{
	bool level=gpioRead(gpioPin);

	return level;
}
}  // namespace Hardware
