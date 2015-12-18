#ifndef STRATEGY_LOCUS_H
#define STRATEGY_LOCUS_H

#include "Coordinate.h"
#include "RandomPositionCoordinate.h"
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv/cv.h>
#include <opencv/highgui.h>

namespace Strategy {
class Locus {
private:
	double mAInclination;

	double mBIntercept;

	bool mIsRandom;

	Coordinate mPositionalCoordinate;
	RandomPositionCoordinate mRandomPositionCoordinate;

public:
	void calculateLocus(CvPoint aCoordinate1, CvPoint aCoordinate2);

	double getAInclination();

	double getBIntercept();

};

}  // namespace Strategy
#endif
