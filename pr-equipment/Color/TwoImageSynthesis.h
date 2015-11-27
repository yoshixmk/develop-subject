#ifndef COLOR_TWO_IMAGE_SYNTHESIS_H
#define COLOR_TWO_IMAGE_SYNTHESIS_H

#include "Hardware/Camera.h"
#include "Color/PerspectiveTransformation.h"
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
	Color::PerspectiveTransformation mPerspectiveTransformation;
	cv::Mat mMatSynthesisImage;
	cv::Mat mMatNonDistortionImage;
	IplImage* mSynthesisImage;
	IplImage* mImgRobotSide;
	IplImage* mImgHumanSide;

public:
	TwoImageSynthesis();
	~TwoImageSynthesis();
	IplImage* synthesize();
	IplImage* synthesizeNonDistortion();
};

}  // namespace Color
#endif
