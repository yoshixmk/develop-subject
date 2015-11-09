#ifndef DEBUG_WINDOW_MANAGEMENT_H
#define DEBUG_WINDOW_MANAGEMENT_H

#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>

#include "Debug/Window.h"
#include "Debug/Drawing.h"

namespace Debug
{
class WindowManagement
{
private:
	Window window[];
	Drawing drawing;

public:
	void manage();

};

}  // namespace Debug
#endif
