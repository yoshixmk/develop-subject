# CMakeの最低バージョンを記述
cmake_minimum_required(VERSION 2.8)
 
# ソリューション名を指定
project(SampleSolution)
 
# 実行ファイル名とソース指定
add_executable(SampleProject main.cpp)

# OpenCVインストールパスを指定
set(OpenCV_DIR "C:/dev/opencv-2.4.11/build/install")
 
# OpenCVのパッケージを探す
find_package(OpenCV REQUIRED)
 
# OpenCVが見つかった場合のみ設定を行う
if(OpenCV_FOUND)
  # インクルードパスを指定
  include_directories(${OpenCV_INCLUDE_DIRS})
 
  # リンクするライブラリ指定
  target_link_libraries(SampleProject ${OpenCV_LIBS})
endif(OpenCV_FOUND)