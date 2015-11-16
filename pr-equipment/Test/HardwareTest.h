#ifndef TEST_HARDWARETEST_H
#define TEST_HARDWARETEST_H

#include "Hardware/Timer.h"
#include "Hardware/RaspberryPiSignal.h"
#include "Hardware/PhotoelectricSensor.h"
#include "Hardware/Photomicrosensor.h"
#include "Hardware/LimitSwitch.h"
#include "Hardware/ProximitySensor.h"
#include "Hardware/PushSwitch.h"
#include "Hardware/MotorDriver.h"
#include "Hardware/Speaker.h"
#include "Hardware/BGMSignal.h"
#include <iostream>
#include <pigpio.h>
#include <signal.h>

namespace Test
{
class HardwareTest
{
private:
	static void signalHandler(int aSignal);

public:
	HardwareTest();
	~HardwareTest();
	void timerTest();
	void raspberryPiSignalTest();
	void photoelectricSensorTest();
	void photomicrosensorTest();
	void limitSwitchTest();
	void proximitySensorTest();
	void pushSwitchTest();
	void moterDriverTest();
	void speakerTest();
	void bgmSignalTest();
};

}  // namespace Test
#endif
