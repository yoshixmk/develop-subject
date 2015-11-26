#include "ColorTest.h"

namespace Test {

ColorTest::ColorTest() {
}

void ColorTest::twoImageSynthesisTest() {
	std::cout << "TwoImageSynthesis_test" << std::endl;
	Color::TwoImageSynthesis twoImageSynthesis;

	cvNamedWindow("AllRound", CV_WINDOW_AUTOSIZE);
	while (1) {
		Hardware::Camera::renew();
		cvShowImage("AllRound", twoImageSynthesis.synthesize());
		if (cv::waitKey(1) >= 0) {
			break;
		}
	}
}

void ColorTest::hockeyTableMaskingTest() {
	std::cout << "HockeyTableMasking_test" << std::endl;
	Color::HockeyTableMasking hockeyTableMasking;

	cvNamedWindow("HockeyTableMacking", CV_WINDOW_AUTOSIZE);
	while (1) {
		Hardware::Camera::renew();
		cvShowImage("HockeyTableMacking", hockeyTableMasking.mask());
		if (cv::waitKey(1) >= 0) {
			break;
		}
	}
}

} /* namespace Test */
