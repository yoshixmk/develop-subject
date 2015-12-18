#include "Drawing.h"

namespace ShowWindow {

void Drawing::drawPack(IplImage* aImage) {
	CvPoint drawPoint = mPackCoordinate.getCoordinate();
	cvCircle(aImage, drawPoint, Hardware::Camera::getHeight() / 10, CV_RGB(0,0,255), 6, 8, 0);
}

void Drawing::drawMallet(IplImage* aImage) {
	CvPoint drawPoint = mMalletCoordinate.getCoordinate();
	cvCircle(aImage, drawPoint, Hardware::Camera::getHeight() / 10, CV_RGB(0,0,255), 6, 8, 0);
}

void Drawing::drawDefenseLine(IplImage* aImage) {
	cvLine(aImage, cvPoint(Hardware::Camera::getWidth(), Hardware::Camera::getHeight() * 2 - 30), cvPoint(0, Hardware::Camera::getHeight() * 2 - 30), cvScalar(255,255,0), 2);
}

void Drawing::drawPackLocus(IplImage* aImage) {
	mLocus.calculateLocus(mPackCoordinate.getCoordinate(), mPackCoordinate.getPreviousCoordinate());
	if(mLocus.getAInclination() < 0){
		cvLine(aImage, mPackCoordinate.getCoordinate(), cvPoint(mFrameCoordinate.getLowerLeftF().x, mLocus.getAInclination() * mFrameCoordinate.getLowerLeftF().x + mLocus.getBIntercept()), cvScalar(0, 255, 255), 2);
	}
	else{
		cvLine(aImage, mPackCoordinate.getCoordinate(), cvPoint(mFrameCoordinate.getLowerRightF().x, mLocus.getAInclination() * mFrameCoordinate.getLowerRightF().x + mLocus.getBIntercept()), cvScalar(0, 255, 255), 2);
	}
}
}  // namespace ShowWindow
