#include "Test/HardwareTest.h"

int  main()
{
	Test::HardwareTest hardwareTest;
	//hardware_test.timerTest();
	//hardware_test.raspberryPiSignalTest();
	//hardware_test.photoelectricSensor();
	//hardware_test.photomicrosensor();
	//hardware_test.limitSwitch();
	//hardware_test.proximitySensor();
	//hardwareTest.pushSwitchTest();
	hardwareTest.moterDriverTest();
	return 0;
}

