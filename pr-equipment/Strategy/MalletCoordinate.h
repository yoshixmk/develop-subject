#ifndef STRATEGY_MALLET_COORDINATE_H
#define STRATEGY_MALLET_COORDINATE_H

#include "Strategy/Coordinate.h"
#include "Color/ColorExtraction.h"
#include <opencv/cv.h>
#include <opencv/highgui.h>

namespace Strategy
{
class MalletCoordinate : public Coordinate
{
private:
	CvPoint mXYCoordinate;

public:
	MalletCoordinate();
	CvPoint getCoordinate();

};

}  // namespace Strategy
#endif
