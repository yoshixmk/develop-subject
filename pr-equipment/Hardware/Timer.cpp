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
		return true;
	} else {
		return false;
	}
}

double Timer::getOperatingTime()
{
	double now_time;
	double passed_time;
	//現在時刻、経過時刻を取得、計算
	now_time = time_time();
	passed_time = now_time - mStartOperatingTime;
	return passed_time;
}

void Timer::resetStartOperatingTime()
{
	mStartOperatingTime = time_time();
}

}  // namespace Hardware
