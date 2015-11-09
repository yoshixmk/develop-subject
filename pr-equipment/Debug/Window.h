#ifndef DEBUG_WINDOW_H
#define DEBUG_WINDOW_H

#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>

namespace Debug
{
class Window
{
private:
	int window_neme;


public:
	void showImage(int image);

	void destroyWindow();

};

}  // namespace Debug
#endif
