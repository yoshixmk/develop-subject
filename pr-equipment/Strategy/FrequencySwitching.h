#ifndef STRATEGY_FREQUENCY_SWITCHING_H
#define STRATEGY_FREQUENCY_SWITCHING_H

#include "Hardware/MotorDriver.h"
#include "Hardware/Timer.h"
#include <iostream>
#include <cstdlib>

namespace Strategy {
class FrequencySwitching {
private:
	char mXaxisOrYaxis;
	char mNowDirection;
	double mTargetTime;
	int mFrequencyIndex;

protected:
	int mCurrentFrequency;
	char mTargetDirection;//X: 'L' or 'R' | Y: 'U' or 'D'
	Hardware::MotorDriver *mMotorDriverX;
	Hardware::MotorDriver *mMotorDriverY1;
	Hardware::MotorDriver *mMotorDriverY2;
	Hardware::Timer mTimer;
	int mFrequency[4];

public:
	//FrequencySwitching();
	FrequencySwitching(char aXaxisOrYaxis);

	~FrequencySwitching();

	void setOutputInformation(char aDirection, double aTime);

	void output();

	void stop();

	int getCurrentFrequency();

};

}  // namespace Strategy
#endif
