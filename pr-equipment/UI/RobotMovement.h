#ifndef UI_ROBOTMOVEMENT_H_
#define UI_ROBOTMOVEMENT_H_

#include "Hardware/Serial.h"
#include "Hardware/MotorDriver.h"
#include <pigpio.h>
#include <signal.h>
#include <iostream>

namespace UI {

class RobotMovement {
private:
	static void signalHandler(int aSignal);

public:
	RobotMovement();
	~RobotMovement();
	void move();
};

} /* namespace UI */

#endif /* UI_ROBOTMOVEMENT_H_ */
