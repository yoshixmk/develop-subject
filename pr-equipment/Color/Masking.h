#ifndef COLOR_MASKING_H
#define COLOR_MASKING_H

#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>

#include "Color/2ImageSynthesis.h"

namespace Color
{
class Masking
{
private:
	int output_image;

	2ImageSynthesis 2ImageSynthesis;

public:
	virtual int mask()=0;

};

}  // namespace Color
#endif
