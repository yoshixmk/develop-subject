#ifndef COLOR_2_IMAGE_SYNTHESIS_H
#define COLOR_2_IMAGE_SYNTHESIS_H

#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>

#include "Hardware/Camera.h"

namespace Color
{
class TwoImageSynthesis
{
private:
	int synthesis_image;

	Hardware::Camera camera[2];

public:
	int synthesize();

};

}  // namespace Color
#endif
