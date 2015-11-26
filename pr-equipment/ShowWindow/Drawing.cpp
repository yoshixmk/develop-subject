#include "Drawing.h"

namespace ShowWindow {

void Drawing::drawPack(IplImage* aimage) {

}

void Drawing::drawMallet(IplImage* aimage) {
}

void Drawing::drawDefenseLine(IplImage* aimage) {
	cvLine(aimage, cvPoint(Hardware::Camera::getWidth(), Hardware::Camera::getHeight() - 30), cvPoint(0, Hardware::Camera::getHeight() - 30), cvScalar(255,255,0), 2);
}

void Drawing::drawPackLocus(IplImage* aimage) {
}
}  // namespace ShowWindow
