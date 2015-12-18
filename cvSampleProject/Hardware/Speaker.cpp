#include "Speaker.h"

namespace Hardware {

/* シグナル受信/処理 */
void Speaker::signalHandler(int aSignal) {
	std::cout << "SIGNAL Keybord Interrupt, END" << std::endl;
	exit(0);
}

void Speaker::setSoundTrack(std::string aSoundTrack, bool aIsRepeat) {
	mSoundTrack = aSoundTrack;
	mIsRepeat = aIsRepeat;
}

void Speaker::emitSound() {
	std::string player_command = "mpg321 ";

	if (signal(SIGINT, &signalHandler) == SIG_ERR) {
		std::cout << "I could not set up signal. finished" << std::endl;
		system(("sudo killall " + player_command).c_str());
		exit(1);
	}

	if (mIsRepeat == true) {
		system(
				("sudo " + player_command + "-q -l0 " + mSoundTrack + " &").c_str());
//		system("mpg321 -q -l0 hisyo.mp3 &");
	} else {
		system(("sudo " + player_command + "-q " + mSoundTrack + " &").c_str());
//		system("mpg321 -q -l0 hisyo.mp3 &");
	}

	std::cout << (mSoundTrack + " play!").c_str() << std::endl;
}

void Speaker::stopSound() {
	system(("sudo pkill -f " + mSoundTrack).c_str());
}

}  // namespace Hardware
