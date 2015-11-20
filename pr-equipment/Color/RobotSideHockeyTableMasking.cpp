#include "RobotSideHockeyTableMasking.h"

namespace Color
{

RobotSideHockeyTableMasking::RobotSideHockeyTableMasking() :mTwoImageSynthesis()
{
	mRobotSideHockeyTableImage = cvCreateImage(cvSize(Hardware::Camera::getWidth(), Hardware::Camera::getHeight() * 2), IPL_DEPTH_8U, 3);
}

RobotSideHockeyTableMasking::~RobotSideHockeyTableMasking()
{
	cvReleaseImage(&mRobotSideHockeyTableImage);
}

IplImage* RobotSideHockeyTableMasking::mask()
{
	IplImage* src_img;
	src_img = mTwoImageSynthesis.synthesize();
	int width = Hardware::Camera::getWidth();
	int height = Hardware::Camera::getHeight();

	int npts[2] = { 4, 8 };
	CvPoint **pts;
//	CvPoint center_frame_left = cvPoint(11, height);
//	CvPoint center_frame_right = cvPoint(155, height);

	pts = (CvPoint **) cvAlloc (sizeof (CvPoint *) * 2);
	pts[0] = (CvPoint *) cvAlloc (sizeof (CvPoint) * 4);
	pts[1] = (CvPoint *) cvAlloc (sizeof (CvPoint) * 8);
	pts[0][0] = cvPoint(0,0);
	pts[0][1] = cvPoint(width,0);
	pts[0][2] = cvPoint(width, height*2);
	pts[0][3] = cvPoint(0, height*2);
	pts[1][1] = cvPoint(0, height);
	pts[1][2] = cvPoint(width, height);
	pts[1][3] = cvPoint(width, 164);
	pts[1][4] = cvPoint(145, 224);
	pts[1][5] = cvPoint(125, 233);
	pts[1][6] = cvPoint(39, 233);
	pts[1][7] = cvPoint(15, 217);
	pts[1][0] = cvPoint(0, 133);

//    cvLine(src_img, center_frame_left, center_frame_right, CV_RGB( 0, 255, 255 ));
    mRobotSideHockeyTableImage = src_img;
    cvFillPoly(mRobotSideHockeyTableImage, pts, npts, 2, CV_RGB(0, 0, 0));

	return mRobotSideHockeyTableImage;
}
}  // namespace Color
