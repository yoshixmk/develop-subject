#ifndef TEST_STRATEGYTEST_H
#define TEST_STRATEGYTEST_H

#include "Strategy/AnomalyDetection.h"
#include "Strategy/PackCoordinate.h"
#include "Strategy/MalletCoordinate.h"
#include "Strategy/FrameCoordinate.h"
#include <iostream>
#include <pigpio.h>

namespace Test
{
class StrategyTest
{
private:

public:
	StrategyTest();
	void anomalyDetectionTest();
	void packCoordinateTest();
	void malletCoordinateTest();
	void frameCoordinateTest();

};

}  // namespace Test
#endif
