#ifndef STRATEGY_MALLET_COORDINATE_H
#define STRATEGY_MALLET_COORDINATE_H

#include "Strategy/Coordinate.h"
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv/cv.h>
#include <opencv/highgui.h>

namespace Strategy
{
class MalletCoordinate : public Coordinate
{
private:
	CvPoint mXYCoordinate;


public:
	CvPoint getCoordinate();

};

}  // namespace Strategy
#endif
