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



//---------------------------------------------------------------
//【関数名　】：cv_ColorExtraction
//【処理概要】：色抽出
//【引数　　】：src_img        = 入力画像(8bit3ch)
//　　　　　　：dst_img        = 出力画像(8bit3ch)
//　　　　　　：code        = 色空間の指定（CV_BGR2HSV,CV_BGR2Labなど）
//　　　　　　：ch1_lower    = ch1のしきい値(小)
//　　　　　　：ch1_upper    = ch1のしきい値(大)
//　　　　　　：ch2_lower    = ch2のしきい値(小)
//　　　　　　：ch2_upper    = ch2のしきい値(大)
//　　　　　　：ch3_lower    = ch3のしきい値(小)
//　　　　　　：ch3_upper    = ch3のしきい値(大)
//【戻り値　】：なし
//【備考　　】：lower <= upperの場合、lower以上upper以下の範囲を抽出、
//　　　　　　：lower >  upperの場合、upper以下lower以上の範囲を抽出します。
//---------------------------------------------------------------
void cv_ColorExtraction(IplImage* src_img, IplImage* dst_img,
                        int code,
                        int ch1_lower, int ch1_upper,
                        int ch2_lower, int ch2_upper,
                        int ch3_lower, int ch3_upper
                       ) {

    int i, k;

    IplImage *Color_img;
    IplImage *ch1_img, *ch2_img, *ch3_img;
    IplImage *Mask_img;

    int lower[3];
    int upper[3];
    int val[3];

    CvMat *lut;

    //codeに基づいたカラー変換
    Color_img = cvCreateImage(cvGetSize(src_img), src_img->depth, src_img->nChannels);
    cvCvtColor(src_img, Color_img, code);

    //3ChのLUT作成
    lut    = cvCreateMat(256, 1, CV_8UC3);

    lower[0] = ch1_lower;
    lower[1] = ch2_lower;
    lower[2] = ch3_lower;

    upper[0] = ch1_upper;
    upper[1] = ch2_upper;
    upper[2] = ch3_upper;

    for (i = 0; i < 256; i++) {
        for (k = 0; k < 3; k++) {
            if (lower[k] <= upper[k]) {
                if ((lower[k] <= i) && (i <= upper[k])) {
                    val[k] = 255;
                } else {
                    val[k] = 0;
                }
            } else {
                if ((i <= upper[k]) || (lower[k] <= i)) {
                    val[k] = 255;
                } else {
                    val[k] = 0;
                }
            }
        }
        //LUTの設定
        cvSet1D(lut, i, cvScalar(val[0], val[1], val[2]));
    }

    //3ChごとのLUT変換（各チャンネルごとに２値化処理）
    cvLUT(Color_img, Color_img, lut);
    cvReleaseMat(&lut);

    //各チャンネルごとのIplImageを確保する
    ch1_img = cvCreateImage(cvGetSize(Color_img), Color_img->depth, 1);
    ch2_img = cvCreateImage(cvGetSize(Color_img), Color_img->depth, 1);
    ch3_img = cvCreateImage(cvGetSize(Color_img), Color_img->depth, 1);

    //チャンネルごとに二値化された画像をそれぞれのチャンネルに分解する
    cvSplit(Color_img, ch1_img, ch2_img, ch3_img, NULL);

    //3Ch全てのANDを取り、マスク画像を作成する。
    Mask_img = cvCreateImage(cvGetSize(Color_img), Color_img->depth, 1);
    cvAnd(ch1_img, ch2_img, Mask_img);
    cvAnd(Mask_img, ch3_img, Mask_img);

    //入力画像(src_img)のマスク領域を出力画像(dst_img)へコピーする
    cvZero(dst_img);
    cvCopy(src_img, dst_img, Mask_img);

    //解放
    cvReleaseImage(&Color_img);
    cvReleaseImage(&ch1_img);
    cvReleaseImage(&ch2_img);
    cvReleaseImage(&ch3_img);
    cvReleaseImage(&Mask_img);

}

