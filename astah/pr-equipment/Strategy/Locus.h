#ifndef STRATEGY_LOCUS_H
#define STRATEGY_LOCUS_H

#include "Strategy/Coordinate.h"
#include "Strategy/RandomPositionCoordinate.h"

namespace Strategy
{
class Locus
{
private:
	int a_inclination;

	int b_intercept;

	bool isRandom;

	Coordinate positionalCoordinate;
	RandomPositionCoordinate randomPositionCoordinate;

public:
	void calculateLocus(int coordinate1, int coordinate2);

	double getaAInclination();

	double getBIntercept();

};

}  // namespace Strategy
#endif
