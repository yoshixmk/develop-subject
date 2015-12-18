#ifndef COLOR_MASKING_H
#define COLOR_MASKING_H

#include "TwoImageSynthesis.h"

namespace Color {
class Masking {
private:
	IplImage* mOutputImage;

	TwoImageSynthesis mTwoImageSynthesis;

public:
	virtual IplImage* mask()=0;
};

}  // namespace Color
#endif
