#ifndef STRATEGY_PACK_COORDINATE_H
#define STRATEGY_PACK_COORDINATE_H

#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>

#include "Strategy/Coordinate.h"

namespace Strategy
{
class PackCoordinate : public Coordinate
{
private:
	int x_y_coordinate;

	int previous_x_y_coordinate;


public:
	int getCoordinate();

	int getPreviousCoordinate();

};

}  // namespace Strategy
#endif
