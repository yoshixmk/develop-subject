#include "FrequencySwitching.h"

namespace Strategy
{

FrequencySwitching::FrequencySwitching(char aXaxisOrYaxis)
{
	mFrequencyIndex=0;
	mFrequency[0] = 1000;
	mFrequency[1] = 1250;
	mFrequency[2] = 2000;
	mFrequency[3] = 2500;

	mXaxisOrYaxis = aXaxisOrYaxis;
	mCurrentFrequency = 2000;
	mNowDirection = 'R';
	mTargetTime = 0;
	if(mXaxisOrYaxis == 'X'){
		mMotorDriverX = new Hardware::MotorDriver(25, 18);
		mTargetDirection = 'R';
	}
	else if(mXaxisOrYaxis == 'Y'){
		mMotorDriverY1 = new Hardware::MotorDriver(23, 7);
		mMotorDriverY2 = new Hardware::MotorDriver(24, 12);
		mTargetDirection = 'U';
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

	int i;
	int array_num = sizeof(mFrequency)/sizeof(mFrequency[0]);
	for(i=0; i<array_num; i++){
		if(mFrequency[i] == mCurrentFrequency){
			mFrequencyIndex = i;
		}
	}
}

void FrequencySwitching::output()
{
	double now_time = mTimer.getOperatingTime();
	int i;
	//加速
	for(i=0; i<4; i++){
		if(now_time < 0.05 * (i+1)){ //本番0.05s
			if(mCurrentFrequency != mFrequency[i]){
				mCurrentFrequency = mFrequency[i];
				mMotorDriverX->setPulse(mCurrentFrequency);
				if(mTargetDirection == 'R'){
					mMotorDriverX->setCwCcw(1);
				}
				if(mTargetDirection == 'L'){
					mMotorDriverX->setCwCcw(0);
				}
			}
			break;
		}
	}


	mMotorDriverX->output();
}

void FrequencySwitching::stop()
{
	mTimer.resetStartOperatingTime();
	//減速
	int array_num = sizeof(mFrequency)/sizeof(mFrequency[0]);
	int i;
	double now_time = mTimer.getOperatingTime();
	for(i=mFrequencyIndex; 0<=i; i--){
		if(now_time < 3.0 * (array_num-1 - i)){ //本番0.05s
				mCurrentFrequency = mFrequency[i];
				mMotorDriverX->setPulse(mCurrentFrequency);
				mMotorDriverX->setCwCcw(1);
			break;
		}
	}
	std::cout << mCurrentFrequency << std::endl;

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
