#ifndef COLOR_TWO_IMAGE_SYNTHESIS_H
#define COLOR_TWO_IMAGE_SYNTHESIS_H

#include "Hardware/Camera.h"
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

namespace Color
{
class TwoImageSynthesis
{
private:
	const int CAM_PIX_WIDTH;
	const int CAM_PIX_HEIGHT;

	Hardware::Camera mCamera;

public:
	TwoImageSynthesis();
	IplImage*  synthesize();

};

}  // namespace Color
#endif
