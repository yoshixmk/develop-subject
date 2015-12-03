#ifndef STRATEGY_FRAME_COORDINATE_H
#define STRATEGY_FRAME_COORDINATE_H

#include "Strategy/Coordinate.h"
#include <opencv/cv.h>
#include <opencv/highgui.h>

namespace Strategy {
class FrameCoordinate: public Coordinate {
private:
	//座標はすべて枠の内側
	static CvPoint mUpperLeftF;

	static CvPoint mLowerLeftF;

	static CvPoint mUpperRightF;

	static CvPoint mLowerRightF;

	static CvPoint mUpperLeftG;

	static CvPoint mLowerLeftG;

	static CvPoint mUpperRightG;

	static CvPoint mLowerRightG;

	static CvPoint mRobotGoalLeft;

	static CvPoint mRobotGoalRight;

public:
	FrameCoordinate();

	static CvPoint getUpperLeftF();

	static CvPoint getLowerLeftF();

	static CvPoint getUpperRightF();

	static CvPoint getLowerRightF();

	static CvPoint getUpperLeftG();

	static CvPoint getLowerLeftG();

	static CvPoint getUpperRightG();

	static CvPoint getLowerRightG();

	static CvPoint getRobotGoalLeft();

	static CvPoint getRobotGoalRight();

};

}  // namespace Strategy
#endif
