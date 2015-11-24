#include "StrategyTest.h"

namespace Test
{
StrategyTest::StrategyTest()
{

}

void StrategyTest::anomalyDetectionTest()
{
	std::cout << "!!!anomalyDetection Test!!!" << std::endl;
	Strategy::AnomalyDetection anomalyDetectionTest;

	std::cout << anomalyDetectionTest.detect() <<std::endl;
}

void StrategyTest::packCoordinateTest()
{
	std::cout << "!!!packCoordinate Test!!!" << std::endl;

	Hardware::Camera::renew();
	Strategy::PackCoordinate packCoordinate;
	std::cout << "X: "<< packCoordinate.getCoordinate().x << std::endl;
	std::cout << "Y: "<< packCoordinate.getCoordinate().y << std::endl;
//	packCoordinate.getPreviousCoordinate();
}




}  // namespace Test
