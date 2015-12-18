#include "ShowWindowTest.h"

namespace Test {

ShowWindowTest::ShowWindowTest() {
	// TODO Auto-generated constructor stub

}

void ShowWindowTest::windowTest()
{
	Hardware::Camera camera;
	ShowWindow::Window window("Test");
	Hardware::Camera::renew();
	window.showImage(camera.getRobotSideImage());
	while(1)
	{
		Hardware::Camera::renew();
		window.showImage(camera.getRobotSideImage());



//		cvShowImage("Test", camera.getRobotSideImage());
		if(cv::waitKey(1) >= 0) {
			break;
		}
	}
	window.destroyWindow();
}

void ShowWindowTest::drawingTest()
{
	Hardware::Camera camera;

	ShowWindow::Window window("Test");
	ShowWindow::Drawing drawing;
	Color::TwoImageSynthesis twoImageSynthesis;
	IplImage* testImage = cvCreateImage(cvSize(Hardware::Camera::getWidth(), Hardware::Camera::getHeight()), IPL_DEPTH_8U, 3);
	while(1)
	{
		Hardware::Camera::renew();
		testImage = twoImageSynthesis.synthesizeNonDistortion();
		drawing.drawDefenseLine(testImage);
		drawing.drawPack(testImage);
		drawing.drawMallet(testImage);
//		drawing.drawPackLocus(testImage);
		window.showImage(testImage);
//		cvShowImage("Test", camera.getRobotSideImage());
		if(cv::waitKey(1) >= 0) {
			break;
		}
	}
	window.destroyWindow();
}

//void ShowWindowTest::manageTest()
//{
//	ShowWindow::WindowManagement manage;
//	manage.manage();
//}
} /* namespace Test */
