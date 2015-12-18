#ifndef SHOWWINDOW_WINDOW_MANAGEMENT_H
#define SHOWWINDOW_WINDOW_MANAGEMENT_H

#include "Window.h"
#include "Drawing.h"

namespace ShowWindow {
class WindowManagement {
private:
	Window window0;
	Window window1;
	Window window2;
	Window window3;
//	Window window;
	Drawing drawing;
	Color::TwoImageSynthesis twoImageSynthesis;

public:
	WindowManagement();
	void manage();

};

}  // namespace ShowWindow
#endif
