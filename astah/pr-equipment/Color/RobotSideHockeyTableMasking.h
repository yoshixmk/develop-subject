#ifndef COLOR_ROBOT_SIDE_HOCKEY_TABLE_MASKING_H
#define COLOR_ROBOT_SIDE_HOCKEY_TABLE_MASKING_H

#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>

#include "Color/Masking.h"

namespace Color
{
class RobotSideHockeyTableMasking : public Masking
{
private:
	int robot_side_hockey_table_image;


public:
	int mask();

};

}  // namespace Color
#endif
