#include "AnomalyDetection.h"

namespace Strategy {

AnomalyDetection::AnomalyDetection() :
		limitSwitch(5) {
}

bool AnomalyDetection::detect() {
	return limitSwitch.readLevel();
}
}  // namespace Strategy
