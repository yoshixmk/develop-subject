#ifndef STRATEGY_FREQUENCY_SWITCHING_H
#define STRATEGY_FREQUENCY_SWITCHING_H

#include "../Hardware/MotorDriver.h"
#include "../Hardware/Timer.h"
#include <iostream>
#include <cstdlib>

namespace Strategy {
class FrequencySwitching {
private:
	int mCurrentFrequency;

	char mXaxisOrYaxis;

	Hardware::MotorDriver *mMotorDriverX;
	Hardware::MotorDriver *mMotorDriverY1;
	Hardware::MotorDriver *mMotorDriverY2;
	Hardware::Timer mTimer;

public:
	//FrequencySwitching();
	FrequencySwitching(char aXaxisOrYaxis);

	~FrequencySwitching();

	void output(bool isNormalRotation, int aOperatingTime);

	void stop();

	int getCurrentFrequency();

};

}  // namespace Strategy
#endif
