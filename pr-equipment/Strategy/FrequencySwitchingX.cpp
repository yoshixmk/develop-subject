#include <Strategy/FrequencySwitchingX.h>

namespace Strategy {

FrequencySwitchingX::FrequencySwitchingX(char aXaxis) :FrequencySwitching(aXaxis)
{
}

FrequencySwitchingX::~FrequencySwitchingX()
{
}

void FrequencySwitchingX::setOutputInformation(char aDirection, double aTime)
{
	FrequencySwitching::setOutputInformation(aDirection, aTime);
}

void FrequencySwitchingX::output()
{
	double now_time = mTimer.getOperatingTime();
	int i;
	//加速
	for(i=0; i<4; i++){
		if(now_time < 3.0 * (i+1)){ //本番0.05s
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

void FrequencySwitchingX::stop()
{
	FrequencySwitching::stop();
}

int FrequencySwitchingX::getCurrentFrequency()
{
	return FrequencySwitching::getCurrentFrequency();
}

} /* namespace Strategy */
