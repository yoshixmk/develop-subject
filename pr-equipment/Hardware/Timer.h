#ifndef HARDWARE_TIMER_H
#define HARDWARE_TIMER_H

#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>

namespace Hardware
{
class Timer
{
private:
	int start_time;

	int now_time;

	int notification_time;


public:
	void setTimer(int notification_time);

	bool getAlarm();

};

}  // namespace Hardware
#endif
