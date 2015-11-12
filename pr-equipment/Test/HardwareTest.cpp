#include "HardwareTest.h"

namespace Test
{
HardwareTest::HardwareTest()
{
//	if (gpioInitialise() < 0)
//	{
//		std::cout << "pigpio initialisation failed." << std::endl;
//	}
//	else
//	{
//		std::cout << "pigpio initialised okay." << std::endl;
//	}
}

void HardwareTest::timerTest()
{
	std::cout << "!!!Timer Test!!!" << std::endl; // Timer Test start!

	Hardware::Timer timer;


	timer.setTimer(10.5);
	while(!timer.getAlarm());
	/*//while(!timer.getAlarm()){
		if(timer.getAlarm()){
			std::cout << "getAlarm() retun Bool OK." << std::endl;
		}
		else{
			std::cout << "getAlarm() retun Bool NG." << std::endl;
		}
	//}*/
}
}  // namespace HardwareTest
