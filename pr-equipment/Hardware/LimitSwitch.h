#ifndef HARDWARE_LIMIT_SWITCH_H
#define HARDWARE_LIMIT_SWITCH_H

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
