#include "Camera.h"

namespace Hardware
{
IplImage* Camera::mHumanSideImage;
IplImage* Camera::mRobotSideImage;
CvCapture* Camera::mCvCapture0;
CvCapture* Camera::mCvCapture1;
Camera::Camera(int aWidth, int aHeight)
{
	const int FPS = 60;

	if(!mCvCapture0)
	{
		mCvCapture0 = cvCreateCameraCapture(0);
	}
	if(!mCvCapture1)
	{
		mCvCapture1 = cvCreateCameraCapture(1);
	}

    if(mCvCapture0 == NULL || mCvCapture1 == NULL){
		std::cout << "Camera Capture FAILED" << std::endl;
		exit(-1);
	}
	setSize(aWidth, aHeight);
	cvSetCaptureProperty(mCvCapture0, CV_CAP_PROP_FPS, FPS);
	cvSetCaptureProperty(mCvCapture1, CV_CAP_PROP_FPS, FPS);
}

void Camera::setSize(int aWidth, int aHeight)
{
	mWidth = aWidth;
	mHeight = aHeight;
	cvSetCaptureProperty(mCvCapture0, CV_CAP_PROP_FRAME_WIDTH,aWidth);
	cvSetCaptureProperty(mCvCapture0,CV_CAP_PROP_FRAME_HEIGHT,aHeight);
	cvSetCaptureProperty(mCvCapture1, CV_CAP_PROP_FRAME_WIDTH,aWidth);
	cvSetCaptureProperty(mCvCapture1,CV_CAP_PROP_FRAME_HEIGHT,aHeight);
}

IplImage* Camera::getRobotSideImage()
{
	mRobotSideImage = cvQueryFrame(mCvCapture0);

	return mRobotSideImage;
}

IplImage* Camera::getHumanSideImage()
{
	mHumanSideImage = cvQueryFrame(mCvCapture1);

	return mHumanSideImage;
}

}  // namespace Hardware
