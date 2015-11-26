#include "Drawing.h"

namespace ShowWindow {

void Drawing::drawPack(IplImage* aimage) {
	Strategy::PackCoordinate packCoodinate;
	CvPoint drawpoint = packCoodinate.getCoordinate();
	CvPoint pack;
	pack = cvPoint(80, 120);
	cvCircle(aimage, pack, Hardware::Camera::getHeight() / 10, CV_RGB(0,0,255), 6, 8, 0);
}

void Drawing::drawMallet(IplImage* aimage) {
//	Strategy::MalletCoordinate malletCoodinate;
//	CvPoint drawpoint = malletCoodinate.getCoordinate();
//	cvCircle(aimage, drawpoint, Hardware::Camera::getHeight() / 10, CV_RGB(0,0,255), 6, 8, 0);
}

void Drawing::drawDefenseLine(IplImage* aimage) {
	cvLine(aimage, cvPoint(Hardware::Camera::getWidth(), Hardware::Camera::getHeight() * 2 - 30), cvPoint(0, Hardware::Camera::getHeight() * 2 - 30), cvScalar(255,255,0), 2);
}

void Drawing::drawPackLocus(IplImage* aimage) {
}
}  // namespace ShowWindow
