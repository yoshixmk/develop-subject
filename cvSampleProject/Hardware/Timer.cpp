#include "Timer.h"

namespace Hardware {
void Timer::setTimer(double aNotificationTime) {
	mNotificationTime = aNotificationTime;
	mStartTime = time_time();
	mNowTime = time_time();
}

bool Timer::getAlarm() {
	double passed_time;

	//現在時刻、経過時刻を取得、計算
	mNowTime = time_time();
	passed_time = mNowTime - mStartTime;
	//std::cout<< passed_time <<std::endl;
	//アラーム判定
	if (passed_time >= mNotificationTime) {
		//std::cout << "timer_alarm_true" << std::endl;
		return true;
	} else {
		//std::cout << "timer_alarm_false" << std::endl;
		return false;
	}
}
}  // namespace Hardware
