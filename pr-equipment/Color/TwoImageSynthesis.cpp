#include "TwoImageSynthesis.h"

namespace Color
{

TwoImageSynthesis::TwoImageSynthesis() :CAM_PIX_WIDTH(160),
										CAM_PIX_HEIGHT(120),
										mCamera(CAM_PIX_WIDTH, CAM_PIX_HEIGHT)
{
//	mSynthesisImage = cvCreateImage(cvSize(CAM_PIX_WIDTH, CAM_PIX_HEIGHT * 2), IPL_DEPTH_8U, 3);
	//mCameraRobotSide->setSize(320,280);
	//mCameraHumanSide->setSize(320,280);
}

IplImage*  TwoImageSynthesis::synthesize()
{
	IplImage* imgRobotSide = mCamera.getRobotSideImage();
	IplImage* imgHumanSide = mCamera.getHumanSideImage();
	IplImage* mSynthesisImage = cvCreateImage(cvSize(CAM_PIX_WIDTH, CAM_PIX_HEIGHT * 2), IPL_DEPTH_8U, 3);

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
