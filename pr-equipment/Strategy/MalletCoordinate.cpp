#include "MalletCoordinate.h"

namespace Strategy
{

MalletCoordinate::MalletCoordinate()
{
//	mColorExtractionMallet.setPackHSV();
//	IplImage* packMasikingImage = mColorExtractionMallet.extractRobotSideHockeyTable();
//	cvSetImageCOI(packMasikingImage, 1);
//
//	CvMoments moment_pack;
//	cvMoments(packMasikingImage, &moment_pack, 0);
//
//	double m00_now_pack = cvGetSpatialMoment(&moment_pack, 0, 0);
//	double m10_now_pack = cvGetSpatialMoment(&moment_pack, 1, 0);
//	double m01_now_pack = cvGetSpatialMoment(&moment_pack, 0, 1);
//
//	double gX_now_pack = m10_now_pack / m00_now_pack;
//	double gY_now_pack = m01_now_pack / m00_now_pack;
//
//	//初期化時は前回の座標と現在の座標は同じ。
//	mXYCoordinate = cvPoint(gX_now_pack, gY_now_pack);
}

CvPoint MalletCoordinate::getCoordinate()
{
	Color::ColorExtraction colorExtractionMallet;
	colorExtractionMallet.setMalletHSV();
	IplImage* malletMasikingImage = colorExtractionMallet.extractRobotSideHockeyTable();

	cvSetImageCOI(malletMasikingImage, 1);

	CvMoments moment_mallet;
	cvMoments(malletMasikingImage, &moment_mallet, 0);

	double m00_now_mallet = cvGetSpatialMoment(&moment_mallet, 0, 0);
	double m10_now_mallet = cvGetSpatialMoment(&moment_mallet, 1, 0);
	double m01_now_mallet = cvGetSpatialMoment(&moment_mallet, 0, 1);

	double gX_now_mallet = m10_now_mallet / m00_now_mallet;
	double gY_now_mallet = m01_now_mallet / m00_now_mallet;

	CvPoint mXYCoordinate = cvPoint(gX_now_mallet, gY_now_mallet);
	return mXYCoordinate;
}
}  // namespace Strategy
