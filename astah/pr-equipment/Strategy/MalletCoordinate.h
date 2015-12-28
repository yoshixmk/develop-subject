#ifndef STRATEGY_MALLET_COORDINATE_H
#define STRATEGY_MALLET_COORDINATE_H

#include "Strategy/Coordinate.h"

namespace Strategy
{
class MalletCoordinate : public Coordinate
{
private:
	int x_y_coordinate;


public:
	int getCoordinate();

};

}  // namespace Strategy
#endif
