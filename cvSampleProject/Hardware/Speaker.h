#ifndef HARDWARE_SPEAKER_H
#define HARDWARE_SPEAKER_H

#include <stdio.h>
#include <string>
#include <stdlib.h>
#include <iostream>
#include <signal.h>

namespace Hardware {
class Speaker {
private:
	std::string mSoundTrack;

	bool mIsRepeat;

	static void signalHandler(int aSignal);

public:
	void setSoundTrack(std::string aSoundTrack, bool aIsRepeat);

	void emitSound();

	void stopSound();

};

}  // namespace Hardware
#endif
