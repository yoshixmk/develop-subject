#ifndef UI_SOUND_H
#define UI_SOUND_H

#include "Hardware/Speaker.h"
#include "UI/PackSpeed.h"
#include "Hardware/BGMSignal.h"

namespace UI {
class Sound {
private:
	//Hardware::Speaker mSpeaker;
	//PackSpeed mPackSpeed;
	Hardware::BGMSignal mBGMSignal;

public:
	Sound();
	void emitSettingModeSound();
	void emitPlayModeSound();

};

}  // namespace UI
#endif
