#include <pigpio.h>

#include "Timer.h"

namespace Hardware
{

void Timer::setTimer(int notification_time)
{
	this->notification_time = notification_time;
	start_time = clock();
	now_time = clock();
}

bool Timer::getAlarm()
{
	now_time = clock();

	if (gpioInitialise() < 0)
	{
		std::cout << "pigpio initialisation failed." << std::endl;
	}
	else
	{
		std::cout << "pigpio initialised okay." << std::endl;
	}
	//double now_s = (now_time - start_time) * 100 / CLOCKS_PER_SEC;
	//std::cout << pi_time << std::endl;

	/*if(now_s >= notification_time){
		std::cout << "###true" << std::endl;
		return true;
	}
	else{
		std::cout << "###faluse" << std::endl;*/
		return true;
	//}
}
}  // namespace Hardware
