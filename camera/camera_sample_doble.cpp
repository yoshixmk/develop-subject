#include <cv.h>
#include <highgui.h>
#include <stdio.h>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#define CAM_PIX_WIDTH  320//160
#define CAM_PIX_HEIGHT 240//120

int main(int argc, char** argv)
{
	int key;	
	CvCapture* src1;
	CvCapture* src2;
	IplImage* frame1;
	IplImage* frame2;

	cvNamedWindow("カメラ映像表示1", CV_WINDOW_AUTOSIZE);
	cvNamedWindow("カメラ映像表示2", CV_WINDOW_AUTOSIZE);
	cvNamedWindow("カメラ映像結合", CV_WINDOW_AUTOSIZE);

	src1 = cvCaptureFromCAM(0);
	src2 = cvCaptureFromCAM(1);

// size設定
    cvSetCaptureProperty(src1,CV_CAP_PROP_FRAME_WIDTH,CAM_PIX_WIDTH);
	cvSetCaptureProperty(src1,CV_CAP_PROP_FRAME_HEIGHT,CAM_PIX_HEIGHT);
	cvSetCaptureProperty(src2,CV_CAP_PROP_FRAME_WIDTH,CAM_PIX_WIDTH);
	cvSetCaptureProperty(src2,CV_CAP_PROP_FRAME_HEIGHT,CAM_PIX_HEIGHT);

if(src1 == NULL)
{
printf(" No1 not data \n ");
cvWaitKey(0);
return -1;
}
if(src2 == NULL)
{
printf(" No2 not data \n ");
cvWaitKey(0);
return -1;
}
	cv::Mat mat_frame1;
	cv::Mat mat_frame2;
	cv::Mat dst_img_h;
while(1){

	frame1 = cvQueryFrame(src1);
	frame2 = cvQueryFrame(src2);
	
	mat_frame1 = cv::cvarrToMat(frame1);
	mat_frame2 = cv::cvarrToMat(frame2);
	vconcat(mat_frame1, mat_frame2, dst_img_h);

	cvShowImage("カメラ映像表示1",frame1);
	cvShowImage("カメラ映像表示2",frame2);
	cv::imshow("カメラ映像結合",dst_img_h);

	key = cvWaitKey(33);
	if(key == 27)
	break;
	}
	cvDestroyWindow("カメラ映像表示1");
	cvDestroyWindow("カメラ映像表示2");
	cvDestroyWindow("カメラ映像結合");
	cvReleaseCapture(&src1);
	cvReleaseCapture(&src2);
	return 0;
}
