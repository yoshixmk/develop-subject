#ifndef UI_MAIN_H
#define UI_MAIN_H

#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>

#include "Hardware/RaspberryPiSignal.h"
#include "Debug/WindowManagement.h"
#include "UI/Mode.h"

namespace UI
{
class Main
{
private:
	Mode mode;
	Hardware::RaspberryPiSignal raspberryPiSignal;
	Debug::WindowManagement windowManagement;

public:
	void main();

};

}  // namespace UI
#endif
