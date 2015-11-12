#ifndef TEST_HARDWARETEST_H
#define TEST_HARDWARETEST_H

#include "Hardware/Timer.h"
#include "Hardware/RaspberryPiSignal.h"
#include "Hardware/PhotoelectricSensor.h"
#include "Hardware/Photomicrosensor.h"
#include "Hardware/LimitSwitch.h"
#include"Hardware/ProximitySensor.h"
#include "Hardware/PushSwitch.h"
#include <iostream>
#include <pigpio.h>

namespace Test
{
class HardwareTest
{
private:

public:
	HardwareTest();
	void timerTest();
	void raspberryPiSignalTest();
	void photoelectricSensor();
	void photomicrosensor();
	void limitSwitch();
	void proximitySensor();
	void pushSwitch();
};

}  // namespace HardwareTest
#endif
