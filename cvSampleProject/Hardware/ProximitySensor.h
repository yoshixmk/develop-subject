#ifndef HARDWARE_PROXIMITY_SENSOR_H
#define HARDWARE_PROXIMITY_SENSOR_H

#include "pigpio.h"

namespace Hardware {
class ProximitySensor {
private:
	int mGpioPin;

public:
	ProximitySensor(int aGpioPin);
	bool readLevel();

};

}  // namespace Hardware
#endif
