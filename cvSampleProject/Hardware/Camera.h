#ifndef HARDWARE_CAMERA_H
#define HARDWARE_CAMERA_H

//#include <pigpio.h>
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <iostream>

namespace Hardware
{
class Camera
{
private:
	static IplImage* mRobotSideImage;
	static IplImage* mHumanSideImage;
	static CvCapture* mCvCapture0;
	static CvCapture* mCvCapture1;
	static int mWidth;
	static int mHeight;

public:
	Camera(int aWidth=160, int aHeight=120);
	static void setSize(int aWidth, int aHeight);
	static int getWidth();
	static int getHeight();
	static void renew();
	IplImage* getRobotSideImage();
	IplImage* getHumanSideImage();
};

}  // namespace Hardware
#endif
