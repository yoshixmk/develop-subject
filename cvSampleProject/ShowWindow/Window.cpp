#include "Window.h"

namespace ShowWindow {

void Window::showImage(IplImage* image) {
	cvShowImage(mCharWindowname, image);
}

void Window::destroyWindow() {
	cvDestroyAllWindows();
}

Window::Window(std::string aWindowName)
{
	mWindowName = aWindowName;
	mCharWindowname = mWindowName.c_str();
	cvNamedWindow(mCharWindowname, CV_WINDOW_AUTOSIZE);
}
}  // namespace ShowWindow
