#ifndef COLOR_TWO_IMAGE_SYNTHESIS_H
#define COLOR_TWO_IMAGE_SYNTHESIS_H

#include "../Hardware/Camera.h"
#include "PerspectiveTransformation.h"
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
	Color::PerspectiveTransformation perspectiveTransformation;
	cv::Mat mMatSynthesisImage;
	cv::Mat mMatNonDistortionImage;

public:
	TwoImageSynthesis();
	IplImage* synthesize();
	IplImage* synthesizeNonDistortion();

};

}  // namespace Color
#endif
