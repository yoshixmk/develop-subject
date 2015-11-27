#include "TwoImageSynthesis.h"

namespace Color
{

TwoImageSynthesis::TwoImageSynthesis() :mCamera(), mPerspectiveTransformation()
{
	mSynthesisImage = cvCreateImage(cvSize(Hardware::Camera::getWidth(), Hardware::Camera::getHeight()* 2), IPL_DEPTH_8U, 3);
}

TwoImageSynthesis::~TwoImageSynthesis()
{
	cvReleaseImage(&mSynthesisImage);
}

IplImage*  TwoImageSynthesis::synthesize()
{
	mImgRobotSide = mCamera.getRobotSideImage();
	mImgHumanSide = mCamera.getHumanSideImage();
	cv::Mat matFrameRobotSide;
	cv::Mat matFrameHumanSide;
	matFrameRobotSide = cv::cvarrToMat(mImgRobotSide);
	matFrameHumanSide = cv::cvarrToMat(mImgHumanSide);
	cv::flip(matFrameRobotSide, matFrameRobotSide, 0); //水平軸で反転（垂直反転）
	cv::flip(matFrameRobotSide, matFrameRobotSide, 1); //垂直軸で反転（水平反転）
	vconcat(matFrameHumanSide, matFrameRobotSide, mMatSynthesisImage);
	*mSynthesisImage = mMatSynthesisImage;

	return mSynthesisImage;
}

IplImage* TwoImageSynthesis::synthesizeNonDistortion()
{
	mImgRobotSide = mPerspectiveTransformation.transformRobotSideImage();
	mImgHumanSide = mPerspectiveTransformation.transformHumanSideImage();
	cv::Mat matFrameRobotSide;
	cv::Mat matFrameHumanSide;
	matFrameRobotSide = cv::cvarrToMat(mImgRobotSide);
	matFrameHumanSide = cv::cvarrToMat(mImgHumanSide);
	cv::flip(matFrameRobotSide, matFrameRobotSide, 0); //水平軸で反転（垂直反転）
	cv::flip(matFrameRobotSide, matFrameRobotSide, 1); //垂直軸で反転（水平反転）
	vconcat(matFrameHumanSide, matFrameRobotSide, mMatNonDistortionImage);

	*mSynthesisImage = mMatNonDistortionImage;

	return mSynthesisImage;
}

}  // namespace Color

