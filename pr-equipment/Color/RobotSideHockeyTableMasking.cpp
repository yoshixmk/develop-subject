#include "RobotSideHockeyTableMasking.h"

namespace Color
{

RobotSideHockeyTableMasking::RobotSideHockeyTableMasking() :mTwoImageSynthesis()
{
	mRobotSideHockeyTableImage = cvCreateImage(cvSize(Hardware::Camera::getWidth(), Hardware::Camera::getHeight() * 2), IPL_DEPTH_8U, 3);
}

//RobotSideHockeyTableMasking::~RobotSideHockeyTableMasking()
//{
//	cvReleaseImage(&mRobotSideHockeyTableImage);
//}

IplImage* RobotSideHockeyTableMasking::mask()
{
	int width = Hardware::Camera::getWidth();
	int height = Hardware::Camera::getHeight();

	int npts[2] = { 4, 6 };
	CvPoint **pts;

	pts = (CvPoint **) cvAlloc (sizeof (CvPoint *) * 2);
	pts[0] = (CvPoint *) cvAlloc (sizeof (CvPoint) * 4);
	pts[1] = (CvPoint *) cvAlloc (sizeof (CvPoint) * 6);
	pts[0][0] = cvPoint(0,0);
	pts[0][1] = cvPoint(width,0);
	pts[0][2] = cvPoint(width, height*2);
	pts[0][3] = cvPoint(0, height*2);
	pts[1][0] = cvPoint(13, height);
	pts[1][1] = cvPoint(13, 224);
	pts[1][2] = cvPoint(30, 236);
	pts[1][3] = cvPoint(128, 236);
	pts[1][4] = cvPoint(146, 224);
	pts[1][5] = cvPoint(146, height);

    cvFillPoly(mRobotSideHockeyTableImage, pts, npts, 2, CV_RGB(0, 0, 0));
    cvFree(&pts[0]);
    cvFree(&pts[1]);
    cvFree(pts);
	return mRobotSideHockeyTableImage;
}
}  // namespace Color
