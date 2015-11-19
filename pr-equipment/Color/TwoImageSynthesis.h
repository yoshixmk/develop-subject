#ifndef COLOR_TWO_IMAGE_SYNTHESIS_H
#define COLOR_TWO_IMAGE_SYNTHESIS_H

#include "Hardware/Camera.h"
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

namespace Color
{
class TwoImageSynthesis
{
private:
	Hardware::Camera mCamera;
	IplImage* mSynthesisImage;
	IplImage* imgRobotSide;
	IplImage* imgHumanSide;
	cv::Mat matFrameRobotSide;
	cv::Mat matFrameHumanSide;
	cv::Mat dstImgV;

public:
	TwoImageSynthesis();
	~TwoImageSynthesis();
	IplImage* synthesize();

};

}  // namespace Color
#endif
