#ifndef STRATEGY_ORIGIN_RETRUN_H
#define STRATEGY_ORIGIN_RETRUN_H

#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>

#include "../Hardware/ProximitySensor.h"
#include "Hardware/Photomicrosensor.h"
#include "Strategy/RobotAction.h"

namespace Strategy
{
class OriginRetrun
{
private:
	RobotAction robotAction;
	Hardware::Proximity sensor proximity sensor;
	Hardware::Photomicrosensor photomicrosensor;

public:
	void instruct();

};

}  // namespace Strategy
#endif
