#ifndef STRATEGY_ORIGIN_RETRUN_H
#define STRATEGY_ORIGIN_RETRUN_H

#include "Hardware/ProximitySensor.h"
#include "Hardware/Photomicrosensor.h"
#include "Strategy/RobotAction.h"

namespace Strategy {
class OriginRetrun {
private:
	RobotAction robotAction;
	Hardware::ProximitySensor proximitySensor;
	Hardware::Photomicrosensor photomicrosensor;

public:
	void instruct();

};

}  // namespace Strategy
#endif
