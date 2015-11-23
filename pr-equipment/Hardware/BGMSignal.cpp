#include "BGMSignal.h"

namespace Hardware
{
BGMSignal::BGMSignal(int aGpioPin)
{
	mGpioPin=aGpioPin;
	gpioSetMode(mGpioPin, PI_INPUT);
	gpioWrite(mGpioPin,0);
}

void BGMSignal::writeHigh()
{
	gpioWrite(mGpioPin, 1);
}

void BGMSignal::writeLow()
{
	gpioWrite(mGpioPin, 0);
}
}
