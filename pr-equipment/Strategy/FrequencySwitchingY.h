#ifndef STRATEGY_FREQUENCYSWITCHINGY_H_
#define STRATEGY_FREQUENCYSWITCHINGY_H_

#include "FrequencySwitching.h"

namespace Strategy
{

class FrequencySwitchingY: public FrequencySwitching
{
public:
	FrequencySwitchingY(char aXaxisOrYaxis);
	~FrequencySwitchingY();
};

} /* namespace Strategy */

#endif /* STRATEGY_FREQUENCYSWITCHINGY_H_ */
