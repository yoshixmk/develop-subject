#ifndef HARDWARE_PHOTOELECTRIC_SENSOR_H
#define HARDWARE_PHOTOELECTRIC_SENSOR_H

#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>

namespace Hardware
{
class PhotoelectricSensor
{
private:
	int gpio_pin;


public:
	bool readLevel();

};

}  // namespace Hardware
#endif
