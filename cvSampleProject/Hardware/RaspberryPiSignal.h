#ifndef HARDWARE_RASPBERRY_PI_SIGNAL_H
#define HARDWARE_RASPBERRY_PI_SIGNAL_H

#include<pigpio.h>

namespace Hardware {
class RaspberryPiSignal {
private:
	int mGpioPin;

public:
	RaspberryPiSignal(int aGpioPin);
	bool readLevel();

};

}  // namespace Hardware
#endif
