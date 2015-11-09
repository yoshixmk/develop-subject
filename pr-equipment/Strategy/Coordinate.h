#ifndef STRATEGY_COORDINATE_H
#define STRATEGY_COORDINATE_H

#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>

#include "Color/ColorExtraction.h"

namespace Strategy
{
class Coordinate
{
private:
	int x_y_coordinate;

	Color::ColorExtraction colorExtraction;

public:
	int getCoordinate();

};

}  // namespace Strategy
#endif
