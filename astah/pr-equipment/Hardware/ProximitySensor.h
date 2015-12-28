#ifndef HARDWARE_PROXIMITY_SENSOR_H
#define HARDWARE_PROXIMITY_SENSOR_H

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
