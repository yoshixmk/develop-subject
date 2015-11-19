#include "TwoImageSynthesis.h"

namespace Color
{

TwoImageSynthesis::TwoImageSynthesis() :mCamera()
{
	mSynthesisImage = cvCreateImage(cvSize(160, 120*2), IPL_DEPTH_8U, 3);
	imgRobotSide = cvCreateImage(cvSize(160, 120), IPL_DEPTH_8U, 3);
	imgHumanSide = cvCreateImage(cvSize(160, 120), IPL_DEPTH_8U, 3);
	std::cout << "two image constracter calling" << std::endl;
}

TwoImageSynthesis::~TwoImageSynthesis()
{
	cvReleaseImage(&mSynthesisImage);
	cvReleaseImage(&imgRobotSide);
	cvReleaseImage(&imgHumanSide);
	std::cout << "two image Deconstracter calling" << std::endl;
}
IplImage*  TwoImageSynthesis::synthesize()
{
	imgRobotSide = mCamera.getRobotSideImage();
	imgHumanSide = mCamera.getHumanSideImage();


	matFrameRobotSide = cv::cvarrToMat(imgRobotSide);
	matFrameHumanSide = cv::cvarrToMat(imgHumanSide);
	cv::flip(matFrameRobotSide, matFrameRobotSide, 0); //水平軸で反転（垂直反転）
	cv::flip(matFrameRobotSide, matFrameRobotSide, 1); //垂直軸で反転（水平反転）
	vconcat(matFrameHumanSide, matFrameRobotSide, dstImgV);
	*mSynthesisImage = dstImgV;

	return mSynthesisImage;
}
}  // namespace Color

