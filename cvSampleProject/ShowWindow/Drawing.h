#ifndef SHOWWINDOW_DRAWING_H
#define SHOWWINDOW_DRAWING_H

#include "../Hardware/Camera.h"
#include "../Strategy/PackCoordinate.h"
#include "../Strategy/MalletCoordinate.h"
#include "../Strategy/Locus.h"
#include "../Strategy/FrameCoordinate.h"

namespace ShowWindow {
class Drawing {

private:
	Strategy::PackCoordinate mPackCoordinate;

	Strategy::MalletCoordinate mMalletCoordinate;

	Strategy::Locus mLocus;

	Strategy::FrameCoordinate mFrameCoordinate;

public:
	void drawPack(IplImage* aImage);

	void drawMallet(IplImage* aImage);

	void drawDefenseLine(IplImage* aImage);

	void drawPackLocus(IplImage* aImage);
};

}  // namespace ShowWindow
#endif
