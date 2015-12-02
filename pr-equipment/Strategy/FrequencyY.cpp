#include <Strategy/FrequencyY.h>

namespace Strategy {

FrequencyY::FrequencyY(char aYaxis) :Frequency(aYaxis) {
	mYaxis = aYaxis;
}

FrequencyY::~FrequencyY() {
	// TODO Auto-generated destructor stub
}

void FrequencyY::output100(char aDirection)
{
	int output_frequency = 100;
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

void FrequencyY::output313(char aDirection)
{
	int output_frequency = 313;
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

void FrequencyY::output1000(char aDirection)
{
	int output_frequency = 1000;
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

void FrequencyY::stop()
{
	mMotorDriverY1->stopOutput();
	mMotorDriverY2->stopOutput();
}
} /* namespace Strategy */
