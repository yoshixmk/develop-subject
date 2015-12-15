#ifndef HARDWARE_SERIAL_H_
#define HARDWARE_SERIAL_H_

#include <pigpio.h>
#include <iostream>
#include <cstdlib>

namespace Hardware {

class Serial {
private:
	int mHandle;
	int mIsRead;
//	char mInput[2];
	void serialOpen();
	void serialClose();

public:
	Serial();
	virtual ~Serial();
	int serialRead(char* buf, int bytes);
	int serialDataAvailable();
};

} /* namespace Hardware */

#endif /* HARDWARE_SERIAL_H_ */
