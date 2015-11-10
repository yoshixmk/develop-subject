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
    IplImage *src_img, *dst_img1, *dst_img2;
    CvMat *map_matrix1, *map_matrix2;
    CvPoint2D32f src_pnt[4], dst_pnt[4];

    int npts_robot[2] = { 4, 8 };

    // 画像を読み込む
    if ((src_img = cvLoadImage ("camera/photodir/table.png", CV_LOAD_IMAGE_COLOR)) == 0)
        return -1;
    dst_img1 = cvCreateImage(cvGetSize(src_img), IPL_DEPTH_8U, 3);
        cvCopy(src_img, dst_img1);
	dst_img2 = cvCreateImage(cvGetSize(src_img), IPL_DEPTH_8U, 3);
		cvCopy(src_img, dst_img2);

    cvNamedWindow ("Image", CV_WINDOW_AUTOSIZE);
    cvNamedWindow ("ROIImage1", CV_WINDOW_AUTOSIZE);
    cvNamedWindow ("ROIImage2", CV_WINDOW_AUTOSIZE);
//    cvNamedWindow ("PerspectiveImage", CV_WINDOW_AUTOSIZE);

    CvPoint **pts_robot;

	CvPoint center_frame_left = cvPoint(11, CAM_PIX_HEIGHT);
	CvPoint center_frame_right = cvPoint(155, CAM_PIX_HEIGHT);

	cvSetImageROI(dst_img1, cvRect(0, 0, CAM_PIX_WIDTH, CAM_PIX_HEIGHT));
	cvSetImageROI(dst_img2, cvRect(0, 0, CAM_PIX_WIDTH, CAM_PIX_HEIGHT));

	// (2)四角形の変換前と変換後の対応する頂点をそれぞれセットし
	//    cvWarpPerspectiveを用いて透視投影変換行列を求める
	src_pnt[0] = cvPoint2D32f (17, 17);
	src_pnt[1] = cvPoint2D32f (0, 120);
	src_pnt[2] = cvPoint2D32f (160, 120);
	src_pnt[3] = cvPoint2D32f (147, 15);

	dst_pnt[0] = cvPoint2D32f (17, 17);
	dst_pnt[1] = cvPoint2D32f (17, 120);
	dst_pnt[2] = cvPoint2D32f (147, 120);
	dst_pnt[3] = cvPoint2D32f (147, 17);

	map_matrix1 = cvCreateMat (3, 3, CV_32FC1);
	cvGetPerspectiveTransform (src_pnt, dst_pnt, map_matrix1);

	src_pnt[0] = cvPoint2D32f (0, 0);
	src_pnt[1] = cvPoint2D32f (15, 113);
	src_pnt[2] = cvPoint2D32f (145, 113);
	src_pnt[3] = cvPoint2D32f (160, 0);

	dst_pnt[0] = cvPoint2D32f (15, 0);
	dst_pnt[1] = cvPoint2D32f (15, 113);
	dst_pnt[2] = cvPoint2D32f (145, 113);
	dst_pnt[3] = cvPoint2D32f (145, 0);

	map_matrix2 = cvCreateMat (3, 3, CV_32FC1);
	cvGetPerspectiveTransform (src_pnt, dst_pnt, map_matrix2);

	// (3)指定された透視投影変換行列により，cvWarpPerspectiveを用いて画像を変換させる
	cvWarpPerspective (src_img, dst_img1, map_matrix1, CV_INTER_LINEAR + CV_WARP_FILL_OUTLIERS, cvScalarAll (100));
	cvWarpPerspective (src_img, dst_img2, map_matrix2, CV_INTER_LINEAR + CV_WARP_FILL_OUTLIERS, cvScalarAll (100));

//	pts_robot = (CvPoint **) cvAlloc (sizeof (CvPoint *) * 2);
//	pts_robot[0] = (CvPoint *) cvAlloc (sizeof (CvPoint) * 4);
//	pts_robot[1] = (CvPoint *) cvAlloc (sizeof (CvPoint) * 8);
//	pts_robot[0][0].x = 0;
//	pts_robot[0][0].y = 0;
//	pts_robot[0][1].x = 160;
//	pts_robot[0][1].y = 0;
//	pts_robot[0][2].x = 320;
//	pts_robot[0][2].y = 240;
//	pts_robot[0][3].x = 0;
//	pts_robot[0][3].y = 240;
//	pts_robot[1][0].x = 0;
//	pts_robot[1][0].y = 120;
//	pts_robot[1][1].x = 160;
//	pts_robot[1][1].y = 120;
//	pts_robot[1][2].x = 160;
//	pts_robot[1][2].y = 164;
//	pts_robot[1][3].x = 145;
//	pts_robot[1][3].y = 224;
//	pts_robot[1][4].x = 125;
//	pts_robot[1][4].y = 233;
//	pts_robot[1][5].x = 39;
//	pts_robot[1][5].y = 233;
//	pts_robot[1][6].x = 15;
//	pts_robot[1][6].y = 217;
//	pts_robot[1][7].x = 0;
//	pts_robot[1][7].y = 133;

    cvLine(src_img, center_frame_left, center_frame_right, CV_RGB( 0, 255, 255 ));

    //cvFillPoly(dst_img, pts_robot, npts_robot, 2, CV_RGB(0, 0, 0));
//    dst_img3 = cvCreateImage(cvGetSize(dst_img1), IPL_DEPTH_8U, 3);
//    dst_img3 = cvSetImageROI(dst_img2, cvRect(0, 0, CAM_PIX_WIDTH, CAM_PIX_HEIGHT));

    while(1) {
		cvShowImage ("Image", src_img);
		cvShowImage ("ROIImage1", dst_img1);
        cvShowImage ("ROIImage2", dst_img2);
        if(cv::waitKey(30) >= 0) {
            break;
        }
    }

    // 全てのウィンドウの削除
    cvDestroyAllWindows();

    cvReleaseImage(&src_img);
	cvReleaseImage (&dst_img1);
	cvReleaseImage (&dst_img2);
	cvReleaseMat (&map_matrix1);
	cvReleaseMat (&map_matrix2);
//    cvFree(&pts_robot[0]);
//    cvFree(&pts_robot[1]);
//    cvFree(pts_robot);

    return 0;
}
