#include <pigpio.h>

#include "Timer.h"

namespace Hardware
{
void Timer::setTimer(double notification_time)
{
	this->notification_time = notification_time;
	start_time = time_time();
	now_time = time_time();
}

bool Timer::getAlarm()
{
	double passed_time;

	now_time = time_time();
	passed_time=now_time-start_time;
	std::cout<< passed_time <<std::endl;

	if(passed_time >= notification_time){
		std::cout << "timer_alarm_true" << std::endl;
		return true;
	}
	else{
		//std::cout << "timer_alarm_false" << std::endl;
		return false;
	}
}
}  // namespace Hardware
