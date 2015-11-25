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

} /* namespace Color */
