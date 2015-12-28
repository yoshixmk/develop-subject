#ifndef HARDWARE_PHOTOELECTRIC_SENSOR_H
#define HARDWARE_PHOTOELECTRIC_SENSOR_H

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
