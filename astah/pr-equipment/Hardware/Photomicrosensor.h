#ifndef HARDWARE_PHOTOMICROSENSOR_H
#define HARDWARE_PHOTOMICROSENSOR_H

#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>

namespace Hardware
{
class Photomicrosensor
{
private:
	int gpio_pin;


public:
	bool readLevel();

};

}  // namespace Hardware
#endif
