#include <Strategy/FrequencyX.h>

namespace Strategy {

FrequencyX::FrequencyX(char aXaxis) :Frequency(aXaxis)
{
	mXaxis = aXaxis;
}

FrequencyX::~FrequencyX()
{
}

void FrequencyX::output100(char aDirection){
	int output_frequency = 100;
	if(mCurrentFrequency != output_frequency){
		mCurrentFrequency = output_frequency;
		mMotorDriverX->setPulse(mCurrentFrequency);
		if(aDirection=='R'){
			mMotorDriverX->setCwCcw(1);
		}
		else if(aDirection=='L'){
			mMotorDriverX->setCwCcw(0);
		}
		mMotorDriverX->output();
	}
}

void FrequencyX::output313(char aDirection){
	int output_frequency = 313;
	if(mCurrentFrequency != output_frequency){
		mCurrentFrequency = output_frequency;
		mMotorDriverX->setPulse(mCurrentFrequency);
		if(aDirection=='R'){
			mMotorDriverX->setCwCcw(1);
		}
		else if(aDirection=='L'){
			mMotorDriverX->setCwCcw(0);
		}
		mMotorDriverX->output();
	}
}

void FrequencyX::output1000(char aDirection){
	int output_frequency = 1000;
	if(mCurrentFrequency != output_frequency){
		mCurrentFrequency = output_frequency;
		mMotorDriverX->setPulse(mCurrentFrequency);
		if(aDirection=='R'){
			mMotorDriverX->setCwCcw(1);
		}
		else if(aDirection=='L'){
			mMotorDriverX->setCwCcw(0);
		}
		mMotorDriverX->output();
	}
}
void FrequencyX::stop(){
	mMotorDriverX->stopOutput();
}

} /* namespace Strategy */
