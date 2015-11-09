#ifndef STRATEGY_OFFENSE_DEFENSE_STRATEGY_H
#define STRATEGY_OFFENSE_DEFENSE_STRATEGY_H

#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>

#include "Strategy/Strategy.h"

namespace Strategy
{
class OffenseDefenseStrategy : public Strategy
{
public:
	void initialize();

	void execute(int strength);

	void terminate();

};

}  // namespace Strategy
#endif
