#!/bin/bash

SOURCE_DIR="echo $(cd $(dirname $0);pwd)"
BUILD_DIR=${SOURCE_DIR}/build
GENERATOR_NAME="Unix Makefiles"

mkdir build
cd build

cmake \
-G "${GENERATOR_NAME}" \
--build ${BUILD_DIR} \
-D BUILD_CUDA_STUBS=OFF \
-D BUILD_DOCS=OFF \
-D BUILD_EXAMPLES=OFF \
-D BUILD_JASPER=OFF \
-D BUILD_JPEG=OFF \
-D BUILD_OPENEXR=OFF \
-D BUILD_PACKAGE=ON \
-D BUILD_PERF_TESTS=OFF \
-D BUILD_PNG=OFF \
-D BUILD_SHARED_LIBS=ON \
-D BUILD_TBB=OFF \
-D BUILD_TESTS=OFF \
-D BUILD_TIFF=OFF \
-D BUILD_WITH_DEBUG_INFO=ON \
-D BUILD_ZLIB=OFF \
-D BUILD_WEBP=OFF \
-D BUILD_opencv_apps=ON \
-D BUILD_opencv_calib3d=ON \
-D BUILD_opencv_core=ON \
-D BUILD_opencv_cudaarithm=OFF \
-D BUILD_opencv_cudabgsegm=OFF \
-D BUILD_opencv_cudacodec=OFF \
-D BUILD_opencv_cudafeatures2d=OFF \
-D BUILD_opencv_cudafilters=OFF \
-D BUILD_opencv_cudaimgproc=OFF \
-D BUILD_opencv_cudalegacy=OFF \
-D BUILD_opencv_cudaobjdetect=ON \
-D BUILD_opencv_cudaoptflow=OFF \
-D BUILD_opencv_cudastereo=OFF \
-D BUILD_opencv_cudawarping=OFF \
-D BUILD_opencv_cudev=OFF \
-D BUILD_opencv_features2d=ON \
-D BUILD_opencv_flann=ON \
-D BUILD_opencv_hal=ON \
-D BUILD_opencv_highgui=ON \
-D BUILD_opencv_imgcodecs=ON \
-D BUILD_opencv_imgproc=ON \
-D BUILD_opencv_java=OFF \
-D BUILD_opencv_ml=ON \
-D BUILD_opencv_objdetect=ON \
-D BUILD_opencv_photo=ON \
-D BUILD_opencv_python2=OFF \
-D BUILD_opencv_python3=ON \
-D BUILD_opencv_shape=ON \
-D BUILD_opencv_stitching=ON \
-D BUILD_opencv_superres=ON \
-D BUILD_opencv_ts=ON \
-D BUILD_opencv_video=ON \
-D BUILD_opencv_videoio=ON \
-D BUILD_opencv_videostab=ON \
-D BUILD_opencv_viz=OFF \
-D BUILD_opencv_world=OFF \
-D CMAKE_BUILD_TYPE=RELEASE \
-D WITH_1394=ON \
-D WITH_CUBLAS=OFF \
-D WITH_CUDA=OFF \
-D WITH_CUFFT=OFF \
-D WITH_EIGEN=ON \
-D WITH_FFMPEG=ON \
-D WITH_GDAL=OFF \
-D WITH_GPHOTO2=OFF \
-D WITH_GIGEAPI=ON \
-D WITH_GSTREAMER=ON \
-D WITH_GTK=ON \
-D WITH_INTELPERC=OFF \
-D WITH_IPP=ON \
-D WITH_IPP_A=OFF \
-D WITH_JASPER=ON \
-D WITH_JPEG=ON \
-D WITH_LIBV4L=ON \
-D WITH_OPENCL=ON \
-D WITH_OPENCLAMDBLAS=OFF \
-D WITH_OPENCLAMDFFT=OFF \
-D WITH_OPENCL_SVM=ON \
-D WITH_OPENEXR=ON \
-D WITH_OPENGL=ON \
-D WITH_OPENMP=OFF \
-D WITH_OPENNI=OFF \
-D WITH_PNG=ON \
-D WITH_PTHREADS_PF=OFF \
-D WITH_PVAPI=ON \
-D WITH_QT=ON \
-D WITH_TBB=ON \
-D WITH_TIFF=ON \
-D WITH_UNICAP=OFF \
-D WITH_V4L=OFF \
-D WITH_VTK=OFF \
-D WITH_WEBP=ON \
-D WITH_XIMEA=OFF \
-D WITH_XINE=OFF \
${SOURCE_DIR}