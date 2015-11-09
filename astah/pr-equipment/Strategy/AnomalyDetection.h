#ifndef STRATEGY_ANOMALY_DETECTION_H
#define STRATEGY_ANOMALY_DETECTION_H

#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>

#include "Hardware/LimitSwitch.h"

namespace Strategy
{
class AnomalyDetection
{
private:
	Hardware::LimitSwitch limitSwitch[6];

public:
	bool detect();

};

}  // namespace Strategy
#endif
