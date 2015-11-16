#ifndef HARDWARE_CAMERA_H
#define HARDWARE_CAMERA_H

#include <pigpio.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

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
	Camera(int aWidth, int aHeight, int aCameraNumber);

	void setSize(int width, int height);

	int getCameraImage();

};

}  // namespace Hardware
#endif
