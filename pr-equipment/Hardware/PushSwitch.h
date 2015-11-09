#ifndef HARDWARE_PUSH_SWITCH_H
#define HARDWARE_PUSH_SWITCH_H

#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>

namespace Hardware
{
class PushSwitch
{
private:
	int gpio_pin;


public:
	bool readLevel();

};

}  // namespace Hardware
#endif
