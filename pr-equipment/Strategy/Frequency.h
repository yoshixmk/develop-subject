#ifndef STRATEGY_FREQUENCY_H_
#define STRATEGY_FREQUENCY_H_

#include "Hardware/MotorDriver.h"
#include "Hardware/Timer.h"
#include <iostream>
#include <cstdlib>

namespace Strategy {

//周波数固定で、出力する。
class Frequency {
private:
	char mXaxisOrYaxis;

protected:
	double mTargetTime;
	int mCurrentFrequency;
	Hardware::MotorDriver *mMotorDriverX;
	Hardware::MotorDriver *mMotorDriverY1;
	Hardware::MotorDriver *mMotorDriverY2;
	Hardware::Timer mTimer;

public:
	Frequency(char aXaxisOrYaxis);
	virtual ~Frequency();
	void output100(char aDirection);
	void output313(char aDirection);
	void output1000(char aDirection);
};

} /* namespace Strategy */

#endif /* STRATEGY_FREQUENCY_H_ */
