#ifndef SHOWWINDOW_DRAWING_H
#define SHOWWINDOW_DRAWING_H

#include "Hardware/Camera.h"
#include "Strategy/PackCoordinate.h"

namespace ShowWindow {
class Drawing {
public:
	void drawPack(IplImage* aimage);

	void drawMallet(IplImage* aimage);

	void drawDefenseLine(IplImage* aimage);

	void drawPackLocus(IplImage* aimage);

};

}  // namespace ShowWindow
#endif
