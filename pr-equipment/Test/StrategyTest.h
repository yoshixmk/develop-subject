#ifndef TEST_STRATEGYTEST_H
#define TEST_STRATEGYTEST_H

#include "Strategy/AnomalyDetection.h"
#include "Strategy/PackCoordinate.h"
#include "Strategy/MalletCoordinate.h"
#include "Strategy/FrameCoordinate.h"
#include "Strategy/Locus.h"
#include "Strategy/FrequencySwitching.h"
#include "Strategy/FrequencySwitchingX.h"
#include "Strategy/FrequencySwitchingY.h"
#include "Strategy/Frequency.h"
#include "Strategy/FrequencyX.h"
#include "Strategy/FrequencyY.h"
#include "Strategy/RobotAction.h"
#include <iostream>
#include <pigpio.h>

namespace Test {
class StrategyTest {
private:

public:
	StrategyTest();
	void anomalyDetectionTest();
	void packCoordinateTest();
	void malletCoordinateTest();
	void frameCoordinateTest();
	void locusTest();
	void frequencySwitchingTest();
	void frequencySwitching_X_Test();
	void frequencySwitching_Y_Test();
	void frequencyTest();
	void frequency_X_Test();
	void frequency_Y_Test();
	void robotActionTest();
};

}  // namespace Test
#endif
