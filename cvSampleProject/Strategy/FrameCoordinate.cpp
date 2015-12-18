#include "FrameCoordinate.h"

namespace Strategy
{

FrameCoordinate::FrameCoordinate()
{
	mUpperLeftF = cvPoint(21, 33);

	mLowerLeftF = cvPoint(19, 219);

	mUpperRightF = cvPoint(139, 30);

	mLowerRightF = cvPoint(138, 219);

	mUpperLeftG = cvPoint(33, 22);

	mLowerLeftG = cvPoint(27, 227);

	mUpperRightG = cvPoint(128, 22);

	mLowerRightG = cvPoint(127, 228);

	mRobotGoalLeft = cvPoint(57, 229);

	mRobotGoalRight = cvPoint(100, 229);
}

CvPoint FrameCoordinate::getUpperLeftF()
{
	return mUpperLeftF;
}

CvPoint FrameCoordinate::getLowerLeftF()
{
	return mLowerLeftF;
}

CvPoint FrameCoordinate::getUpperRightF()
{
	return mUpperRightF;
}

CvPoint FrameCoordinate::getLowerRightF()
{
	return mLowerRightF;
}

CvPoint FrameCoordinate::getUpperLeftG()
{
	return mUpperLeftG;
}

CvPoint FrameCoordinate::getLowerLeftG()
{
	return mLowerLeftG;
}

CvPoint FrameCoordinate::getUpperRightG()
{
	return mUpperRightG;
}

CvPoint FrameCoordinate::getLowerRightG()
{
	return mLowerRightG;
}

CvPoint FrameCoordinate::getRobotGoalLeft()
{
	return mRobotGoalLeft;
}

CvPoint FrameCoordinate::getRobotGoalRight()
{
	return mRobotGoalRight;
}
}  // namespace Strategy
