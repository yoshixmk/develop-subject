#ifndef HARDWARE_PHOTOELECTRIC_SENSOR_H
#define HARDWARE_PHOTOELECTRIC_SENSOR_H

#include<pigpio.h>

namespace Hardware
{
class PhotoelectricSensor
{
private:
	int gpioPin;


public:
	PhotoelectricSensor(int aGpioPin);
	bool readLevel();

};

}  // namespace Hardware
#endif