/* コールバック関数 */
/*void
on_mouse (int event, int x, int y, int flags, void *param = NULL)
{
  char str[64];
  static int line = 0;
  const int max_line = 15, w = 15, h = 30;

  // (4)マウスイベントを取得
  switch (event) {
  case CV_EVENT_MOUSEMOVE:
    snprintf (str, 64, "(%d,%d) %s", x, y, "MOUSE_MOVE");
    break;
  case CV_EVENT_LBUTTONDOWN:
    snprintf (str, 64, "(%d,%d) %s", x, y, "LBUTTON_DOWN");
    break;
  case CV_EVENT_RBUTTONDOWN:
    snprintf (str, 64, "(%d,%d) %s", x, y, "RBUTTON_DOWN");
    break;
  case CV_EVENT_MBUTTONDOWN:
    snprintf (str, 64, "(%d,%d) %s", x, y, "MBUTTON_DOWN");
    break;
  case CV_EVENT_LBUTTONUP:
    snprintf (str, 64, "(%d,%d) %s", x, y, "LBUTTON_UP");
    break;
  case CV_EVENT_RBUTTONUP:
    snprintf (str, 64, "(%d,%d) %s", x, y, "RBUTTON_UP");
    break;
  case CV_EVENT_MBUTTONUP:
    snprintf (str, 64, "(%d,%d) %s", x, y, "MBUTTON_UP");
    break;
  case CV_EVENT_LBUTTONDBLCLK:
    snprintf (str, 64, "(%d,%d) %s", x, y, "LBUTTON_DOUBLE_CLICK");
    break;
  case CV_EVENT_RBUTTONDBLCLK:
    snprintf (str, 64, "(%d,%d) %s", x, y, "RBUTTON_DOUBLE_CLICK");
    break;
  case CV_EVENT_MBUTTONDBLCLK:
    snprintf (str, 64, "(%d,%d) %s", x, y, "MBUTTON_DOUBLE_CLICK");
    break;
  }

  // (5)マウスボタン，修飾キーを取得
  if (flags & CV_EVENT_FLAG_LBUTTON)
    strncat (str, " + LBUTTON", 64);
  if (flags & CV_EVENT_FLAG_RBUTTON)
    strncat (str, " + RBUTTON", 64);
  if (flags & CV_EVENT_FLAG_MBUTTON)
    strncat (str, " + MBUTTON", 64);
  if (flags & CV_EVENT_FLAG_CTRLKEY)
    strncat (str, " + CTRL", 64);
  if (flags & CV_EVENT_FLAG_SHIFTKEY)
    strncat (str, " + SHIFT", 64);
  if (flags & CV_EVENT_FLAG_ALTKEY)
    strncat (str, " + ALT", 64);

  // (6)マウス座標，イベント，修飾キーなどを画像に描画，表示
  if (line > max_line) {
    cvGetRectSubPix (img, img, cvPoint2D32f (320 - 0.5, 240 - 0.5 + h));
    cvPutText (img, str, cvPoint (w, 20 + h * max_line), &font, CV_RGB (0, 200, 100));
  }
  else {
    cvPutText (img, str, cvPoint (w, 20 + h * line), &font, CV_RGB (0, 200, 100));
  }
  line++;
  cvShowImage ("Image", img);
}*/


