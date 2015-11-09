#ifndef UI_MODE_H
#define UI_MODE_H

#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>

#include "Strategy/Strategy.h"
#include "UI/Sound.h"
#include "UI/Intelligent.h"

namespace UI
{
class Mode
{
private:
	Strategy::Strategy strategy;
	Sound sound;
	Intelligent intelligent;

public:
	virtual void Execute()=0;

};

}  // namespace UI
#endif
