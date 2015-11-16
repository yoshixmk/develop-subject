#include "BGMSignal.h"

namespace Hardware
{
BGMSignal::BGMSignal(int aGpioPin)
{
	mGpioPin=aGpioPin;
	gpioSetMode(mGpioPin, PI_INPUT);
	gpioWrite(mGpioPin,0);
}

bool BGMSignal::readLevel()
{
	bool level=gpioRead(mGpioPin);

	return level;
}
}
