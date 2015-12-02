#ifndef STRATEGY_FREQUENCYX_H_
#define STRATEGY_FREQUENCYX_H_

#include <Strategy/Frequency.h>

namespace Strategy {

class FrequencyX: public Frequency {
private:
	char mXaxis;

public:
	FrequencyX(char aXaxis = 'X');
	virtual ~FrequencyX();
	void output100(char aDirection);
	void output313(char aDirection);
	void output1000(char aDirection);
	void stop();
};

} /* namespace Strategy */

#endif /* STRATEGY_FREQUENCYX_H_ */
