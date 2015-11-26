#include "PackCoordinate.h"

namespace Strategy
{

PackCoordinate::PackCoordinate()
{
//	Color::ColorExtraction colorExtractionPack;
	mColorExtraction.setPackHSV();
	mPackMasikingImage = mColorExtraction.extractHockeyTable();
	cvSetImageCOI(mPackMasikingImage, 1);

	CvMoments moment_pack;
	cvMoments(mPackMasikingImage, &moment_pack, 0);

	double m00_now_pack = cvGetSpatialMoment(&moment_pack, 0, 0);
	double m10_now_pack = cvGetSpatialMoment(&moment_pack, 1, 0);
	double m01_now_pack = cvGetSpatialMoment(&moment_pack, 0, 1);

	double gX_now_pack = m10_now_pack / m00_now_pack;
	double gY_now_pack = m01_now_pack / m00_now_pack;

	//初期化時は前回の座標と現在の座標は同じ。
	mXYCoordinate = cvPoint(gX_now_pack, gY_now_pack);
	mPreviousXYCoordinate = cvPoint(gX_now_pack, gY_now_pack);
}

CvPoint PackCoordinate::getCoordinate()
{
	//現在の座標を、前回の座標に変える
	mPreviousXYCoordinate = mXYCoordinate;

//	Color::ColorExtraction colorExtractionPack;
	mColorExtraction.setPackHSV();
	mPackMasikingImage = mColorExtraction.extractHockeyTable();

	cvSetImageCOI(mPackMasikingImage, 1);

	CvMoments moment_pack;
	cvMoments(mPackMasikingImage, &moment_pack, 0);

	double m00_now_pack = cvGetSpatialMoment(&moment_pack, 0, 0);
	double m10_now_pack = cvGetSpatialMoment(&moment_pack, 1, 0);
	double m01_now_pack = cvGetSpatialMoment(&moment_pack, 0, 1);

	double gX_now_pack = m10_now_pack / m00_now_pack;
	double gY_now_pack = m01_now_pack / m00_now_pack;

	CvPoint mXYCoordinate = cvPoint(gX_now_pack, gY_now_pack);
	return mXYCoordinate;
}

CvPoint PackCoordinate::getPreviousCoordinate()
{
	return mPreviousXYCoordinate;
}
}  // namespace Strategy
