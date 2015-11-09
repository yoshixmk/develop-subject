#ifndef COLOR_TWO_IMAGE_SYNTHESIS_H
#define COLOR_TWO_IMAGE_SYNTHESIS_H

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
