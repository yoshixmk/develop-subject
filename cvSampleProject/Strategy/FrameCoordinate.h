#ifndef STRATEGY_FRAME_COORDINATE_H
#define STRATEGY_FRAME_COORDINATE_H

#include "Coordinate.h"
#include <opencv/cv.h>
#include <opencv/highgui.h>

namespace Strategy {
class FrameCoordinate: public Coordinate {
private:
	//座標はすべて枠の内側
	CvPoint mUpperLeftF;

	CvPoint mLowerLeftF;

	CvPoint mUpperRightF;

	CvPoint mLowerRightF;

	CvPoint mUpperLeftG;

	CvPoint mLowerLeftG;

	CvPoint mUpperRightG;

	CvPoint mLowerRightG;

	CvPoint mRobotGoalLeft;

	CvPoint mRobotGoalRight;

public:
	FrameCoordinate();

	CvPoint getUpperLeftF();

	CvPoint getLowerLeftF();

	CvPoint getUpperRightF();

	CvPoint getLowerRightF();

	CvPoint getUpperLeftG();

	CvPoint getLowerLeftG();

	CvPoint getUpperRightG();

	CvPoint getLowerRightG();

	CvPoint getRobotGoalLeft();

	CvPoint getRobotGoalRight();

};

}  // namespace Strategy
#endif
