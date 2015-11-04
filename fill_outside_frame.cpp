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

    // 画像を読み込む
    if ((src_img = cvLoadImage ("camera/photodir/table.png", CV_LOAD_IMAGE_COLOR)) == 0)
        return -1;

    cvNamedWindow ("Image", CV_WINDOW_AUTOSIZE);
    cvNamedWindow ("FillImage", CV_WINDOW_AUTOSIZE);
    CvPoint out_frame_robot[10];
    CvPoint out_frame_human[10];
	CvPoint upper_left_f, upper_left_g, upper_right_f, upper_right_g,
			lower_left_f, lower_left_g, lower_right_f, lower_right_g;
	CvPoint center_frame_left = cvPoint(11, CAM_PIX_HEIGHT);
	CvPoint center_frame_right = cvPoint(155, CAM_PIX_HEIGHT);

	out_frame_human[0] = upper_left_f = cvPoint(26, 29);
	out_frame_human[3] = upper_right_f = cvPoint(136, 29);
	out_frame_robot[0] = lower_left_f = cvPoint(26, 220);
	out_frame_robot[3] = lower_right_f =  cvPoint(136, 220);

	out_frame_human[1] = upper_left_g = cvPoint(38, 22);
	out_frame_human[2] = upper_right_g = cvPoint(125, 22);
	out_frame_robot[1] = lower_left_g =  cvPoint(38, 226);
	out_frame_robot[2] = lower_right_g = cvPoint(125, 226);

	out_frame_human[4] = center_frame_right;
	out_frame_human[5] = cvPoint(CAM_PIX_WIDTH, CAM_PIX_HEIGHT);
	out_frame_human[6] = cvPoint(CAM_PIX_WIDTH, 0);
	out_frame_human[7] = cvPoint(0, 0);
	out_frame_human[8] = cvPoint(0, CAM_PIX_HEIGHT);
	out_frame_human[9] = center_frame_left;

	out_frame_robot[4] = center_frame_right;
	out_frame_robot[5] = cvPoint(CAM_PIX_WIDTH, CAM_PIX_HEIGHT);
	out_frame_robot[6] = cvPoint(CAM_PIX_WIDTH, CAM_PIX_2HEIGHT);
	out_frame_robot[7] = cvPoint(0, CAM_PIX_2HEIGHT);
	out_frame_robot[8] = cvPoint(0, CAM_PIX_HEIGHT);
	out_frame_robot[9] = center_frame_left;

    cvLine(src_img, center_frame_left, center_frame_right, CV_RGB( 0, 255, 255 ));
    dst_img = cvCreateImage(cvGetSize(src_img), IPL_DEPTH_8U, 3);
    cvCopy(src_img, dst_img);
    cvFillConvexPoly(dst_img, out_frame_human, 10, CV_RGB(0, 0, 0));
    cvFillConvexPoly(dst_img, out_frame_robot, 10, CV_RGB(0, 0, 0));
    while(1) {
		cvShowImage ("Image", src_img);
        cvShowImage ("FillImage", dst_img);
        if(cv::waitKey(30) >= 0) {
            break;
        }
    }

    // 全てのウィンドウの削除
    cvDestroyAllWindows();

    cvReleaseImage(&src_img);

    return 0;
}
