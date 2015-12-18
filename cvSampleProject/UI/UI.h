#ifndef UI_UI_H
#define UI_UI_H

#include "Hardware/RaspberryPiSignal.h"
#include "ShowWindow/WindowManagement.h"
#include "UI/Mode.h"
#include <iostream>

namespace UI {
class UI {
private:
	//Mode mode;
	Hardware::RaspberryPiSignal raspberryPiSignal;
	ShowWindow::WindowManagement windowManagement;

public:
	void main();

};

}  // namespace UI
#endif
