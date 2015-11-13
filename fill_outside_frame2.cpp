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

    // 画像を読み込む
    if ((src_img = cvLoadImage ("camera/photodir/table.png", CV_LOAD_IMAGE_COLOR)) == 0)
        return -1;

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

    cvLine(src_img, center_frame_left, center_frame_right, CV_RGB( 0, 255, 255 ));
    dst_img = cvCreateImage(cvGetSize(src_img), IPL_DEPTH_8U, 3);
    cvCopy(src_img, dst_img);

    cvFillPoly(dst_img, pts, npts, 2, CV_RGB(0, 0, 0));

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
    cvFree(&pts[0]);
    cvFree(&pts[1]);
    cvFree(pts);

    return 0;
}
