#ifndef STRATEGY_DEFENSE_STRATEGY_H
#define STRATEGY_DEFENSE_STRATEGY_H

#include "Strategy/Strategy.h"

namespace Strategy {
class DefenseStrategy: public Strategy {
public:
	void initialize();

	void execute(int strength);

	void terminate();

};

}  // namespace Strategy
#endif
