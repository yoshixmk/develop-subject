#ifndef HARDWARE_BGMSIGNAL_H_
#define HARDWARE_BGMSIGNAL_H_

#include<pigpio.h>

namespace Hardware {
class BGMSignal {
private:
	int mGpioPin;

public:
	BGMSignal(int aGpioPin);
	void writeHigh();
	void writeLow();
};
}
#endif /* HARDWARE_BGMSIGNAL_H_ */
