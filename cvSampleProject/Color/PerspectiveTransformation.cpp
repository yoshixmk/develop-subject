#include "PerspectiveTransformation.h"
#include "../Hardware/Camera.h"

namespace Color
{

PerspectiveTransformation::PerspectiveTransformation() :mCamera()
{
	mRobotSideImage = cvCreateImage(cvSize(Hardware::Camera::getWidth(), Hardware::Camera::getHeight()), IPL_DEPTH_8U, 3);
	mHumanSideImage = cvCreateImage(cvSize(Hardware::Camera::getWidth(), Hardware::Camera::getHeight()), IPL_DEPTH_8U, 3);
}

IplImage* PerspectiveTransformation::transformRobotSideImage()
{
	IplImage *src_img = cvCreateImage(cvSize(Hardware::Camera::getWidth(), Hardware::Camera::getHeight()), IPL_DEPTH_8U, 3);
    CvMat *map_matrix;
    CvPoint2D32f src_pnt[4], dst_pnt[4];

    src_img = mCamera.getRobotSideImage();

	src_pnt[0] = cvPoint2D32f (25, 12);
	src_pnt[1] = cvPoint2D32f (4, 120);
	src_pnt[2] = cvPoint2D32f (154, 120);
	src_pnt[3] = cvPoint2D32f (136, 14);

	dst_pnt[0] = cvPoint2D32f (19, 12);
	dst_pnt[1] = cvPoint2D32f (19, 120);
	dst_pnt[2] = cvPoint2D32f (141, 120);
	dst_pnt[3] = cvPoint2D32f (141, 12);

	map_matrix = cvCreateMat (3, 3, CV_32FC1);
	cvGetPerspectiveTransform (src_pnt, dst_pnt, map_matrix);

	cvWarpPerspective (src_img, mRobotSideImage, map_matrix, CV_INTER_LINEAR + CV_WARP_FILL_OUTLIERS, cvScalarAll (100));

	return mRobotSideImage;
}

IplImage* PerspectiveTransformation::transformHumanSideImage()
{
	IplImage *src_img = cvCreateImage(cvSize(Hardware::Camera::getWidth(), Hardware::Camera::getHeight()), IPL_DEPTH_8U, 3);
    CvMat *map_matrix;
    CvPoint2D32f src_pnt[4], dst_pnt[4];

    src_img = mCamera.getHumanSideImage();

	src_pnt[0] = cvPoint2D32f (23, 22);
	src_pnt[1] = cvPoint2D32f (7, 120);
	src_pnt[2] = cvPoint2D32f (154, 120);
	src_pnt[3] = cvPoint2D32f (135, 21);

	dst_pnt[0] = cvPoint2D32f (19, 21);
	dst_pnt[1] = cvPoint2D32f (19, 120);
	dst_pnt[2] = cvPoint2D32f (141, 120);
	dst_pnt[3] = cvPoint2D32f (141, 21);

	map_matrix = cvCreateMat (3, 3, CV_32FC1);
	cvGetPerspectiveTransform (src_pnt, dst_pnt, map_matrix);
	cvWarpPerspective (src_img, mHumanSideImage, map_matrix, CV_INTER_LINEAR + CV_WARP_FILL_OUTLIERS, cvScalarAll (100));

	return mHumanSideImage;
}

} /* namespace Color */
