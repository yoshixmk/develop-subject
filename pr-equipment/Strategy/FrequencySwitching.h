#ifndef STRATEGY_FREQUENCY_SWITCHING_H
#define STRATEGY_FREQUENCY_SWITCHING_H

#include "Hardware/MotorDriver.h"
#include "Hardware/Timer.h"

namespace Strategy {
class FrequencySwitching {
private:
	int current_frequency;

	int xaxis_or_yaxis;

	Hardware::MotorDriver motorDriver;
	Hardware::Timer timer;

public:
	void output();

	void setXaxis();

	void setYaxis();

	int getCurrentFrequency();

};

}  // namespace Strategy
#endif
