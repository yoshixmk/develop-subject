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

	cv::Mat mMatSynthesisImage;

public:
	TwoImageSynthesis();
	IplImage* synthesize();

};

}  // namespace Color
#endif
