#ifndef STRATEGY_FRAME_COORDINATE_H
#define STRATEGY_FRAME_COORDINATE_H

#include "Strategy/Coordinate.h"

namespace Strategy {
class FrameCoordinate: public Coordinate {
private:
	int upper_left_f;

	int lower_left_f;

	int upper_right_f;

	int lower_right_f;

	int upper_left_g;

	int lower_left_g;

	int upper_right_g;

	int lower_right_g;

public:
	void getUpperLeftF();

	void getLowerLeftF();

	void getUpperRightF();

	void getLowerRightF();

	void getUpperLeftG();

	void getLowerLeftG();

	void getUpperRightG();

	void getLowerRightG();

};

}  // namespace Strategy
#endif
