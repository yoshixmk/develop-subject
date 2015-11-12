#ifndef HARDWARE_TIMER_H
#define HARDWARE_TIMER_H

#include <time.h>

#include <iostream>

namespace Hardware
{
class Timer
{
private:
	double start_time;
	double now_time;
	double notification_time;

public:
	void setTimer(double notification_time);
	bool getAlarm();
};

}  // namespace Hardware
#endif
