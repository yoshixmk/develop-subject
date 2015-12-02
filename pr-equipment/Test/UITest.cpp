#include "UITest.h"

namespace Test {

UITest::UITest() {
	// TODO Auto-generated constructor stub

}

void UITest::intelligentTest()
{
	std::cout<<"intelligent Test"<<std::endl;
	UI::Intelligent inteligent;
	while(1){
		inteligent.renew();
//		if(inteligent.isStrong()){
//			std::cout<<"Strong."<<std::endl;
//		}
//		else{
//			std::cout<<"Not Strong."<<std::endl;
//		}
		if(inteligent.isWeak()){
			std::cout<<"Weak."<<std::endl;
		}
		else{
			std::cout<<"Not Weak."<<std::endl;
		}
		if(cv::waitKey(1) >= 0) {
			break;
		}
	}
}

void UITest::soundTest()
{
	std::cout<<"sound Test"<<std::endl;
	Hardware::RaspberryPiSignal raspberryPiSignal(8);
	UI::Sound sound;

	sound.emitSettingModeSound();

	if(raspberryPiSignal.readLevel()==0){
		std::cout<<"setting mode"<<std::endl;
	}
	else{
		std::cout<<"play mode"<<std::endl;
	}
}
} /* namespace Color */
