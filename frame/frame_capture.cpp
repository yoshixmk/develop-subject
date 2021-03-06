#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <time.h>
#include <stdio.h>

using namespace cv;

void DrawNextContour(
    IplImage *img,    //ﾗﾍﾞﾘﾝｸﾞ結果を描画するIplImage(8Bit3chｶﾗｰ)
    CvSeq *Contour, //輪郭へのﾎﾟｲﾝﾀ
    int Level            //輪郭のﾚﾍﾞﾙ(階層)
);

double perimeter_max;
CvSeq *max_perimeter_contor;

//各種輪郭の特徴量の取得
void GetContourFeature(CvSeq *Contour) {
    //面積
    double Area = fabs(cvContourArea(Contour, CV_WHOLE_SEQ));
    //周囲長
    double Perimeter = cvArcLength(Contour);
    //円形度
    double CircleLevel = 4.0 * CV_PI * Area / (Perimeter * Perimeter);

    //傾いていない外接四角形領域(ﾌｨﾚ径)
    CvRect rect = cvBoundingRect(Contour);

    if(perimeter_max < Perimeter) {
        perimeter_max = Perimeter;
        max_perimeter_contor = Contour;
    }
}

////////////////////////////////////////////////////////////////
//  子の輪郭を描画する｡
////////////////////////////////////////////////////////////////
void DrawChildContour(
    IplImage *img,    //ﾗﾍﾞﾘﾝｸﾞ結果を描画するIplImage(8Bit3chｶﾗｰ)
    CvSeq *Contour, //輪郭へのﾎﾟｲﾝﾀ
    int Level             //輪郭のﾚﾍﾞﾙ(階層)
) {

    // 輪郭を描画する色の設定
    CvScalar ContoursColor;

    if ((Level % 2) == 1) {
        //白の輪郭の場合､赤で輪郭を描画
        ContoursColor = CV_RGB( 255, 0, 0 );
    } else {
        //黒の輪郭の場合､青で輪郭を描画
        ContoursColor = CV_RGB( 0, 0, 255 );
    }

    //輪郭の描画
    //cvDrawContours( img, Contour, ContoursColor, ContoursColor, 0, 2);

    //各種輪郭の特徴量の取得
    GetContourFeature(Contour); //←ｵﾘｼﾞﾅﾙ関数です｡(詳細は後述)

    if (Contour->h_next != NULL)
        //次の輪郭がある場合は次の輪郭を描画
        DrawNextContour(img, Contour->h_next, Level);
    if (Contour->v_next != NULL)
        //子の輪郭がある場合は子の輪郭を描画
        DrawChildContour(img, Contour->v_next, Level + 1);
}

////////////////////////////////////////////////////////////////
//  次の輪郭を描画する｡
////////////////////////////////////////////////////////////////
void DrawNextContour(
    IplImage *img,    //ﾗﾍﾞﾘﾝｸﾞ結果を描画するIplImage(8Bit3chｶﾗｰ)
    CvSeq *Contour, //輪郭へのﾎﾟｲﾝﾀ
    int Level            //輪郭のﾚﾍﾞﾙ(階層)
) {

    // 輪郭を描画する色の設定
    CvScalar ContoursColor;

    if ((Level % 2) == 1) {
        //白の輪郭の場合､赤で輪郭を描画
        ContoursColor = CV_RGB( 255, 0, 0 );
    } else {
        //黒の輪郭の場合､青で輪郭を描画
        ContoursColor = CV_RGB( 0, 0, 255 );
    }

    //輪郭の描画
    //cvDrawContours( img, Contour, ContoursColor, ContoursColor, 0, 2);

    //各種輪郭の特徴量の取得
    GetContourFeature(Contour); //←ｵﾘｼﾞﾅﾙ関数です｡(詳細は後述)

    if (Contour->h_next != NULL)
        //次の輪郭がある場合は次の輪郭を描画
        DrawNextContour(img, Contour->h_next, Level);

    if (Contour->v_next != NULL)
        //子の輪郭がある場合は子の輪郭を描画
        DrawChildContour(img, Contour->v_next, Level + 1);
}

