#ifndef HARDWARE_RASPBERRY_PI_SIGNAL_H
#define HARDWARE_RASPBERRY_PI_SIGNAL_H

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
