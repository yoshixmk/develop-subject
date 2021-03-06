#include "PushSwitch.h"

namespace Hardware
{
PushSwitch::PushSwitch(int aGpioPin)
{
	mGpioPin=aGpioPin;

	gpioSetMode(mGpioPin, PI_INPUT);
	gpioWrite(mGpioPin,0);
}

bool PushSwitch::readLevel()
{
	bool level=gpioRead(mGpioPin);

	return level;
}
}  // namespace Hardware
