#ifndef COLOR_HOCKEY_TABLE_MASKING_H
#define COLOR_HOCKEY_TABLE_MASKING_H

#include "Masking.h"
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv/cv.h>
#include <opencv/highgui.h>

namespace Color
{
class HockeyTableMasking : public Masking
{
private:
	IplImage* mHockeyTableImage;
	TwoImageSynthesis mTwoImageSynthesis;

public:
	HockeyTableMasking();
//	~HockeyTableMasking();
	IplImage* mask();
};

}  // namespace Color
#endif
