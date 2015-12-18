#include "ColorTest.h"

namespace Test {

ColorTest::ColorTest() {
}

void ColorTest::twoImageSynthesisTest() {
	std::cout << "TwoImageSynthesis_test" << std::endl;
	Color::TwoImageSynthesis twoImageSynthesis;

//	cvNamedWindow("AllRound", CV_WINDOW_AUTOSIZE);
	cvNamedWindow("NonDistortion", CV_WINDOW_AUTOSIZE);
	while(1)
	{
		Hardware::Camera::renew();
//		cvShowImage("AllRound", twoImageSynthesis.synthesize());
		cvShowImage("NonDistortion", twoImageSynthesis.synthesizeNonDistortion());
		if(cv::waitKey(1) >= 0) {
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
		cvSaveImage("hockeyTablemasking.png", hockeyTableMasking.mask());
		if(cv::waitKey(1) >= 0) {
			break;
		}
	}
}

void ColorTest::robotSideHockeyTableMaskingTest()
{
	std::cout<<"RobotSideHockeyTableMasking_test"<<std::endl;
	Color::RobotSideHockeyTableMasking robotSideHockeyTableMasking;

	cvNamedWindow("RobotSideHockeyTableMasking", CV_WINDOW_AUTOSIZE);

	while(1)
	{
		Hardware::Camera::renew();
		cvShowImage("RobotSideHockeyTableMasking", robotSideHockeyTableMasking.mask());
		if(cv::waitKey(1) >= 0) {
			break;
		}
	}
}

void ColorTest::perspectiveTransformationTest()
{
	std::cout<<"PerspectiveTransformation_test"<<std::endl;
	Color::PerspectiveTransformation perspectiveTransformation;
	cvNamedWindow("PerspectiveTransformationR", CV_WINDOW_AUTOSIZE);
	cvNamedWindow("PerspectiveTransformationH", CV_WINDOW_AUTOSIZE);
	IplImage* robotSideImage;
	IplImage* humanSideImage;
	while(1)
	{
		Hardware::Camera::renew();
		robotSideImage = perspectiveTransformation.transformRobotSideImage();
		humanSideImage = perspectiveTransformation.transformHumanSideImage();
		cvShowImage("PerspectiveTransformationR", robotSideImage);
		cvShowImage("PerspectiveTransformationH", humanSideImage);
		if(cv::waitKey(1) >= 0) {
			break;
		}
	}
}

void ColorTest::colorExtractionTest()
{
	std::cout<<"ColorExtraction_test"<<std::endl;
	cvNamedWindow("ColorExtractionAll", CV_WINDOW_AUTOSIZE);
	cvNamedWindow("ColorExtractionR", CV_WINDOW_AUTOSIZE);

	Color::ColorExtraction colorExtractionMallet;
	Color::ColorExtraction colorExtractionPack;
	colorExtractionMallet.setMalletHSV();
	colorExtractionPack.setPackHSV();
	while(1)
	{
		Hardware::Camera::renew();
		cvShowImage("ColorExtractionAll", colorExtractionMallet.extractRobotSideHockeyTable());
		cvShowImage("ColorExtractionR", colorExtractionPack.extractHockeyTable());
		if(cv::waitKey(1) >= 0) {
			break;
		}
	}
}

} /* namespace Test */