int main(int argc, char* argv[])
{
    IplImage *src_img, *dst_img, *poly_dst, *poly_tmp, *poly_gray;
    CvMemStorage *contStorage = cvCreateMemStorage(0);
    CvSeq *contours;
    CvTreeNodeIterator polyIterator;
    int found = 0;
    int i;
    CvPoint poly_point;

    // ポリライン近似
    CvMemStorage *polyStorage = cvCreateMemStorage(0);
    CvSeq *polys, *poly;

    // (1)画像を読み込む
    /*if ((src_img = cvLoadImage ("../camera/photodir/capmallet1.png", CV_LOAD_IMAGE_GRAYSCALE)) == 0)
        return -1;*/
    
    if ((dst_img = cvLoadImage ("../camera/photodir/capmallet1.png", CV_LOAD_IMAGE_COLOR )) == 0)
        return -1;
    IplImage *scale_image=cvCreateImage(cvSize(160, 120), IPL_DEPTH_8U, 3);
    cvResize(dst_img, scale_image, CV_INTER_LINEAR);
    src_img = cvCreateImage(cvGetSize(scale_image), IPL_DEPTH_8U, 1);
    IplImage* dst_img_pack = cvCreateImage(cvGetSize(scale_image), IPL_DEPTH_8U, 3);
	cv_ColorExtraction(scale_image, dst_img_pack, CV_BGR2HSV, 0, 54, 77, 255, 0, 255);
	
	cvCvtColor(dst_img_pack, src_img, CV_BGR2GRAY);
    cv_Labelling(src_img, scale_image);

    poly_gray = cvCreateImage( cvGetSize(scale_image),IPL_DEPTH_8U,1);
    cvCvtColor(scale_image, poly_gray, CV_BGR2GRAY);

    poly_tmp = cvCreateImage( cvGetSize( poly_gray), IPL_DEPTH_8U, 1);
    poly_dst = cvCreateImage( cvGetSize( poly_gray), IPL_DEPTH_8U, 3);
    cvCopy( poly_gray, poly_tmp);
    cvCvtColor( poly_gray, poly_dst, CV_GRAY2BGR);

    // 輪郭抽出
    found = cvFindContours( poly_tmp, contStorage, &contours, sizeof( CvContour), CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);

    // ポリライン近似
    polys = cvApproxPoly( contours, sizeof( CvContour), polyStorage, CV_POLY_APPROX_DP, 8, 10);

     // 表示
    cvDrawContours( poly_dst, contours, OUTLINE_COLOR, HOLE_COLOR, 10, 2, 4, cvPoint( 0, 0));

    cvInitTreeNodeIterator( &polyIterator, ( void*)polys, 10);
    while( (poly = (CvSeq *)cvNextTreeNode( &polyIterator)) != NULL)
    {
            for( i=0; i<poly->total; i++)
            {
                poly_point = *( CvPoint*)cvGetSeqElem( poly, i);
                cvCircle( poly_dst, poly_point, 1, CV_RGB(255, 0 , 255), -1);
                cvCircle( poly_dst, poly_point, 8, CV_RGB(255, 0 , 255));
                std::cout << "x:" << poly_point.x << ", y:" << poly_point.y  << std::endl;
            }
    }

	cv::Mat eigen_img = cv::cvarrToMat(scale_image);  // データをコピーする

	Mat gray_img;
    cvtColor(eigen_img, gray_img, CV_BGR2GRAY);
    normalize(gray_img, gray_img, 0, 255, NORM_MINMAX);

    vector<Point2f> corners;
    goodFeaturesToTrack(gray_img, corners, 80, 0.01, 5);
    vector<Point2f>::iterator it_corner = corners.begin();
    for(; it_corner!=corners.end(); ++it_corner) {
        //if((it_corner->y < 76 || 345 < it_corner->y) && (it_corner->x < 75 || 690 < it_corner->x) ){
            circle(eigen_img, Point(it_corner->x, it_corner->y), 1, Scalar(0,200,255), -1);
            circle(eigen_img, Point(it_corner->x, it_corner->y), 8, Scalar(0,200,255));
            //std::cout << "x:" << it_corner->x << ", y:" << it_corner->y  << std::endl;
        //}
    }

    cvNamedWindow ("Image", CV_WINDOW_AUTOSIZE);
    cvNamedWindow ("Poly", CV_WINDOW_AUTOSIZE);
    while(1) {
        cvShowImage ("Image", scale_image);
        cvShowImage ("Poly", poly_dst);
        if(cv::waitKey(30) >= 0) {
            break;
        }
    }

    // 全てのウィンドウの削除
    cvDestroyAllWindows();

    cvReleaseImage (&dst_img);
    cvReleaseImage (&scale_image);


    return 0;
}
