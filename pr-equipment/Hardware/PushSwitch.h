#ifndef HARDWARE_PUSH_SWITCH_H
#define HARDWARE_PUSH_SWITCH_H

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
