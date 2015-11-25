#ifndef TEST_UITEST_H_
#define TEST_UITEST_H_

#include "UI/Intelligent.h"
#include "Hardware/Camera.h"
#include"Hardware/RaspberryPiSignal.h"
#include"UI/Sound.h"
#include <iostream>

namespace Test {

class UITest {
public:
	UITest();
	void intelligentTest();
	void soundTest();
};

} /* namespace Color */

#endif /* TEST_UITEST_H_ */
