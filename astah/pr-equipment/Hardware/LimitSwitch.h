#ifndef HARDWARE_LIMIT_SWITCH_H
#define HARDWARE_LIMIT_SWITCH_H

#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>

namespace Hardware
{
class LimitSwitch
{
private:
	int gpio_pin;


public:
	bool readLevel();

};

}  // namespace Hardware
#endif