////////////////////////////////////////////////////////////////
//  ﾗﾍﾞﾘﾝｸﾞ処理
////////////////////////////////////////////////////////////////
void cv_Labelling(
    IplImage *src_img,       //入力画像(8Bitﾓﾉｸﾛ)
    IplImage *dst_img        //出力画像(8Bit3chｶﾗｰ)
) {

    CvMemStorage *storage = cvCreateMemStorage (0);
    CvSeq *contours = NULL;

    if (src_img == NULL)
        return;

    // 画像の二値化【判別分析法(大津の二値化)】
    cvThreshold (src_img, src_img, 0, 255, CV_THRESH_BINARY | CV_THRESH_OTSU);

    // 輪郭の検出(戻り値は取得した輪郭の全個数)
    int find_contour_num = cvFindContours (
                               src_img,                     // 入力画像
                               storage,                      // 抽出された輪郭を保存する領域
                               &contours,                  // 一番外側の輪郭へのﾎﾟｲﾝﾀへのﾎﾟｲﾝﾀ
                               sizeof (CvContour),      // ｼｰｹﾝｽﾍｯﾀﾞのｻｲｽﾞ
                               CV_RETR_EXTERNAL,       // 抽出ﾓｰﾄﾞ
                               // CV_RETR_EXTERNAL - 最も外側の輪郭のみ抽出
                               // CV_RETR_LIST - 全ての輪郭を抽出し,ﾘｽﾄに追加
                               // CV_RETR_CCOMP - 全ての輪郭を抽出し,
                               // 二つのﾚﾍﾞﾙを持つ階層構造を構成する.
                               // 1番目のﾚﾍﾞﾙは連結成分の外側の境界線,
                               // 2番目のﾚﾍﾞﾙは穴(連結成分の内側に存在する)の境界線.
                               // CV_RETR_TREE - 全ての輪郭を抽出し,
                               // 枝分かれした輪郭を完全に表現する階層構造を構成する.
                               CV_CHAIN_APPROX_NONE    // CV_CHAIN_APPROX_SIMPLE:輪郭の折れ線の端点を取得
                               // CV_CHAIN_APPROX_NONE: 輪郭の全ての点を取得
                               // Teh-Chinﾁｪｰﾝの近似ｱﾙｺﾞﾘｽﾞﾑ中の一つを適用する
                               // CV_CHAIN_APPROX_TC89_L1
                               // CV_CHAIN_APPROX_TC89_KCOS
                           );

    if (contours != NULL) {
        //処理後画像を0(黒)で初期化
        cvSet(dst_img, CV_RGB( 0, 0, 0 ));
        //輪郭の描画
        DrawNextContour(dst_img, contours, 1);
    }

    cvDrawContours( dst_img, max_perimeter_contor, CV_RGB( 255, 0, 0 ), CV_RGB( 255, 0, 0 ), 0, 2);
        for ( int i = 0; i < max_perimeter_contor->total; i++) {
        CvPoint *point = CV_GET_SEQ_ELEM (CvPoint, max_perimeter_contor, i);
        //std::cout << "x:" << point->x << ", y:" << point->y  << std::endl;
    }
	//輪郭を構成する頂点座標を取得
    /*for ( int i = 0; i < Contour->total; i++) {
        CvPoint *point = CV_GET_SEQ_ELEM (CvPoint, Contour, i);
        std::cout << "x:" << point->x << ", y:" << point->y  << std::endl;

    }*/
    //ﾒﾓﾘｽﾄﾚｰｼﾞの解放
    cvReleaseMemStorage (&storage);
}



int main(int argc, char* argv[])
{
    IplImage *src_img, *dst_img;

    // (1)画像を読み込む
    /*if ((src_img = cvLoadImage ("ah01.jpg", CV_LOAD_IMAGE_GRAYSCALE)) == 0)
        return -1;
    if ((dst_img = cvLoadImage ("ah01.jpg", CV_LOAD_IMAGE_COLOR )) == 0)
        return -1;*/
        
	CvCapture* capture_allround;
    capture_allround = cvCaptureFromCAM(0);
	
    cvSetCaptureProperty(capture_allround,CV_CAP_PROP_FRAME_WIDTH,160);
	cvSetCaptureProperty(capture_allround,CV_CAP_PROP_FRAME_HEIGHT,120);
	src_img = cvCreateImage(cvSize(160, 120), IPL_DEPTH_8U, 1);
	dst_img = cvQueryFrame(capture_allround);
	cvCvtColor(dst_img, src_img, CV_BGR2GRAY);
	cvNamedWindow ("NowImage", CV_WINDOW_AUTOSIZE);
	cvShowImage ("NowImage", dst_img);
/*    cv_Labelling(src_img, dst_img);

	cv::Mat eigen_img = cv::cvarrToMat(dst_img);  // データをコピーする

	Mat gray_img;
    cvtColor(eigen_img, gray_img, CV_BGR2GRAY);
    normalize(gray_img, gray_img, 0, 255, NORM_MINMAX);

    vector<Point2f> corners;
    goodFeaturesToTrack(gray_img, corners, 80, 0.01, 5);
    vector<Point2f>::iterator it_corner = corners.begin();
    for(; it_corner!=corners.end(); ++it_corner) {
        if((it_corner->y < 76 || 345 < it_corner->y) && (it_corner->x < 75 || 690 < it_corner->x) ){
            circle(eigen_img, Point(it_corner->x, it_corner->y), 1, Scalar(0,200,255), -1);
            circle(eigen_img, Point(it_corner->x, it_corner->y), 8, Scalar(0,200,255));
            std::cout << "x:" << it_corner->x << ", y:" << it_corner->y  << std::endl;
        }
    }*/

    cvNamedWindow ("Image", CV_WINDOW_AUTOSIZE);
    cvNamedWindow ("GrayImage", CV_WINDOW_AUTOSIZE);
    while(1) {
		cvShowImage ("GrayImage", src_img);
        cvShowImage ("Image", dst_img);
        if(cv::waitKey(30) >= 0) {
            break;
        }
    }

    // 全てのウィンドウの削除
    cvDestroyAllWindows();

    cvReleaseImage (&dst_img);


    return 0;
}
