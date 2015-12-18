#ifndef UI_PACK_SPEED_H
#define UI_PACK_SPEED_H

#include "Hardware/Timer.h"
#include "Hardware/PhotoelectricSensor.h"

namespace UI {
class PackSpeed {
private:
	int speed;

	Hardware::Timer timer;
	Hardware::PhotoelectricSensor photoelectricSensor;

public:
	double getSpeed();

};

}  // namespace UI
#endif
