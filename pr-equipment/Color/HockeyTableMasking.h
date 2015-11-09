#ifndef COLOR_HOCKEY_TABLE_MASKING_H
#define COLOR_HOCKEY_TABLE_MASKING_H

#include "Color/Masking.h"

namespace Color
{
class HockeyTableMasking : public Masking
{
private:
	int hockey_table_image;


public:
	int mask();

};

}  // namespace Color
#endif
