#ifndef STRATEGY_COORDINATE_H
#define STRATEGY_COORDINATE_H

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
