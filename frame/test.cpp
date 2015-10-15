#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <time.h>
#include <stdio.h>

#define OUTLINE_COLOR   CV_RGB( 255, 0, 0)
#define HOLE_COLOR      CV_RGB( 0, 255, 0)
#define VIRTEX_COLOR    CV_RGB( 0, 0, 255)

#define CAM_PIX_2HEIGHT (2 * CAM_PIX_HEIGHT)
#define CAM_PIX_WIDTH  160
#define CAM_PIX_HEIGHT 120

int main(int argc, char* argv[])
{
    IplImage *src_img, *dst_img, *poly_dst, *poly_tmp, *poly_gray, *ipl_concat;
    CvMemStorage *contStorage = cvCreateMemStorage(0);
    CvSeq *contours;
    CvTreeNodeIterator polyIterator;
    int found = 0;
    int i;
    CvPoint poly_point;

    // ポリライン近似
    CvMemStorage *polyStorage = cvCreateMemStorage(0);
    CvSeq *polys, *poly;

    CvCapture* capture_robot_side;
    CvCapture* capture_human_side;
    capture_robot_side = cvCaptureFromCAM(0);
    capture_human_side = cvCaptureFromCAM(1);
    
    int c;
    int fps=30;
    int iSliderValue1 = 50;
    int iSliderValue2 = 50;
 
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
    IplImage* img2  = cvCreateImage(cvGetSize(img_all_round), IPL_DEPTH_8U, 3);
    IplImage* show_img  = cvCreateImage(cvGetSize(img_all_round), IPL_DEPTH_8U, 3);

    //IplImage* -> Mat
    cv::Mat pre_src;
    cv::Mat pre_dst;
    pre_src = cv::cvarrToMat(img_robot_side);
    int iBrightness  = iSliderValue1 - 50;
    double dContrast = iSliderValue2 / 50.0;
    pre_src.convertTo(pre_dst, -1, dContrast, iBrightness); 
    //明るさ調整した結果を変換(Mat->IplImage*)して渡す。その後解放。
    *img_robot_side = pre_dst;
    pre_src.release();

    cv::Mat mat_frame1;
    cv::Mat mat_frame2;
    cv::Mat dst_img_v;
    cv::Mat dst_bright_cont;
    int rotate_times = 0;

    cvNamedWindow ("Vertical Concat", CV_WINDOW_AUTOSIZE);

    while(1) {
        //cvCopy(img_all_round, img2);
	    //cvCopy(img_all_round, show_img);
	    img_robot_side = cvQueryFrame(capture_robot_side);
	    img_human_side = cvQueryFrame(capture_human_side);
	    //IplImage* -> Mat
	    mat_frame1 = cv::cvarrToMat(img_robot_side);
	    mat_frame2 = cv::cvarrToMat(img_human_side);
	    //上下左右を反転。本番環境では、mat_frame1を反転させる
	    cv::flip(mat_frame2, mat_frame2, 0); //水平軸で反転（垂直反転）
	    cv::flip(mat_frame2, mat_frame2, 1); //垂直軸で反転（水平反転）
	    vconcat(mat_frame2, mat_frame1, dst_img_v);

	    iBrightness  = iSliderValue1 - 50;
	    dContrast = iSliderValue2 / 50.0;
	    //mat_frame1.convertTo(dst_bright_cont, -1, dContrast, iBrightness); 
	    dst_img_v.convertTo(dst_bright_cont, -1, dContrast, iBrightness); //１枚にした画像をコンバート
	    //明るさ調整した結果を変換(Mat->IplImage*)して渡す。その後解放。
	    //*img_robot_side = dst_bright_cont;
	    *img_all_round = dst_bright_cont;
	    
	    mat_frame1.release();
	    mat_frame2.release();

        cv::imshow("Vertical Concat", dst_img_v);;

        if(cv::waitKey(30) >= 0) {
            break;
        }
    }

    // 全てのウィンドウの削除
    cvDestroyAllWindows();
    cvReleaseCapture(&capture_robot_side);
    cvReleaseCapture(&capture_human_side);
    dst_img_v.release();

    return 0;
}

