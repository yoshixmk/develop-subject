#include "TwoImageSynthesis.h"

namespace Color
{

TwoImageSynthesis::TwoImageSynthesis() :mCamera(), perspectiveTransformation() {}

IplImage*  TwoImageSynthesis::synthesize()
{
	IplImage* imgRobotSide = mCamera.getRobotSideImage();
	IplImage* imgHumanSide = mCamera.getHumanSideImage();
	cv::Mat matFrameRobotSide;
	cv::Mat matFrameHumanSide;
	matFrameRobotSide = cv::cvarrToMat(imgRobotSide);
	matFrameHumanSide = cv::cvarrToMat(imgHumanSide);
	cv::flip(matFrameRobotSide, matFrameRobotSide, 0); //水平軸で反転（垂直反転）
	cv::flip(matFrameRobotSide, matFrameRobotSide, 1); //垂直軸で反転（水平反転）
	vconcat(matFrameHumanSide, matFrameRobotSide, mMatSynthesisImage);
	IplImage* mSynthesisImage = cvCreateImage(cvSize(Hardware::Camera::getWidth(), Hardware::Camera::getHeight()* 2), IPL_DEPTH_8U, 3);
	*mSynthesisImage = mMatSynthesisImage;

	return mSynthesisImage;
}

IplImage* TwoImageSynthesis::synthesizeNonDistortion()
{
	IplImage* imgRobotSide = cvCreateImage(cvSize(Hardware::Camera::getWidth(), Hardware::Camera::getHeight() * 2), IPL_DEPTH_8U, 3);
	imgRobotSide = perspectiveTransformation.transformRobotSideImage();
	IplImage* imgHumanSide = cvCreateImage(cvSize(Hardware::Camera::getWidth(), Hardware::Camera::getHeight() * 2), IPL_DEPTH_8U, 3);
	imgHumanSide = perspectiveTransformation.transformHumanSideImage();
	cv::Mat matFrameRobotSide;
	cv::Mat matFrameHumanSide;
	matFrameRobotSide = cv::cvarrToMat(imgRobotSide);
	matFrameHumanSide = cv::cvarrToMat(imgHumanSide);
	cv::flip(matFrameRobotSide, matFrameRobotSide, 0); //水平軸で反転（垂直反転）
	cv::flip(matFrameRobotSide, matFrameRobotSide, 1); //垂直軸で反転（水平反転）
	vconcat(matFrameHumanSide, matFrameRobotSide, mMatNonDistortionImage);
	IplImage* mSynthesisImage = cvCreateImage(cvSize(Hardware::Camera::getWidth(), Hardware::Camera::getHeight()* 2), IPL_DEPTH_8U, 3);
	*mSynthesisImage = mMatNonDistortionImage;

	return mSynthesisImage;
}

}  // namespace Color

