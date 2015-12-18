#include "Sound.h"

namespace UI
{
Sound::Sound() : mBGMSignal(13)
{

}

void Sound::emitSettingModeSound()
{
	mBGMSignal.writeLow();
}

void Sound::emitPlayModeSound()
{
	mBGMSignal.writeHigh();
}
}  // namespace UI
