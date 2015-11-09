#ifndef SHOWWINDOW_WINDOW_MANAGEMENT_H
#define SHOWWINDOW_WINDOW_MANAGEMENT_H

#include "ShowWindow/Window.h"
#include "ShowWindow/Drawing.h"

namespace ShowWindow
{
class WindowManagement
{
private:
	Window window[];
	Drawing drawing;

public:
	void manage();

};

}  // namespace ShowWindow
#endif
