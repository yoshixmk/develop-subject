#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>

#include "RobotAction.h"

namespace Strategy
{

bool RobotAction::move(int direction, int time)
{
	return false;
}

void RobotAction::stop(int time)
{
}
}  // namespace Strategy
