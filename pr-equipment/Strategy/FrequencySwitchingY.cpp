#include <Strategy/FrequencySwitchingY.h>

namespace Strategy {

FrequencySwitchingY::FrequencySwitchingY(char aYaxis) :FrequencySwitching(aYaxis)
{
}

FrequencySwitchingY::~FrequencySwitchingY()
{
}

void FrequencySwitchingY::setOutputInformation(char aDirection, double aTime)
{
	FrequencySwitching::setOutputInformation(aDirection, aTime);
}

void FrequencySwitchingY::output()
{
	double now_time = mTimer.getOperatingTime();
	int i;
	int array_num = sizeof(mFrequency)/sizeof(mFrequency[0]);

	//加速
	if(now_time < mTargetTime){
		//減速のときのために周波数のインデックスを更新
		if(now_time < 0.05 * (array_num)){ //本番0.05s
			for(i=0; i<array_num; i++){
				if(mFrequency[i] == mCurrentFrequency){
					mFrequencyIndex = i;
				}
			}
		}
		for(i=0; i<array_num; i++){
			if(now_time < 0.05 * (i+1)){ //本番0.05s
				if(mCurrentFrequency != mFrequency[i]){
					mCurrentFrequency = mFrequency[i];
					mMotorDriverY1->setPulse(mCurrentFrequency);
					mMotorDriverY2->setPulse(mCurrentFrequency);

					if(mTargetDirection == 'U'){
						mMotorDriverY1->setCwCcw(1);
						mMotorDriverY2->setCwCcw(0);
					}
					if(mTargetDirection == 'D'){
						mMotorDriverY1->setCwCcw(0);
						mMotorDriverY2->setCwCcw(1);
					}
				}
				break;
			}
		}
		mMotorDriverY1->output();
		mMotorDriverY2->output();
		mMovingStopTimer.resetStartOperatingTime();//停止動作に移った場合のため
	}
	else{ //減速
		double now_stop_time = mMovingStopTimer.getOperatingTime();
		for(i=0; i<=mFrequencyIndex; i++){
			if(now_stop_time <= 0.05 * i){ //本番0.05s
				if(mCurrentFrequency != mFrequency[mFrequencyIndex - i]){
					mCurrentFrequency = mFrequency[mFrequencyIndex - i];
					mMotorDriverY1->setPulse(mCurrentFrequency);
					mMotorDriverY2->setPulse(mCurrentFrequency);

					if(mTargetDirection == 'U'){
						mMotorDriverY1->setCwCcw(1);
						mMotorDriverY2->setCwCcw(0);
					}
					if(mTargetDirection == 'D'){
						mMotorDriverY1->setCwCcw(0);
						mMotorDriverY2->setCwCcw(1);
					}
					mMotorDriverY1->output();
					mMotorDriverY2->output();
				}
				break;
			}
			else if(0.05 * (array_num - 1) < now_stop_time){//本番0.05s
				mCurrentFrequency = 0;
				mMotorDriverY1->stopOutput();
				mMotorDriverY2->stopOutput();
			}
		}
//		std::cout << mCurrentFrequency << std::endl;
	}
}

void FrequencySwitchingY::stop()
{
	//減速
	int array_num = sizeof(mFrequency)/sizeof(mFrequency[0]);
	int i;
	double now_stop_time = mMovingStopTimer.getOperatingTime();
	for(i=0; i<=mFrequencyIndex; i++){
		if(now_stop_time <= 0.05 * i){ //本番0.05s
			if(mCurrentFrequency != mFrequency[mFrequencyIndex - i]){
				mCurrentFrequency = mFrequency[mFrequencyIndex - i];
				mMotorDriverY1->setPulse(mCurrentFrequency);
				mMotorDriverY2->setPulse(mCurrentFrequency);

				if(mTargetDirection == 'U'){
					mMotorDriverY1->setCwCcw(1);
					mMotorDriverY2->setCwCcw(0);
				}
				if(mTargetDirection == 'D'){
					mMotorDriverY1->setCwCcw(0);
					mMotorDriverY2->setCwCcw(1);
				}
				mMotorDriverY1->output();
				mMotorDriverY2->output();
			}
			break;
		}
		else if(0.05 * (array_num - 1) < now_stop_time){//本番0.05s
			mCurrentFrequency = 0;
			mMotorDriverY1->stopOutput();
			mMotorDriverY2->stopOutput();
		}
	}

//	std::cout << mCurrentFrequency << std::endl;
}

int FrequencySwitchingY::getCurrentFrequency()
{
	return FrequencySwitching::getCurrentFrequency();
}

} /* namespace Strategy */
