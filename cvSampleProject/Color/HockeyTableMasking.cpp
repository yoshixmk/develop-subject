#include "HockeyTableMasking.h"

namespace Color
{

HockeyTableMasking::HockeyTableMasking() :mTwoImageSynthesis()
{
	mHockeyTableImage = cvCreateImage(cvSize(Hardware::Camera::getWidth(), Hardware::Camera::getHeight() * 2), IPL_DEPTH_8U, 3);
}

//HockeyTableMasking::~HockeyTableMasking()
//{
//	cvReleaseImage(&mHockeyTableImage);
//}

IplImage* HockeyTableMasking::mask()
{
	IplImage* src_img = cvCreateImage(cvSize(Hardware::Camera::getWidth(), Hardware::Camera::getHeight() * 2), IPL_DEPTH_8U, 3);
	src_img = mTwoImageSynthesis.synthesizeNonDistortion();
	int width = Hardware::Camera::getWidth();
	int height = Hardware::Camera::getHeight();

	int npts[2] = { 4, 8 };
	CvPoint **pts;
//	CvPoint center_frame_left = cvPoint(11, height);
//	CvPoint center_frame_right  = cvPoint(155, height);

	pts = (CvPoint **) cvAlloc (sizeof (CvPoint *) * 2);
	pts[0] = (CvPoint *) cvAlloc (sizeof (CvPoint) * 4);
	pts[1] = (CvPoint *) cvAlloc (sizeof (CvPoint) * 8);
	pts[0][0] = cvPoint(0,0);
	pts[0][1] = cvPoint(width,0);
	pts[0][2] = cvPoint(width, height*2);
	pts[0][3] = cvPoint(0, height*2);
	pts[1][0] = cvPoint(13,25);
	pts[1][1] = cvPoint(13,224);
	pts[1][2] = cvPoint(30,236);
	pts[1][3] = cvPoint(128,236);
	pts[1][4] = cvPoint(146,224);
	pts[1][5] = cvPoint(146,25);
	pts[1][6] = cvPoint(128,13);
	pts[1][7] = cvPoint(30,13);

//    cvLine(src_img, center_frame_left, center_frame_right, CV_RGB( 0, 255, 255 ));
//    mHockeyTableImage = src_img;
	cvCopy(src_img, mHockeyTableImage);
    cvFillPoly(mHockeyTableImage, pts, npts, 2, CV_RGB(0, 0, 0));

	return mHockeyTableImage;
}
}  // namespace Color
