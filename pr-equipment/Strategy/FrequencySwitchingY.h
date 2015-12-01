#ifndef STRATEGY_FREQUENCYSWITCHINGY_H_
#define STRATEGY_FREQUENCYSWITCHINGY_H_

#include "FrequencySwitching.h"

namespace Strategy
{

class FrequencySwitchingY: public FrequencySwitching
{
public:
	FrequencySwitchingY(char aYaxis='Y');

	~FrequencySwitchingY();

	void setOutputInformation(char aDirection, double aTime);

	void output();

	void stop();

	int getCurrentFrequency();
};

} /* namespace Strategy */

#endif /* STRATEGY_FREQUENCYSWITCHINGY_H_ */
