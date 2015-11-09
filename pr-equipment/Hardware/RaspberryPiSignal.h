#ifndef HARDWARE_RASPBERRY_PI_SIGNAL_H
#define HARDWARE_RASPBERRY_PI_SIGNAL_H

#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>

namespace Hardware
{
class RaspberryPiSignal
{
private:
	int gpio_pin;


public:
	bool readLevel();

};

}  // namespace Hardware
#endif
