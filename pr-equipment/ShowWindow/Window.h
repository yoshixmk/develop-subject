#ifndef SHOWWINDOW_WINDOW_H
#define SHOWWINDOW_WINDOW_H

#include <iostream>
#include <string.h>
#include <opencv/cv.h>
#include <opencv/highgui.h>

namespace ShowWindow {
class Window {
private:
	std::string mWindowName;
	const char *mCharWindowname;

public:
	Window(std::string aWindowName);
	void showImage(IplImage* aImage);

	void destroyWindow();



};

}  // namespace ShowWindow
#endif
