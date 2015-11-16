#ifndef HARDWARE_BGMSIGNAL_H_
#define HARDWARE_BGMSIGNAL_H_

#include<pigpio.h>

namespace Hardware
{
class BGMSignal
{
private:
	int mGpioPin;

public:
	BGMSignal(int aGpioPin);
	bool readLevel();
};
}
#endif /* HARDWARE_BGMSIGNAL_H_ */
