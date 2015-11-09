#ifndef COLOR_MASKING_H
#define COLOR_MASKING_H

#include "Color/TwoImageSynthesis.h"

namespace Color
{
class Masking
{
private:
	int output_image;

	TwoImageSynthesis twoImageSynthesis;

public:
	virtual int mask()=0;

};

}  // namespace Color
#endif
