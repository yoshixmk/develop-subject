#ifndef TEST_STRATEGYTEST_H
#define TEST_STRATEGYTEST_H

#include "Strategy/AnomalyDetection.h"
#include <iostream>
#include <pigpio.h>

namespace Test {
class StrategyTest {
private:

public:
	StrategyTest();
	void anomalyDetectionTest();

};

}  // namespace Test
#endif
