#ifndef STRATEGY_ROBOT_ACTION_H
#define STRATEGY_ROBOT_ACTION_H

#include "Hardware/MotorDriver.h"
#include "Strategy/FrequencySwitchingX.h"
#include "Strategy/FrequencySwitchingY.h"
#include "Strategy/FrequencyX.h"
#include "Strategy/FrequencyY.h"
#include "Strategy/AnomalyDetection.h"
#include "Strategy/FrameCoordinate.h"

namespace Strategy {
class RobotAction {
private:
	FrequencySwitchingX mFrequencySwitchingX;
	FrequencySwitchingY mFrequencySwitchingY;
	FrequencyX mFrequencyX;
	FrequencyY mFrequencyY;
	AnomalyDetection mAnomalyDetection;

	void moveForLimit();

	void limitCheck();

public:
	void moveToCenter(CvPoint aMalletCoordinate);

	void moveToHitBack(CvPoint aPredictedCoordinate, CvPoint aMalletCoordinate);
};

}  // namespace Strategy
#endif
