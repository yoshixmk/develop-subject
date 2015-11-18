#ifndef HARDWARE_CAMERA_H
#define HARDWARE_CAMERA_H

#include <pigpio.h>
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <iostream>

namespace Hardware
{
class Camera
{
private:
	int mWidth;

	int mHeight;

public:
	static IplImage* mRobotSideImage;
	static IplImage* mHumanSideImage;
	static CvCapture* mCvCapture0;
	static CvCapture* mCvCapture1;

	Camera(int aWidth=160, int aHeight=120);

	void setSize(int aWidth, int aHeight);

	IplImage* getRobotSideImage();
	IplImage* getHumanSideImage();
};

}  // namespace Hardware
#endif
