#include "WindowManagement.h"

namespace ShowWindow {

WindowManagement::WindowManagement() :window0("origin"), window1("pack"), window2("mallet"), window3("locus")
{

}


void WindowManagement::manage() {
//	Hardware::Camera camera;

	IplImage* testImage = cvCreateImage(cvSize(Hardware::Camera::getWidth(), Hardware::Camera::getHeight()*2), IPL_DEPTH_8U, 3);
	IplImage *pack, *mallet, *locus;
//	pack = cvCreateImage(cvSize(Hardware::Camera::getWidth(), Hardware::Camera::getHeight()*2), IPL_DEPTH_8U, 3);
//	mallet = cvCreateImage(cvSize(Hardware::Camera::getWidth(), Hardware::Camera::getHeight()*2), IPL_DEPTH_8U, 3);
//	locus = cvCreateImage(cvSize(Hardware::Camera::getWidth(), Hardware::Camera::getHeight()*2), IPL_DEPTH_8U, 3);
	while(1){
		Hardware::Camera::renew();
		testImage = twoImageSynthesis.synthesizeNonDistortion();
		drawing.drawDefenseLine(testImage);
		pack = mallet = locus = testImage;

//		cvCopy(testImage, pack);
//		cvCopy(testImage, mallet);
//		cvCopy(testImage, locus);

		drawing.drawPack(pack);
		drawing.drawMallet(mallet);
//		drawing.drawPackLocus(locus);

		window0.showImage(testImage);
		window1.showImage(pack);
		window2.showImage(mallet);
		window3.showImage(locus);

		if(cv::waitKey(1) >= 0) {
					break;
		}
	}
	window0.destroyWindow();
	window1.destroyWindow();
	window2.destroyWindow();
	window3.destroyWindow();
}
}  // namespace ShowWindow
