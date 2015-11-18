#include "TwoImageSynthesis.h"

namespace Color
{

TwoImageSynthesis::TwoImageSynthesis() :mCamera()
{
	mSynthesisImage=0;
}

IplImage*  TwoImageSynthesis::synthesize()
{
	IplImage* imgRobotSide = mCamera.getRobotSideImage();
	IplImage* imgHumanSide = mCamera.getHumanSideImage();
	mSynthesisImage = cvCreateImage(cvSize(imgRobotSide->width, imgRobotSide->height * 2), IPL_DEPTH_8U, 3);
	cv::Mat matFrameRobotSide;
	cv::Mat matFrameHumanSide;
	cv::Mat dstImgV;
	matFrameRobotSide = cv::cvarrToMat(imgRobotSide);
	matFrameHumanSide = cv::cvarrToMat(imgHumanSide);
	cv::flip(matFrameRobotSide, matFrameRobotSide, 0); //水平軸で反転（垂直反転）
	cv::flip(matFrameRobotSide, matFrameRobotSide, 1); //垂直軸で反転（水平反転）
	vconcat(matFrameHumanSide, matFrameRobotSide, dstImgV);
	*mSynthesisImage = dstImgV;

	return mSynthesisImage;
}
}  // namespace Color
