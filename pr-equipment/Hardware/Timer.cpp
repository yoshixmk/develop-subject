#include "Timer.h"

namespace Hardware
{
void Timer::setTimer(double aNotificationTime)
{
	this->notificationTime = aNotificationTime;
	startTime = time_time();
	nowTime = time_time();
}

bool Timer::getAlarm()
{
	double passed_time;

	//現在時刻、経過時刻を取得、計算
	nowTime = time_time();
	passed_time=nowTime-startTime;
	std::cout<< passed_time <<std::endl;
	//アラーム判定
	if(passed_time >= notificationTime){
		std::cout << "timer_alarm_true" << std::endl;
		return true;
	}
	else{
		//std::cout << "timer_alarm_false" << std::endl;
		return false;
	}
}
}  // namespace Hardware
