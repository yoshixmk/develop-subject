#ifndef COLOR_MASKING_H
#define COLOR_MASKING_H

#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>

#include "TwoImageSynthesis.h"

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
