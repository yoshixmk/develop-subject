#include "Speaker.h"

namespace Hardware
{

/* シグナル受信/処理 */
void Speaker::sigHandler(int aSignal)
{
	std::cout << "SIGNAL Keybord Interrupt, END" <<std::endl;
    exit(0);
}

void Speaker::setSoundTrack(std::string aSoundTrack, bool aIsRepeat)
{
	mSoundTrack = aSoundTrack;
	mIsRepeat = aIsRepeat;

	if (signal(SIGINT, &sigHandler) == SIG_ERR) {
		std::cout << "I could not set up signal. finished" <<std::endl;
		exit(1);
	}
}

void Speaker::emitSound()
{
	std::string player_command = "mpg321 ";

	if(mIsRepeat == true){
		system((player_command + "-q -l0 " + mSoundTrack + " &").c_str());
	}
	else{
		system((player_command + "-q " + mSoundTrack + " &").c_str());
	}

	std::cout << (mSoundTrack + " play!").c_str() <<std::endl;
}

void Speaker::stopSound()
{
	system(("pkill -f " + mSoundTrack).c_str());
}

}  // namespace Hardware
