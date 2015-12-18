#ifndef COLOR_ROBOT_SIDE_HOCKEY_TABLE_MASKING_H
#define COLOR_ROBOT_SIDE_HOCKEY_TABLE_MASKING_H

#include "Masking.h"
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv/cv.h>
#include <opencv/highgui.h>

namespace Color {
class RobotSideHockeyTableMasking: public Masking {
private:
	IplImage* mRobotSideHockeyTableImage;
	TwoImageSynthesis mTwoImageSynthesis;

public:
	RobotSideHockeyTableMasking();
//	~RobotSideHockeyTableMasking();
	IplImage* mask();
};

}  // namespace Color
#endif
