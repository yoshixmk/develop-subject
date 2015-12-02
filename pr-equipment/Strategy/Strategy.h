#ifndef STRATEGY_STRATEGY_H
#define STRATEGY_STRATEGY_H

#include "Strategy/OriginRetrun.h"
#include "Strategy/RobotAction.h"
#include "Strategy/Locus.h"
#include "Strategy/Coordinate.h"

namespace Strategy
{
class Strategy
{
private:
	OriginRetrun originRetrun;
	RobotAction robotAction;
	Locus locus;
	Coordinate positionalCoordinate;

public:
	virtual void initialize()=0;

	virtual void execute(int strength)=0;

	virtual void terminate()=0;

};

}  // namespace Strategy
#endif
