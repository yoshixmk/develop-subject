#ifndef STRATEGY_ROBOT_ACTION_H
#define STRATEGY_ROBOT_ACTION_H

#include "Hardware/MotorDriver.h"
#include "Strategy/FrequencySwitching.h"
#include "Strategy/AnomalyDetection.h"

namespace Strategy {
class RobotAction {
private:
	FrequencySwitching frequencySwitching[3];
	Hardware::MotorDriver motorDriver;
	AnomalyDetection anomalyDetection;

public:
	bool move(int direction, int time);

	void stop(int time);

};

}  // namespace Strategy
#endif
