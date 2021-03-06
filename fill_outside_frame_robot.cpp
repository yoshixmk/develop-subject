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
    int npts_robot[2] = { 4, 8 };
    
    // 画像を読み込む
    if ((src_img = cvLoadImage ("camera/photodir/table.png", CV_LOAD_IMAGE_COLOR)) == 0)
        return -1;

    cvNamedWindow ("Image", CV_WINDOW_AUTOSIZE);
    cvNamedWindow ("FillImage", CV_WINDOW_AUTOSIZE);

    CvPoint **pts_robot;

	CvPoint center_frame_left = cvPoint(11, CAM_PIX_HEIGHT);
	CvPoint center_frame_right = cvPoint(155, CAM_PIX_HEIGHT);

	pts_robot = (CvPoint **) cvAlloc (sizeof (CvPoint *) * 2);
	pts_robot[0] = (CvPoint *) cvAlloc (sizeof (CvPoint) * 4);
	pts_robot[1] = (CvPoint *) cvAlloc (sizeof (CvPoint) * 8);
	pts_robot[0][0].x = 0;
	pts_robot[0][0].y = 0;
	pts_robot[0][1].x = 160;
	pts_robot[0][1].y = 0;
	pts_robot[0][2].x = 320;
	pts_robot[0][2].y = 240;
	pts_robot[0][3].x = 0;
	pts_robot[0][3].y = 240;
	pts_robot[1][0].x = 0;
	pts_robot[1][0].y = 120;
	pts_robot[1][1].x = 160;
	pts_robot[1][1].y = 120;
	pts_robot[1][2].x = 160;
	pts_robot[1][2].y = 164;
	pts_robot[1][3].x = 145;
	pts_robot[1][3].y = 224;
	pts_robot[1][4].x = 125;
	pts_robot[1][4].y = 233;
	pts_robot[1][5].x = 39;
	pts_robot[1][5].y = 233;
	pts_robot[1][6].x = 15;
	pts_robot[1][6].y = 217;
	pts_robot[1][7].x = 0;
	pts_robot[1][7].y = 133;

    cvLine(src_img, center_frame_left, center_frame_right, CV_RGB( 0, 255, 255 ));
    dst_img = cvCreateImage(cvGetSize(src_img), IPL_DEPTH_8U, 3);
    cvCopy(src_img, dst_img);

    cvFillPoly(dst_img, pts_robot, npts_robot, 2, CV_RGB(0, 0, 0));

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
    cvFree(&pts_robot[0]);
    cvFree(&pts_robot[1]);
    cvFree(pts_robot);

    return 0;
}



