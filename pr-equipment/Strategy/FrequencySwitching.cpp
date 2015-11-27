#include "FrequencySwitching.h"

namespace Strategy
{

FrequencySwitching::FrequencySwitching(char aXaxisOrYaxis)
{
	mXaxisOrYaxis = aXaxisOrYaxis;
	mCurrentFrequency = 400;
	mTargetDirection = 'R';
	mNowDirection = 'R';
	mTargetTime = 0;
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

void FrequencySwitching::setOutputInformation(char aTargetDirection, double aTargetTime)
{
	mTargetDirection = aTargetDirection;
	mTargetTime = aTargetTime;
	mTimer.resetStartOperatingTime();
}

void FrequencySwitching::output()
{
	int frequency_acceleration[] = {1000, 1250, 2000, 2500};
	int frequency_deceleration[] = {2500, 2000, 1250, 1000, 625, 500, 400, 313};
	double now_time = mTimer.getOperatingTime();
	int i;
	for(i=0; i<4; i++){
		if(now_time < 1.0 * (i+1)){ //本番0.05s
			if(mCurrentFrequency != frequency_acceleration[i]){
				mCurrentFrequency = frequency_acceleration[i];
				mMotorDriverX->setPulse(mCurrentFrequency);
				mMotorDriverX->setCwCcw(1);
			}
			break;
		}
	}
//	if(mTargetDirection == 'L')

	mMotorDriverX->output();
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
