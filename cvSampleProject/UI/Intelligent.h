#ifndef UI_INTELLIGENT_H
#define UI_INTELLIGENT_H

#include "Hardware/PushSwitch.h"

namespace UI {
class Intelligent {
private:
	bool mStrongOrWeak;

	Hardware::PushSwitch mPushSwitchStrong;
	Hardware::PushSwitch mPushSwitchWeak;

public:
	Intelligent();

	void renew();

	bool isStrong();

	bool isWeak();

};

}  // namespace UI
#endif
