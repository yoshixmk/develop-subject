#ifndef COLOR_MASKING_H
#define COLOR_MASKING_H

#include "Color/TwoImageSynthesis.h"

namespace Color
{
class Masking
{
private:
	IplImage* output_image;

	TwoImageSynthesis twoImageSynthesis;

public:
	virtual IplImage* mask()=0;

};

}  // namespace Color
#endif
