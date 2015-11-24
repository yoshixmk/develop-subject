#ifndef STRATEGY_PACK_COORDINATE_H
#define STRATEGY_PACK_COORDINATE_H

#include "Strategy/Coordinate.h"
#include "Color/ColorExtraction.h"
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv/cv.h>
#include <opencv/highgui.h>

namespace Strategy
{
class PackCoordinate : public Coordinate
{
private:
	CvPoint mXYCoordinate;

	CvPoint mPreviousXYCoordinate;

	Color::ColorExtraction mColorExtractionPack;

public:
	PackCoordinate();

	CvPoint getCoordinate();

	CvPoint getPreviousCoordinate();

};

}  // namespace Strategy
#endif
