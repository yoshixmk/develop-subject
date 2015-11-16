#include "Camera.h"

namespace Hardware
{

Camera::Camera(int aCameraNumber, int aWidth=160, int aHeight=120)
{
	mCameraNumber = aCameraNumber;
	mWidth = aWidth;
	mHeight = aHeight;
	mCvCapture = cvCaptureFromCAM(mCameraNumber);
	mCameraImage = cvQueryFrame(mCvCapture);
}

void Camera::setSize(int width, int height)
{
}

int Camera::getCameraImage()
{
	return 0;
}
}  // namespace Hardware
