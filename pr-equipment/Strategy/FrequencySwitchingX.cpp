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
	int array_num = sizeof(mFrequency)/sizeof(mFrequency[0]);

	//加速
	if(now_time < mTargetTime){
		//減速のときのために周波数のインデックスを更新
		if(now_time < 3.0 * (array_num)){ //本番0.05s
			for(i=0; i<array_num; i++){
				if(mFrequency[i] == mCurrentFrequency){
					mFrequencyIndex = i;
				}
			}
		}
		for(i=0; i<array_num; i++){
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
		mMovingStopTimer.resetStartOperatingTime();//停止動作に移った場合のため
	}
	else{ //減速
		double now_stop_time = mMovingStopTimer.getOperatingTime();
		for(i=0; i<=mFrequencyIndex; i++){
			if(now_stop_time <= 3.0 * i){ //本番0.05s
				if(mCurrentFrequency != mFrequency[mFrequencyIndex - i]){
					mCurrentFrequency = mFrequency[mFrequencyIndex - i];
					mMotorDriverX->setPulse(mCurrentFrequency);

					if(mTargetDirection == 'R'){
						mMotorDriverX->setCwCcw(1);
					}
					if(mTargetDirection == 'L'){
						mMotorDriverX->setCwCcw(0);
					}
					mMotorDriverX->output();
				}
				break;
			}
			else if(3.0 * (array_num - 1) < now_stop_time){//本番0.05s
				mCurrentFrequency = 0;
				mMotorDriverX->stopOutput();
			}
		}
		std::cout << mCurrentFrequency << std::endl;
	}
}

void FrequencySwitchingX::stop()
{
	//減速
	int array_num = sizeof(mFrequency)/sizeof(mFrequency[0]);
	int i;
	double now_time = mMovingStopTimer.getOperatingTime();
	for(i=mFrequencyIndex; 0<=i; i--){
		if(now_time < 3.0 * (array_num-1 - i)){ //本番0.05s
			mCurrentFrequency = mFrequency[i];
			mMotorDriverX->setPulse(mCurrentFrequency);
			mMotorDriverX->setCwCcw(1);
			break;
		}
		else if(now_time < 3.0 * (array_num-1)){//本番0.05s
			mCurrentFrequency = 0;
			mMotorDriverX->stopOutput();
		}
	}

	std::cout << mCurrentFrequency << std::endl;
}

int FrequencySwitchingX::getCurrentFrequency()
{
	return FrequencySwitching::getCurrentFrequency();
}

} /* namespace Strategy */
