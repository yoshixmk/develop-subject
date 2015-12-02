#ifndef STRATEGY_FREQUENCYY_H_
#define STRATEGY_FREQUENCYY_H_

#include <Strategy/Frequency.h>

namespace Strategy {

class FrequencyY: public Frequency {
private:
	char mYaxis;

public:
	FrequencyY(char aYaxis = 'Y');
	virtual ~FrequencyY();
	void output100(char aDirection);
	void output313(char aDirection);
	void output1000(char aDirection);
	void stop();
};

} /* namespace Strategy */

#endif /* STRATEGY_FREQUENCYY_H_ */
