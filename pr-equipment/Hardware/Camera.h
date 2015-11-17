#ifndef HARDWARE_CAMERA_H
#define HARDWARE_CAMERA_H

#include <pigpio.h>
#include <opencv/cv.h>
#include <opencv/highgui.h>
//#include <opencv2/imgproc/imgproc.hpp>
//#include <opencv2/highgui/highgui.hpp>
#include <iostream>

namespace Hardware
{
class Camera
{
private:
	IplImage* mCameraImage;

	int mWidth;

	int mHeight;

	int mCameraNumber;

	CvCapture* mCvCapture;

public:
	Camera(int aCameraNumber, int aWidth=160, int aHeight=120);

	void setSize(int aWidth, int aHeight);

	IplImage* getCameraImage();
};

}  // namespace Hardware
#endif
