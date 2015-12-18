#include "StrategyTest.h"

namespace Test {
StrategyTest::StrategyTest() {

}

//void StrategyTest::anomalyDetectionTest()
//{
//	std::cout << "!!!anomalyDetection Test!!!" << std::endl;
//	Strategy::AnomalyDetection anomalyDetectionTest;
//
//	std::cout << anomalyDetectionTest.detect() << std::endl;
//}

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

void StrategyTest::frameCoordinateTest()
{
	std::cout << "!!!frameCoordinate Test!!!" << std::endl;
	Strategy::FrameCoordinate frameCoordinate;
	std::cout << "X: "<< frameCoordinate.getUpperLeftF().x << std::endl;
	std::cout << "Y: "<< frameCoordinate.getUpperLeftF().y << std::endl;

	std::cout << "X: "<< frameCoordinate.getLowerLeftF().x << std::endl;
	std::cout << "Y: "<< frameCoordinate.getLowerLeftF().y << std::endl;

	std::cout << "X: "<< frameCoordinate.getUpperRightF().x << std::endl;
	std::cout << "Y: "<< frameCoordinate.getUpperRightF().y << std::endl;

	std::cout << "X: "<< frameCoordinate.getLowerRightF().x << std::endl;
	std::cout << "Y: "<< frameCoordinate.getLowerRightF().y << std::endl;

	std::cout << "X: "<< frameCoordinate.getUpperLeftG().x << std::endl;
	std::cout << "Y: "<< frameCoordinate.getUpperLeftG().y << std::endl;

	std::cout << "X: "<< frameCoordinate.getLowerLeftG().x << std::endl;
	std::cout << "Y: "<< frameCoordinate.getLowerLeftG().y << std::endl;

	std::cout << "X: "<< frameCoordinate.getUpperRightG().x << std::endl;
	std::cout << "Y: "<< frameCoordinate.getUpperRightG().y << std::endl;

	std::cout << "X: "<< frameCoordinate.getLowerRightG().x << std::endl;
	std::cout << "Y: "<< frameCoordinate.getLowerRightG().y << std::endl;

	std::cout << "X: "<< frameCoordinate.getRobotGoalLeft().x << std::endl;
	std::cout << "Y: "<< frameCoordinate.getRobotGoalLeft().y << std::endl;

	std::cout << "X: "<< frameCoordinate.getRobotGoalRight().x << std::endl;
	std::cout << "Y: "<< frameCoordinate.getRobotGoalRight().y << std::endl;
}

void StrategyTest::locusTest()
{
	std::cout << "!!!Locus Test!!!" << std::endl;
	Hardware::Camera::renew();
	Strategy::PackCoordinate packCoordinate;
	Strategy::Locus locus;
	while(1){
		Hardware::Camera::renew();
		CvPoint coordinate = packCoordinate.getCoordinate();
		CvPoint previousCoordinate = packCoordinate.getPreviousCoordinate();
		locus.calculateLocus(coordinate, previousCoordinate);
		double a_inclination = locus.getAInclination();
		double b_intercept = locus.getBIntercept();
		std::cout << "a: " << a_inclination << std::endl;
		std::cout << "b: " << b_intercept << std::endl;
		if(cv::waitKey(1) >= 0) {
			break;
		}
	}
}

}  // namespace Test
