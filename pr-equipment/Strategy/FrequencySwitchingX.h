#ifndef STRATEGY_FREQUENCYSWITCHINGX_H_
#define STRATEGY_FREQUENCYSWITCHINGX_H_

#include "FrequencySwitching.h"

namespace Strategy {

class FrequencySwitchingX: public FrequencySwitching
{
public:
	FrequencySwitchingX(char aXaxis);

	~FrequencySwitchingX();

	void setOutputInformation(char aDirection, double aTime);

	void output();

	void stop();

	int getCurrentFrequency();
};

} /* namespace Strategy */

#endif /* STRATEGY_FREQUENCYSWITCHINGX_H_ */
