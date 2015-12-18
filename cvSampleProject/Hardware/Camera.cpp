#include "Camera.h"

namespace Hardware
{
IplImage* Camera::mHumanSideImage;
IplImage* Camera::mRobotSideImage;
CvCapture* Camera::mCvCapture0;
CvCapture* Camera::mCvCapture1;
int Camera::mWidth;
int Camera::mHeight;
Camera::Camera(int aWidth, int aHeight)
{
	const int FPS = 30;
	mWidth = aWidth;
	mHeight = aHeight;
	if(!mCvCapture0)
	{
		mCvCapture0 = cvCreateCameraCapture(0);
		cvSetCaptureProperty(mCvCapture0, CV_CAP_PROP_FPS, FPS);
		setSize(aWidth, aHeight);
	}
	if(!mCvCapture1)
	{
		mCvCapture1 = cvCreateCameraCapture(1);
		cvSetCaptureProperty(mCvCapture1, CV_CAP_PROP_FPS, FPS);
		setSize(aWidth, aHeight);
	}

    if(mCvCapture0 == NULL || mCvCapture1 == NULL){
		std::cout << "Camera Capture FAILED" << std::endl;
		exit(-1);
	}
    renew();
}

void Camera::setSize(int aWidth, int aHeight)
{
	cvSetCaptureProperty(mCvCapture0, CV_CAP_PROP_FRAME_WIDTH,aWidth);
	cvSetCaptureProperty(mCvCapture0, CV_CAP_PROP_FRAME_HEIGHT,aHeight);
	cvSetCaptureProperty(mCvCapture1, CV_CAP_PROP_FRAME_WIDTH,aWidth);
	cvSetCaptureProperty(mCvCapture1, CV_CAP_PROP_FRAME_HEIGHT,aHeight);
	mWidth = aWidth;
	mHeight = aHeight;
}

int Camera::getWidth()
{
	return mWidth;
}

int Camera::getHeight()
{
	return mHeight;
}

IplImage* Camera::getRobotSideImage()
{
	return mRobotSideImage;
}

IplImage* Camera::getHumanSideImage()
{
	return mHumanSideImage;
}

void Camera::renew()
{
	mRobotSideImage = cvQueryFrame(mCvCapture0);
	mHumanSideImage = cvQueryFrame(mCvCapture1);
}

}  // namespace Hardware
