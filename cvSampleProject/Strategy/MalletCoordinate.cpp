#include "MalletCoordinate.h"

namespace Strategy
{

MalletCoordinate::MalletCoordinate()
{
	mColorExtraction.setPackHSV();
	IplImage* packMasikingImage = mColorExtraction.extractRobotSideHockeyTable();
	cvSetImageCOI(packMasikingImage, 1);

	CvMoments moment_mallet;
	cvMoments(packMasikingImage, &moment_mallet, 0);

	double m00_now_mallet = cvGetSpatialMoment(&moment_mallet, 0, 0);
	double m10_now_mallet = cvGetSpatialMoment(&moment_mallet, 1, 0);
	double m01_now_mallet = cvGetSpatialMoment(&moment_mallet, 0, 1);

	double gX_now_mallet = m10_now_mallet / m00_now_mallet;
	double gY_now_mallet = m01_now_mallet / m00_now_mallet;

	//初期化時は前回の座標と現在の座標は同じ。
	mXYCoordinate = cvPoint(gX_now_mallet, gY_now_mallet);
}

CvPoint MalletCoordinate::getCoordinate()
{
	mColorExtraction.setMalletHSV();
	IplImage* malletMasikingImage = mColorExtraction.extractRobotSideHockeyTable();

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
