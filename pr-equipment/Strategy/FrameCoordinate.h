#ifndef STRATEGY_FRAME_COORDINATE_H
#define STRATEGY_FRAME_COORDINATE_H

#include "Strategy/Coordinate.h"
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv/cv.h>
#include <opencv/highgui.h>

namespace Strategy
{
class FrameCoordinate : public Coordinate
{
private:
	CvPoint mUpperLeftF;

	CvPoint mLowerLeftF;

	CvPoint mUpperRightF;

	CvPoint mLowerRightF;

	CvPoint mUpperLeftG;

	CvPoint mLowerLeftG;

	CvPoint mUpperRightG;

	CvPoint mLowerRightG;


public:
	CvPoint getUpperLeftF();

	CvPoint getLowerLeftF();

	CvPoint getUpperRightF();

	CvPoint getLowerRightF();

	CvPoint getUpperLeftG();

	CvPoint getLowerLeftG();

	CvPoint getUpperRightG();

	CvPoint getLowerRightG();

};

}  // namespace Strategy
#endif
