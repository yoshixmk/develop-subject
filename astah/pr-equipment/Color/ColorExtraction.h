#ifndef COLOR_COLOR_EXTRACTION_H
#define COLOR_COLOR_EXTRACTION_H

#include "Color/Masking.h"

namespace Color
{
class ColorExtraction
{
private:
	int h_max;

	int h_min;

	int s_max;

	int s_min;

	int v_max;

	int v_min;

	Masking masking[2];

public:
	void setHSV(int h_max, int h_min, int s_max, int s_min, int v_max, int v_min);

	int extractHockeyTable();

	int extractRobotSideHockeyTable();

};

}  // namespace Color
#endif
