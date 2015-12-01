#ifndef STRATEGY_ROBOT_ACTION_H
#define STRATEGY_ROBOT_ACTION_H

#include "Hardware/MotorDriver.h"
#include "Strategy/FrequencySwitching.h"
#include "Strategy/AnomalyDetection.h"

namespace Strategy {
class RobotAction {
private:
	FrequencySwitching mFrequencySwitching[3];
	Hardware::MotorDriver mMotorDriver;
	AnomalyDetection mAnomalyDetection;

public:
	bool move(int aDirection, int aTime);

	void stop();

};

}  // namespace Strategy
#endif
