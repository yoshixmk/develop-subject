#include <Test/ShowWindowTest.h>

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
	Hardware::Camera::renew();
	drawing.drawDefenseLine(camera.getRobotSideImage());
	while(1)
	{
		Hardware::Camera::renew();
		drawing.drawDefenseLine(camera.getRobotSideImage());
		window.showImage(camera.getRobotSideImage());
//		cvShowImage("Test", camera.getRobotSideImage());
		if(cv::waitKey(1) >= 0) {
			break;
		}
	}
	window.destroyWindow();
}
} /* namespace Test */
