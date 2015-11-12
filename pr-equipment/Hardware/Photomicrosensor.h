#ifndef HARDWARE_PHOTOMICROSENSOR_H
#define HARDWARE_PHOTOMICROSENSOR_H

#include<pigpio.h>

namespace Hardware
{
class Photomicrosensor
{
private:
	int gpioPin;


public:
	Photomicrosensor(int aGpioPin);
	bool readLevel();

};

}  // namespace Hardware
#endif
