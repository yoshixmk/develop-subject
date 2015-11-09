#ifndef HARDWARE_PROXIMITY SENSOR_H
#define HARDWARE_PROXIMITY SENSOR_H

#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>

namespace Hardware
{
class ProximitySensor
{
private:
	int gpio_pin;


public:
	bool readLevel();

};

}  // namespace Hardware
#endif
