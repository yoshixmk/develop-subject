#ifndef UI_MAIN_H
#define UI_MAIN_H

#include "Hardware/RaspberryPiSignal.h"
#include "ShowWindow/WindowManagement.h"
#include "UI/Mode.h"

namespace UI
{
class UI
{
private:
	Mode mode;
	Hardware::RaspberryPiSignal raspberryPiSignal;
	ShowWindow::WindowManagement windowManagement;

public:
	void main();

};

}  // namespace UI
#endif
