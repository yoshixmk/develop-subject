#ifndef UI_SOUND_H
#define UI_SOUND_H

#include "Hardware/Speaker.h"
#include "UI/PackSpeed.h"

namespace UI
{
class Sound
{
private:
	Hardware::Speaker speaker;
	PackSpeed packSpeed;

public:
	void emitSettingModeSound();

	void emitPlayModeSound();

};

}  // namespace UI
#endif
