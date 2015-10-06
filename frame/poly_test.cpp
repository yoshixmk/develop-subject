#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <time.h>
#include <stdio.h>

void GetContourFeature(CvSeq *Contour);
void DrawChildContour(       
                IplImage *img,    //ﾗﾍﾞﾘﾝｸﾞ結果を描画するIplImage(8Bit3chｶﾗｰ)
                CvSeq *Contour, //輪郭へのﾎﾟｲﾝﾀ
                int Level             //輪郭のﾚﾍﾞﾙ(階層)
                );

////////////////////////////////////////////////////////////////
//  次の輪郭を描画する｡
////////////////////////////////////////////////////////////////
void DrawNextContour(       
                IplImage *img,    //ﾗﾍﾞﾘﾝｸﾞ結果を描画するIplImage(8Bit3chｶﾗｰ)
                CvSeq *Contour, //輪郭へのﾎﾟｲﾝﾀ
                int Level            //輪郭のﾚﾍﾞﾙ(階層)
                ){

      // 輪郭を描画する色の設定
      CvScalar ContoursColor;

      if ((Level % 2) == 1){
            //白の輪郭の場合､赤で輪郭を描画
            ContoursColor = CV_RGB( 255, 0, 0 );
      }else{
            //黒の輪郭の場合､青で輪郭を描画
            ContoursColor = CV_RGB( 0, 0, 255 );
      }
             
      //輪郭の描画
      cvDrawContours( img, Contour, ContoursColor, ContoursColor, 0, 2);

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
//  子の輪郭を描画する｡
////////////////////////////////////////////////////////////////
void DrawChildContour(       
                IplImage *img,    //ﾗﾍﾞﾘﾝｸﾞ結果を描画するIplImage(8Bit3chｶﾗｰ)
                CvSeq *Contour, //輪郭へのﾎﾟｲﾝﾀ
                int Level             //輪郭のﾚﾍﾞﾙ(階層)
                ){
             
      // 輪郭を描画する色の設定
      CvScalar ContoursColor;

      if ((Level % 2) == 1){
            //白の輪郭の場合､赤で輪郭を描画
            ContoursColor = CV_RGB( 255, 0, 0 );
      }else{
            //黒の輪郭の場合､青で輪郭を描画
            ContoursColor = CV_RGB( 0, 0, 255 );
      }
             
      //輪郭の描画
      cvDrawContours( img, Contour, ContoursColor, ContoursColor, 0, 2);
             
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

      if (contours != NULL){
            //処理後画像を0(黒)で初期化
            cvSet(dst_img, CV_RGB( 0, 0, 0 ));
            //輪郭の描画
            DrawNextContour(dst_img, contours, 1);
      }

      //ﾒﾓﾘｽﾄﾚｰｼﾞの解放
      cvReleaseMemStorage (&storage);
}

//各種輪郭の特徴量の取得
void GetContourFeature(CvSeq *Contour){
   //面積
   double Area = fabs(cvContourArea(Contour, CV_WHOLE_SEQ));
   //周囲長
   double Perimeter = cvArcLength(Contour);
   //円形度
   double CircleLevel = 4.0 * CV_PI * Area / (Perimeter * Perimeter);

   //傾いていない外接四角形領域(ﾌｨﾚ径)
   CvRect rect = cvBoundingRect(Contour);
   //輪郭を構成する頂点座標を取得
   for ( int i = 0; i < Contour->total; i++){
            CvPoint *point = CV_GET_SEQ_ELEM (CvPoint, Contour, i);
             std::cout << "x:" << point->x << ", y:" << point->y  << std::endl;
            
   }
}

int main(int argc, char* argv[])
{
  IplImage *src_img, *src_img2, *dst_img, *tmp, *dst;
  CvMemStorage *contStorage = cvCreateMemStorage(0);
  CvSeq *contours;
  CvTreeNodeIterator polyIterator;
  int found = 0;
  int i;
  CvPoint point;
  // ポリライン近似
  CvMemStorage *polyStorage = cvCreateMemStorage(0);
  CvSeq *polys, *poly;

  // (1)画像を読み込む
  if ((src_img = cvLoadImage ("ah01.jpg", CV_LOAD_IMAGE_GRAYSCALE)) == 0)
    return -1;
  if ((dst_img = cvLoadImage ("ah01.jpg", CV_LOAD_IMAGE_COLOR )) == 0)
  return -1;

  if ((src_img2 = cvLoadImage ("ah01.jpg", CV_LOAD_IMAGE_GRAYSCALE )) == 0)
  return -1;
  cv_Labelling(src_img, dst_img);
  tmp = cvCreateImage( cvGetSize( src_img2), IPL_DEPTH_8U, 1);
  dst = cvCreateImage( cvGetSize( src_img2), IPL_DEPTH_8U, 3);

  cvCopy( src_img2, tmp);
  cvCvtColor( src_img2, dst, CV_GRAY2BGR);
  

  found = cvFindContours( tmp, contStorage, &contours, sizeof( CvContour), CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE);

  polys = cvApproxPoly( contours, sizeof( CvContour), polyStorage , CV_POLY_APPROX_DP, 7, 10);

  cvInitTreeNodeIterator( &polyIterator, ( void*)polys, 10);
  while( (poly = (CvSeq *)cvNextTreeNode( &polyIterator)) != NULL)
  {
    //４点の領域が1000（適当）以上のとき、その４点を描画
    if( ( abs(cvContourArea(poly, CV_WHOLE_SEQ) > 100 ) ) ){
        for( i = 0 ; i < poly -> total ; i++ )
        {
            point = *( CvPoint*)cvGetSeqElem( poly, i);
            cvCircle( dst, point, 5, CV_RGB(0,0,255), 1);
            std::cout << "x:" << point.x << ", y:" << point.y  << std::endl;
        }
    }
  }

  

  while(1){
        // 画像の表示
  cvNamedWindow ("Image", CV_WINDOW_AUTOSIZE);
  cvNamedWindow( "Poly", CV_WINDOW_AUTOSIZE);
  cvShowImage ("Image", dst_img);
  cvShowImage( "Poly", dst);
  if(cv::waitKey(30) >= 0) {
    break;
    }
  }
  
  // 全てのウィンドウの削除
  cvDestroyAllWindows();

  cvReleaseImage (&src_img);
  cvReleaseImage (&dst_img);
  cvReleaseImage( &src_img2);
  cvReleaseImage( &dst);
  cvReleaseImage( &tmp);
  cvReleaseMemStorage( &polyStorage);
  
  return 0;
}