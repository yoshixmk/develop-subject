#ifndef HARDWARE_TIMER_H
#define HARDWARE_TIMER_H

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
