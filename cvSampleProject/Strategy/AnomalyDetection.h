#ifndef STRATEGY_ANOMALY_DETECTION_H
#define STRATEGY_ANOMALY_DETECTION_H

#include "Hardware/LimitSwitch.h"

namespace Strategy {
class AnomalyDetection {
private:
	Hardware::LimitSwitch limitSwitch;

public:
	AnomalyDetection();
	bool detect();

};

}  // namespace Strategy
#endif
