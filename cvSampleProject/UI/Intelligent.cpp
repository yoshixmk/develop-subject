#include "Intelligent.h"

namespace UI {

Intelligent::Intelligent() :mPushSwitchStrong(10), mPushSwitchWeak(11)
{
	//default = strong
	mStrongOrWeak = true;
}

void Intelligent::renew()
{
	if(mPushSwitchStrong.readLevel() == 1){
		mStrongOrWeak = true;
	}
	else if(mPushSwitchWeak.readLevel() == 1){
		mStrongOrWeak = false;
	}
}

bool Intelligent::isStrong()
{
	return mStrongOrWeak;
}

bool Intelligent::isWeak()
{
	return !mStrongOrWeak;
}
}  // namespace UI
