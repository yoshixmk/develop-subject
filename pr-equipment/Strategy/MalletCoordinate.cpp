#include "MalletCoordinate.h"

namespace Strategy
{

CvPoint MalletCoordinate::getCoordinate()
{
	Color::ColorExtraction colorExtractionMallet;

	colorExtractionMallet.setMalletHSV();

	return cvPoint(0, 0);
}
}  // namespace Strategy
