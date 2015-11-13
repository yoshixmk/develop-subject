#ifndef HARDWARE_SPEAKER_H
#define HARDWARE_SPEAKER_H

namespace Hardware
{
class Speaker
{
public:
	void setSoundTrack(int aSoundTrack, bool aLoop);

	void emitSound();

	void stopSound();

};

}  // namespace Hardware
#endif
