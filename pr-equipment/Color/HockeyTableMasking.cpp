#include "HockeyTableMasking.h"
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv/cv.h>
#include <opencv/highgui.h>

namespace Color
{

HockeyTableMasking::HockeyTableMasking() :twoImageSynthesis()
{
	mHockeyTableImage = cvCreateImage(cvSize(160, 120*2), IPL_DEPTH_8U, 3);
//	src_img = cvCreateImage(cvSize(160, 120), IPL_DEPTH_8U, 3);
//	dst_img = cvCreateImage(cvSize(160, 120), IPL_DEPTH_8U, 3);
}

IplImage* HockeyTableMasking::mask()
{
	IplImage* src_img, *dst_img;
	src_img = twoImageSynthesis.synthesize();
	int height = src_img->height / 2;

	int npts[2] = { 4, 12 };
	CvPoint **pts;
	CvPoint center_frame_left = cvPoint(11, height);
	CvPoint center_frame_right  = cvPoint(155, height);
	pts = (CvPoint **) cvAlloc (sizeof (CvPoint *) * 2);
	pts[0] = (CvPoint *) cvAlloc (sizeof (CvPoint) * 4);
	pts[1] = (CvPoint *) cvAlloc (sizeof (CvPoint) * 12);
	pts[0][0] = cvPoint(0,0);
	pts[0][1] = cvPoint(160,0);
	pts[0][2] = cvPoint(320,240);
	pts[0][3] = cvPoint(0,240);
	pts[1][0] = cvPoint(39,17);
	pts[1][1] = cvPoint(126,15);
	pts[1][2] = cvPoint(147,26);
	pts[1][3] = cvPoint(160,77);
	pts[1][4] = cvPoint(160,164);
	pts[1][5] = cvPoint(145,224);
	pts[1][6] = cvPoint(125,233);
	pts[1][7] = cvPoint(39,233);
	pts[1][8] = cvPoint(15,217);
	pts[1][9] = cvPoint(0,133);
	pts[1][10] = cvPoint(0,115);
	pts[1][11] = cvPoint(17,28);

    cvLine(src_img, center_frame_left, center_frame_right, CV_RGB( 0, 255, 255 ));
//    dst_img = cvCreateImage(cvGetSize(src_img), IPL_DEPTH_8U, 3);
//    cvCopy(src_img, dst_img);

    cvFillPoly(src_img, pts, npts, 2, CV_RGB(0, 0, 0));
//    mHockeyTableImage = dst_img;

//	return mHockeyTableImage;
	return src_img;
}
}  // namespace Color
