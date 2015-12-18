#ifndef TEST_SHOWWINDOWTEST_H_
#define TEST_SHOWWINDOWTEST_H_
#include "../ShowWindow/Window.h"
#include "../ShowWindow/Drawing.h"
#include "../ShowWindow/WindowManagement.h"
#include "../Color/TwoImageSynthesis.h"
#include "../Hardware/Camera.h"

namespace Test {

class ShowWindowTest {
public:
	ShowWindowTest();
	void windowTest();
	void drawingTest();
	void manageTest();
};

} /* namespace Test */

#endif /* TEST_SHOWWINDOWTEST_H_ */
