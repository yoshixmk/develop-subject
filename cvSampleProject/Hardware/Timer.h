#ifndef HARDWARE_TIMER_H
#define HARDWARE_TIMER_H

#include <time.h>
#include <iostream>
#include <pigpio.h>

namespace Hardware {
class Timer {
private:
	double mStartTime;
	double mNowTime;
	double mNotificationTime;

public:
	void setTimer(double aNotificationTime);
	bool getAlarm();
};

}  // namespace Hardware
#endif
