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
	FrequencySwitching::output();
}

void FrequencySwitchingY::stop()
{
	FrequencySwitching::stop();
}

int FrequencySwitchingY::getCurrentFrequency()
{
	return FrequencySwitching::getCurrentFrequency();
}

} /* namespace Strategy */
