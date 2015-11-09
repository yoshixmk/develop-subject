#ifndef HARDWARE_SPEAKER_H
#define HARDWARE_SPEAKER_H

#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>

namespace Hardware
{
class Speaker
{
public:
	void emitSoundEffect();

	void stopSoundEffect();

	void emitBGM();

	void stopBGM();

};

}  // namespace Hardware
#endif
