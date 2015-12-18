#ifndef COLOR_PERSPECTIVETRANSFORMATION_H_
#define COLOR_PERSPECTIVETRANSFORMATION_H_

#include <opencv2/highgui/highgui.hpp>
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include "../Hardware/Camera.h"

namespace Color
{

class PerspectiveTransformation
{

private:
	Hardware::Camera mCamera;
	IplImage* mRobotSideImage;
	IplImage* mHumanSideImage;

public:
	PerspectiveTransformation();
	IplImage* transformRobotSideImage();
	IplImage* transformHumanSideImage();
};

} /* namespace Color */

#endif /* COLOR_PERSPECTIVETRANSFORMATION_H_ */
