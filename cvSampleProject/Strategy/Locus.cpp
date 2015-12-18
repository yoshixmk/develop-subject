#include "Locus.h"

namespace Strategy
{

void Locus::calculateLocus(CvPoint aCoordinate1, CvPoint aCoordinate2)
{
	if((aCoordinate2.x - aCoordinate1.x) != 0){
		mAInclination = (aCoordinate2.y - aCoordinate1.y) / (aCoordinate2.x - aCoordinate1.x);
		mBIntercept = aCoordinate2.y - mAInclination * aCoordinate2.x;
	}
	else{
		mAInclination = 0;
		mBIntercept = 0;
	}
}

double Locus::getAInclination()
{
	return mAInclination;
}

double Locus::getBIntercept()
{
	return mBIntercept;
}
}  // namespace Strategy
