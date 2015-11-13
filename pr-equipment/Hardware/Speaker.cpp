#include "Speaker.h"

namespace Hardware
{

void Speaker::setSoundTrack(std::string aSoundTrack, bool aIsRepeat)
{
	mSoundTrack = aSoundTrack;
	mIsRepeat = aIsRepeat;
}

void Speaker::emitSound()
{
	std::string player_command = "mpg321 ";

	if(mIsRepeat == true){
		system((player_command + "-q -l0 " + mSoundTrack).c_str());
	}
	else{
		system((player_command + "-q " + mSoundTrack).c_str());
	}

	std::cout << (mSoundTrack + "-q play").c_str() <<std::endl;
}

void Speaker::stopSound()
{
	std::string player_command = "mpg321 ";
	system(("killall " + player_command).c_str());
}
}  // namespace Hardware
