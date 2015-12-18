#include "FrequencySwitching.h"

namespace Strategy
{
//FrequencySwitching::FrequencySwitching() :mMotorDriver(25,18), mMotorDriverY1(23, 7), mMotorDriverY2(24,12)
//{
//
//}

FrequencySwitching::FrequencySwitching(char aXaxisOrYaxis)
{
	mXaxisOrYaxis = aXaxisOrYaxis;
	mCurrentFrequency = 1000;
	if(mXaxisOrYaxis == 'X'){
		mMotorDriverX = new Hardware::MotorDriver(25, 18);
	}
	else if(mXaxisOrYaxis == 'Y'){
		mMotorDriverY1 = new Hardware::MotorDriver(23, 7);
		mMotorDriverY2 = new Hardware::MotorDriver(24, 12);
	}
	else{
		std::cout<<"mXaxisOrYaxis is Bad argument in FrequencySwitching Class"<<std::endl;
		std::exit(2);
	}
}

FrequencySwitching::~FrequencySwitching()
{
	if(mXaxisOrYaxis == 'X'){
		delete mMotorDriverX;
	}
	else if(mXaxisOrYaxis == 'Y'){
		delete mMotorDriverY1;
		delete mMotorDriverY2;
	}
}

void FrequencySwitching::output(bool isNormalRotation, int aOperatingTime)
{
	int frequency[] = {400, 500, 625, 1000, 1250, 2000, 2500, 5000, 10000};
	mTimer.setTimer(0.03);
	if(mTimer.getAlarm()){
		mCurrentFrequency = frequency[4];
	}
}

void FrequencySwitching::stop()
{
	mCurrentFrequency = 0;
	if(mXaxisOrYaxis == 'X'){
		mMotorDriverX->stopOutput();
	}
	else if(mXaxisOrYaxis == 'Y'){
		mMotorDriverY1->stopOutput();
		mMotorDriverY2->stopOutput();
	}
}

int FrequencySwitching::getCurrentFrequency()
{
	return mCurrentFrequency;
}
}  // namespace Strategy
