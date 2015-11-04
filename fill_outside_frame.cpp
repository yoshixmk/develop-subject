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
    //cvNamedWindow ("FillImage", CV_WINDOW_AUTOSIZE);

    cvLine(src_img, cvPoint(11, CAM_PIX_HEIGHT), cvPoint(155, CAM_PIX_HEIGHT), CV_RGB( 0, 255, 255 ));

    while(1) {
		cvShowImage ("Image", src_img);
        //cvShowImage ("FillImage", dst_img);
        if(cv::waitKey(30) >= 0) {
            break;
        }
    }

    // 全てのウィンドウの削除
    cvDestroyAllWindows();

    cvReleaseImage(&src_img);

    return 0;
}
