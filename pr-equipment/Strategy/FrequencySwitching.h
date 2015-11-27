#ifndef STRATEGY_FREQUENCY_SWITCHING_H
#define STRATEGY_FREQUENCY_SWITCHING_H

#include "Hardware/MotorDriver.h"
#include "Hardware/Timer.h"
#include <iostream>
#include <cstdlib>

namespace Strategy {
class FrequencySwitching {
private:
	int mCurrentFrequency;
	char mXaxisOrYaxis;
	char mTargetDirection;//X: 'L' or 'R' | Y: 'U' or 'D'
	char mNowDirection;
	double mTargetTime;

	Hardware::MotorDriver *mMotorDriverX;
	Hardware::MotorDriver *mMotorDriverY1;
	Hardware::MotorDriver *mMotorDriverY2;
	Hardware::Timer mTimer;

	int mFrequencyIndex;
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
