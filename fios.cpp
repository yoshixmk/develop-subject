#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <time.h>
#include <stdio.h>

#define CAM_PIX_2HEIGHT (2 * CAM_PIX_HEIGHT)
#define CAM_PIX_WIDTH  160
#define CAM_PIX_HEIGHT 120

int main(int argc, char* argv[])
{
    IplImage *src_img, *dst_img;
    int npts[2] = { 4, 12 };
	CvCapture* capture_robot_side = cvCaptureFromCAM(0);
	CvCapture* capture_human_side = cvCaptureFromCAM(1);
    if(capture_robot_side == NULL){
		//std::cout << "Robot Side Camera Capture FAILED" << std::endl;
		return -1;
	 }
	if(capture_human_side ==NULL){
		//std::cout << "Human Side Camera Capture FAILED" << std::endl;
		return -1;
	}
int fps = 60;
	// size設定
    cvSetCaptureProperty(capture_robot_side,CV_CAP_PROP_FRAME_WIDTH,CAM_PIX_WIDTH);
	cvSetCaptureProperty(capture_robot_side,CV_CAP_PROP_FRAME_HEIGHT,CAM_PIX_HEIGHT);
	cvSetCaptureProperty(capture_human_side,CV_CAP_PROP_FRAME_WIDTH,CAM_PIX_WIDTH);
	cvSetCaptureProperty(capture_human_side,CV_CAP_PROP_FRAME_HEIGHT,CAM_PIX_HEIGHT);
	//fps設定
	cvSetCaptureProperty(capture_robot_side,CV_CAP_PROP_FPS,fps);
	cvSetCaptureProperty(capture_human_side,CV_CAP_PROP_FPS,fps);
		// 画像ファイルポインタの宣言
	IplImage* img_robot_side = cvQueryFrame(capture_robot_side);
	IplImage* img_human_side = cvQueryFrame(capture_human_side);
	IplImage* img_all_round = cvCreateImage(cvSize(CAM_PIX_WIDTH, CAM_PIX_2HEIGHT), IPL_DEPTH_8U, 3);
	
	cv::Mat mat_frame1;
	cv::Mat mat_frame2;
	cv::Mat dst_img_v;

	IplImage* dst_img_frame = cvCreateImage(cvGetSize(img_all_round), IPL_DEPTH_8U, 3);
	IplImage* grayscale_img = cvCreateImage(cvGetSize(img_all_round), IPL_DEPTH_8U, 1);
	IplImage* poly_tmp = cvCreateImage( cvGetSize( img_all_round), IPL_DEPTH_8U, 1);
	IplImage* poly_dst = cvCreateImage( cvGetSize( img_all_round), IPL_DEPTH_8U, 3);
	IplImage* poly_gray = cvCreateImage( cvGetSize(img_all_round),IPL_DEPTH_8U,1);

	int rotate_times = 0;
	//IplImage* -> Mat
	mat_frame1 = cv::cvarrToMat(img_robot_side);
	mat_frame2 = cv::cvarrToMat(img_human_side);
	//上下左右を反転。本番環境では、mat_frame1を反転させる
	cv::flip(mat_frame1, mat_frame1, 0); //水平軸で反転（垂直反転）
	cv::flip(mat_frame1, mat_frame1, 1); //垂直軸で反転（水平反転）
	vconcat(mat_frame2, mat_frame1, dst_img_v);

	*img_all_round = dst_img_v;
    cvNamedWindow ("Image", CV_WINDOW_AUTOSIZE);
    cvNamedWindow ("FillImage", CV_WINDOW_AUTOSIZE);

    CvPoint **pts;

	CvPoint center_frame_left = cvPoint(11, CAM_PIX_HEIGHT);
	CvPoint center_frame_right = cvPoint(155, CAM_PIX_HEIGHT);

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

    while(1) {
	img_robot_side = cvQueryFrame(capture_robot_side);
			img_human_side = cvQueryFrame(capture_human_side);
			//IplImage* -> Mat
			mat_frame1 = cv::cvarrToMat(img_robot_side);
			mat_frame2 = cv::cvarrToMat(img_human_side);
			//上下左右を反転。本番環境では、mat_frame1を反転させる
			cv::flip(mat_frame1, mat_frame1, 0); //水平軸で反転（垂直反転）
			cv::flip(mat_frame1, mat_frame1, 1); //垂直軸で反転（水平反転）
			vconcat(mat_frame2, mat_frame1, dst_img_v);
				*img_all_round = dst_img_v;
			
			cvLine(img_all_round, center_frame_left, center_frame_right, CV_RGB( 0, 255, 255 ));
		dst_img = cvCreateImage(cvGetSize(img_all_round), IPL_DEPTH_8U, 3);
		cvCopy(img_all_round, dst_img);

		cvFillPoly(dst_img, pts, npts, 2, CV_RGB(0, 0, 0));
			
		cvShowImage ("Image", img_all_round);
        cvShowImage ("FillImage", dst_img);
        if(cv::waitKey(30) >= 0) {
            break;
        }
    }

    // 全てのウィンドウの削除
    cvDestroyAllWindows();

    cvReleaseImage(&src_img);
    cvFree(&pts[0]);
    cvFree(&pts[1]);
    cvFree(pts);

    return 0;
}
