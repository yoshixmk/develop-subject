#include "Camera.h"

namespace Hardware
{

Camera::Camera(int aCameraNumber, int aWidth, int aHeight)
{
	const int fps = 30;
	mCameraNumber = aCameraNumber;
	mCvCapture = cvCreateCameraCapture(mCameraNumber);
    if(mCvCapture == NULL){
		std::cout << "Camera Capture FAILED" << std::endl;
		exit(-1);
	}
	setSize(aWidth, aHeight);
	cvSetCaptureProperty(mCvCapture,CV_CAP_PROP_FPS,fps);
	mCameraImage = 0;
}

void Camera::setSize(int aWidth, int aHeight)
{
	mWidth = aWidth;
	mHeight = aHeight;
	cvSetCaptureProperty(mCvCapture, CV_CAP_PROP_FRAME_WIDTH,aWidth);
	cvSetCaptureProperty(mCvCapture,CV_CAP_PROP_FRAME_HEIGHT,aHeight);
}

IplImage* Camera::getCameraImage()
{
	mCameraImage = cvQueryFrame(mCvCapture);
	return mCameraImage;
}
}  // namespace Hardware
