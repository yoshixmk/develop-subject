#include "ColorExtraction.h"
#include <opencv2/highgui/highgui.hpp>
#include <opencv/cv.h>
#include <opencv/highgui.h>

namespace Color
{

ColorExtraction::ColorExtraction():mHockeyTableMasking(), mRobotSideHockeyTableMasking()
{
	mColorExtractionImage = cvCreateImage(cvSize(Hardware::Camera::getWidth(), Hardware::Camera::getHeight() * 2), IPL_DEPTH_8U, 3);
	mHMin = 0;
	mHMax = 255;
	mSMin = 0;
	mSMax = 255;
	mVMin = 0;
	mVMax = 255;
}

ColorExtraction::ColorExtraction(int aHMin, int aHMax, int aSMin, int aSMax, int aVMin, int aVMax) :mHockeyTableMasking(), mRobotSideHockeyTableMasking()
{
	mColorExtractionImage = cvCreateImage(cvSize(Hardware::Camera::getWidth(), Hardware::Camera::getHeight() * 2), IPL_DEPTH_8U, 3);
	mHMax = aHMax;
	mHMin = aHMin;
	mSMax = aSMax;
	mSMin = aSMin;
	mVMax = aVMax;
	mVMin = aVMin;
};

void ColorExtraction::cvColorExtraction(IplImage* aSrcImg, IplImage* aDstImg,
										int aCode,
										int aCh1Lower, int aCh1Upper,
										int aCh2Lower, int aCh2Upper,
										int aCh3Lower, int aCh3Upper)
{
	//---------------------------------------------------------------
	//【関数名　】：cvColorExtraction
	//【処理概要】：色抽出
	//【引数　　】：aSrcImg        = 入力画像(8bit3ch)
	//　　　　　　：aDstImg        = 出力画像(8bit3ch)
	//　　　　　　：aCode        = 色空間の指定（CV_BGR2HSV,CV_BGR2Labなど）
	//　　　　　　：aCh1Lower    = ch1のしきい値(小)
	//　　　　　　：aCh1Upper    = ch1のしきい値(大)
	//　　　　　　：aCh2Lower    = ch2のしきい値(小)
	//　　　　　　：aCh2Upper    = ch2のしきい値(大)
	//　　　　　　：aCh3Lower    = ch3のしきい値(小)
	//　　　　　　：aCh3Upper    = ch3のしきい値(大)
	//【戻り値　】：なし
	//【備考　　】：lower <= upperの場合、lower以上upper以下の範囲を抽出、
	//　　　　　　：lower >  upperの場合、upper以下lower以上の範囲を抽出します。
	//---------------------------------------------------------------
	int i, k;

	IplImage *Color_img;
	IplImage *ch1_img, *ch2_img, *ch3_img;
	IplImage *Mask_img;

	int lower[3];
	int upper[3];
	int val[3];

	CvMat *lut;

	//aCodeに基づいたカラー変換
	Color_img = cvCreateImage(cvGetSize(aSrcImg), aSrcImg->depth, aSrcImg->nChannels);
	cvCvtColor(aSrcImg, Color_img, aCode);

	//3ChのLUT作成
	lut    = cvCreateMat(256, 1, CV_8UC3);

	lower[0] = aCh1Lower;
	lower[1] = aCh2Lower;
	lower[2] = aCh3Lower;

	upper[0] = aCh1Upper;
	upper[1] = aCh2Upper;
	upper[2] = aCh3Upper;

	for (i = 0; i < 256; i++) {
		for (k = 0; k < 3; k++) {
			if (lower[k] <= upper[k]) {
				if ((lower[k] <= i) && (i <= upper[k])) {
					val[k] = 255;
				} else {
					val[k] = 0;
				}
			} else {
				if ((i <= upper[k]) || (lower[k] <= i)) {
					val[k] = 255;
				} else {
					val[k] = 0;
				}
			}
		}
		//LUTの設定
		cvSet1D(lut, i, cvScalar(val[0], val[1], val[2]));
	}

	//3ChごとのLUT変換（各チャンネルごとに２値化処理）
	cvLUT(Color_img, Color_img, lut);
	cvReleaseMat(&lut);

	//各チャンネルごとのIplImageを確保する
	ch1_img = cvCreateImage(cvGetSize(Color_img), Color_img->depth, 1);
	ch2_img = cvCreateImage(cvGetSize(Color_img), Color_img->depth, 1);
	ch3_img = cvCreateImage(cvGetSize(Color_img), Color_img->depth, 1);

	//チャンネルごとに二値化された画像をそれぞれのチャンネルに分解する
	cvSplit(Color_img, ch1_img, ch2_img, ch3_img, NULL);

	//3Ch全てのANDを取り、マスク画像を作成する。
	Mask_img = cvCreateImage(cvGetSize(Color_img), Color_img->depth, 1);
	cvAnd(ch1_img, ch2_img, Mask_img);
	cvAnd(Mask_img, ch3_img, Mask_img);

	//入力画像(aSrcImg)のマスク領域を出力画像(aDstImg)へコピーする
	cvZero(aDstImg);
	cvCopy(aSrcImg, aDstImg, Mask_img);

	//解放
	cvReleaseImage(&Color_img);
	cvReleaseImage(&ch1_img);
	cvReleaseImage(&ch2_img);
	cvReleaseImage(&ch3_img);
	cvReleaseImage(&Mask_img);

}

void ColorExtraction::setHSV(int aHMin, int aHMax, int aSMin, int aSMax, int aVMin, int aVMax)
{
	mHMin = aHMin;
	mHMax = aHMax;
	mSMin = aSMin;
	mSMax = aSMax;
	mVMin = aVMin;
	mVMax = aVMax;
}

IplImage* ColorExtraction::extractHockeyTable()
{
	mColorExtractionImage = cvCreateImage(cvSize(Hardware::Camera::getWidth(), Hardware::Camera::getHeight() * 2), IPL_DEPTH_8U, 3);
	IplImage* src_img = cvCreateImage(cvSize(Hardware::Camera::getWidth(), Hardware::Camera::getHeight() * 2), IPL_DEPTH_8U, 3);
	src_img = mHockeyTableMasking.mask();
	cvColorExtraction(src_img, mColorExtractionImage, CV_BGR2HSV, mHMin, mHMax, mSMin, mSMax, mVMin, mVMax);
	return mColorExtractionImage;
}

IplImage* ColorExtraction::extractRobotSideHockeyTable()
{
	mColorExtractionImage = cvCreateImage(cvSize(Hardware::Camera::getWidth(), Hardware::Camera::getHeight() * 2), IPL_DEPTH_8U, 3);
	IplImage* src_img = cvCreateImage(cvSize(Hardware::Camera::getWidth(), Hardware::Camera::getHeight() * 2), IPL_DEPTH_8U, 3);
	src_img = mRobotSideHockeyTableMasking.mask();
	cvColorExtraction(src_img, mColorExtractionImage, CV_BGR2HSV, mHMin, mHMax, mSMin, mSMax, mVMin, mVMax);
	return mColorExtractionImage;
}

void ColorExtraction::setMalletHSV()
{
	mHMin = 106;
	mHMax = 135;
	mSMin = 218;
	mSMax = 255;
	mVMin = 0;
	mVMax = 105;
}

void ColorExtraction::setPackHSV()
{
	mHMin = 54;
	mHMax = 84;
	mSMin = 100;
	mSMax = 255;
	mVMin = 0;
	mVMax = 255;
}

}  // namespace Color
