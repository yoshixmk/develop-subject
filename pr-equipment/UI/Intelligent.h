#ifndef UI_INTELLIGENT_H
#define UI_INTELLIGENT_H

#include "Hardware/PushSwitch.h"

namespace UI
{
class Intelligent
{
private:
	bool strong_or_weak;

	Hardware::PushSwitch pushSwitch[2];

public:
	void chooseStrong();

	void chooseWeak();

	bool isStrong();

	bool isWeak();

};

}  // namespace UI
#endif
