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

void StrategyTest::malletCoordinateTest()
{
	std::cout << "!!!malletCoordinate Test!!!" << std::endl;

	Hardware::Camera::renew();
	Strategy::MalletCoordinate malletCoordinate;
	while(1){
		Hardware::Camera::renew();
		std::cout << "X: "<< malletCoordinate.getCoordinate().x << std::endl;
		std::cout << "Y: "<< malletCoordinate.getCoordinate().y << std::endl;
		if(cv::waitKey(1) >= 0) {
			break;
		}
	}
}


}  // namespace Test
