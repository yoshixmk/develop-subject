#ifndef HARDWARE_TIMER_H
#define HARDWARE_TIMER_H

#include <time.h>
#include <iostream>
#include <pigpio.h>

namespace Hardware
{
class Timer
{
private:
	double startTime;
	double nowTime;
	double notificationTime;

public:
	void setTimer(double aNotificationTime);
	bool getAlarm();
};

}  // namespace Hardware
#endif
