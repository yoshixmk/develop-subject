#include "StrategyTest.h"

namespace Test {
StrategyTest::StrategyTest() {

}

void StrategyTest::anomalyDetectionTest() {
	std::cout << "!!!anomalyDetectionTest Test!!!" << std::endl;
	Strategy::AnomalyDetection anomalyDetectionTest;

	std::cout << anomalyDetectionTest.detect() << std::endl;
}

}  // namespace Test
