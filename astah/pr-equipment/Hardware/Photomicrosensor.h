#ifndef HARDWARE_PHOTOMICROSENSOR_H
#define HARDWARE_PHOTOMICROSENSOR_H

namespace Hardware
{
class Photomicrosensor
{
private:
	int gpio_pin;


public:
	bool readLevel();

};

}  // namespace Hardware
#endif
