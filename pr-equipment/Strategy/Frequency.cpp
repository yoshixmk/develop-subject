#include <Strategy/Frequency.h>

namespace Strategy {

Frequency::Frequency(char aXaxisOrYaxis) {
	mXaxisOrYaxis = aXaxisOrYaxis;
	mCurrentFrequency = 0;
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

Frequency::~Frequency() {
	if(mXaxisOrYaxis == 'X'){
		delete mMotorDriverX;
	}
	else if(mXaxisOrYaxis == 'Y'){
		delete mMotorDriverY1;
		delete mMotorDriverY2;
	}
}

//aDirection -> X: 'L' or 'R' | Y: 'U' or 'D' で指定
void Frequency::output100(char aDirection)
{
	int output_frequency = 100;
	if(mXaxisOrYaxis == 'X'){
		if(mCurrentFrequency != output_frequency){
			mCurrentFrequency = output_frequency;
			mMotorDriverX->setPulse(mCurrentFrequency);
			if(aDirection == 'R'){
				mMotorDriverX->setCwCcw(1);
			}
			else if(aDirection == 'L'){
				mMotorDriverX->setCwCcw(0);
			}
			mMotorDriverX->output();
		}
	}
	else if(mXaxisOrYaxis == 'Y'){
		if(mCurrentFrequency != output_frequency){
			mCurrentFrequency = output_frequency;
			mMotorDriverY1->setPulse(mCurrentFrequency);
			mMotorDriverY2->setPulse(mCurrentFrequency);
			if(aDirection == 'U'){
				mMotorDriverY1->setCwCcw(1);
				mMotorDriverY2->setCwCcw(0);
			}
			if(aDirection == 'D'){
				mMotorDriverY1->setCwCcw(0);
				mMotorDriverY2->setCwCcw(1);
			}
			mMotorDriverY1->output();
			mMotorDriverY2->output();
		}
	}
}

void Frequency::output313(char aDirection)
{
	int output_frequency = 313;
	if(mXaxisOrYaxis == 'X'){
		if(mCurrentFrequency != output_frequency){
			mCurrentFrequency = output_frequency;
			mMotorDriverX->setPulse(mCurrentFrequency);
			if(aDirection == 'R'){
				mMotorDriverX->setCwCcw(1);
			}
			else if(aDirection == 'L'){
				mMotorDriverX->setCwCcw(0);
			}
			mMotorDriverX->output();
		}
	}
	else if(mXaxisOrYaxis == 'Y'){
		if(mCurrentFrequency != output_frequency){
			mCurrentFrequency = output_frequency;
			mMotorDriverY1->setPulse(mCurrentFrequency);
			mMotorDriverY2->setPulse(mCurrentFrequency);
			if(aDirection == 'U'){
				mMotorDriverY1->setCwCcw(1);
				mMotorDriverY2->setCwCcw(0);
			}
			if(aDirection == 'D'){
				mMotorDriverY1->setCwCcw(0);
				mMotorDriverY2->setCwCcw(1);
			}
			mMotorDriverY1->output();
			mMotorDriverY2->output();
		}
	}
}

void Frequency::output1000(char aDirection)
{
	int output_frequency = 1000;
	if(mXaxisOrYaxis == 'X'){
		if(mCurrentFrequency != output_frequency){
			mCurrentFrequency = output_frequency;
			mMotorDriverX->setPulse(mCurrentFrequency);
			if(aDirection == 'R'){
				mMotorDriverX->setCwCcw(1);
			}
			else if(aDirection == 'L'){
				mMotorDriverX->setCwCcw(0);
			}
			mMotorDriverX->output();
		}
	}
	else if(mXaxisOrYaxis == 'Y'){
		if(mCurrentFrequency != output_frequency){
			mCurrentFrequency = output_frequency;
			mMotorDriverY1->setPulse(mCurrentFrequency);
			mMotorDriverY2->setPulse(mCurrentFrequency);
			if(aDirection == 'U'){
				mMotorDriverY1->setCwCcw(1);
				mMotorDriverY2->setCwCcw(0);
			}
			if(aDirection == 'D'){
				mMotorDriverY1->setCwCcw(0);
				mMotorDriverY2->setCwCcw(1);
			}
			mMotorDriverY1->output();
			mMotorDriverY2->output();
		}
	}
}

} /* namespace Strategy */
