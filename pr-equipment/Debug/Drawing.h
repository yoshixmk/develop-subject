#ifndef DEBUG_DRAWING_H
#define DEBUG_DRAWING_H

#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>

namespace Debug
{
class Drawing
{
public:
	void drawPack(int image);

	void drawMallet(int image);

	void drawDefenseLine(int image);

	void drawPackLocus(int image);

};

}  // namespace Debug
#endif
