#include "Test/HardwareTest.h"

int  main()
{
	Test::HardwareTest hardware_test;
	//hardware_test.timerTest();
	//hardware_test.raspberryPiSignalTest();
	//hardware_test.photoelectricSensor();
	//hardware_test.photomicrosensor();
	//hardware_test.limitSwitch();
	//hardware_test.proximitySensor();
	hardware_test.pushSwitch();
	return 0;
}

