#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <stdio.h>
//#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#define CAM_PIX_WIDTH  320//160
#define CAM_PIX_HEIGHT 240//120

int main(int argc, char** argv)
{
	int key;	
	CvCapture* src1;
	CvCapture* src2;
	cv::Mat description;
	IplImage* frame1;
	IplImage* frame2; 

	//cvNamedWindow("camera all", CV_WINDOW_AUTOSIZE);
	//cvNamedWindow("description", CV_WINDOW_AUTOSIZE);
	description = cv::imread("/home/pi/develop-subject/camera/photodir/description.png");
	if (!description.data){
		printf(" Description image cannot load \n ");
	        return -1;
	}
	src1 = cvCaptureFromCAM(0);
	src2 = cvCaptureFromCAM(1);

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
	cv::Mat dst_img_v;
	cv::Point upper_left_f, upper_left_g, upper_right_f, upper_right_g,
		      lower_left_f, lower_left_g, lower_right_f, lower_right_g,
			  center_left, center_right, court_center;
	upper_left_f = cvPoint(47, 55);
	upper_right_f =  cvPoint(269, 57);
	lower_left_f = cvPoint(44, 434);
	lower_right_f =  cvPoint(264, 438);

	upper_left_g = cvPoint(73, 41);
	upper_right_g = cvPoint(244, 43);
	lower_left_g =  cvPoint(69, 449);
	lower_right_g =  cvPoint(239, 453);
	center_left = cvPoint(10, 240);
	center_right = cvPoint(306, 240);
	court_center = cvPoint((center_left.x+center_right.x)/2, 240);

	cv::imshow("description", description);
	while(1){
		int target_destanceY = CAM_PIX_HEIGHT * 2 - 2 * 30;
		frame1 = cvQueryFrame(src1);
		frame2 = cvQueryFrame(src2);
		
		mat_frame1 = cv::cvarrToMat(frame1);
		mat_frame2 = cv::cvarrToMat(frame2);

		cv::flip(mat_frame1, mat_frame1, 0);
		cv::flip(mat_frame1, mat_frame1, 1);
		vconcat(mat_frame2, mat_frame1, dst_img_v);
		cv::line(dst_img_v, upper_left_f, upper_right_f, CV_RGB( 255, 255, 0 ), 3);
		cv::line(dst_img_v, lower_left_f, lower_right_f, CV_RGB( 255, 255, 0 ), 3);
		cv::line(dst_img_v, upper_right_f, lower_right_f, CV_RGB( 255, 255, 0 ), 3);
		cv::line(dst_img_v, upper_left_f, lower_left_f, CV_RGB( 255, 255, 0 ), 3);

		cv::line(dst_img_v, upper_left_g, upper_right_g, CV_RGB( 0, 255, 0 ), 3);
		cv::line(dst_img_v, lower_left_g, lower_right_g, CV_RGB( 0, 255, 0 ), 3);
		cv::line(dst_img_v, upper_right_g, lower_right_g, CV_RGB( 0, 255, 0 ), 3);
		cv::line(dst_img_v, upper_left_g, lower_left_g, CV_RGB( 0, 255, 0 ), 3);

		cv::line(dst_img_v, center_left, center_right, CV_RGB(0, 0, 255), 3);
		cv::circle(dst_img_v, court_center, 20, CV_RGB(0, 0, 255), 3);

		cv::line(dst_img_v, cvPoint(0, target_destanceY), cvPoint(CAM_PIX_WIDTH, target_destanceY), CV_RGB(255, 0, 0), 3);

		cv::imshow("camera all",dst_img_v);

		if(cv::waitKey(30) >= 0){
			//cv::imwrite("photodir/table2.png", dst_img_v);
			break;
		}
	}

	cvDestroyWindow("camera all");
	cvReleaseCapture(&src1);
	cvReleaseCapture(&src2);
	mat_frame1.release();
	mat_frame2.release();
	dst_img_v.release();
	return 0;
}
