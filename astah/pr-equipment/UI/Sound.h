#ifndef UI_SOUND_H
#define UI_SOUND_H

#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>

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
