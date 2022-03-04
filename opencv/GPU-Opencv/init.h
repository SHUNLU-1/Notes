#ifndef INIT_H
#define INIT_H

#include <iostream>

#include "opencv2/video.hpp"
#include "opencv4/opencv2/highgui.hpp"
#include "opencv4/opencv2/imgproc.hpp"
#include "opencv4/opencv2/core.hpp"
#include <opencv4/opencv2/imgproc/types_c.h>

#include"opencv4/opencv2/core/cuda.hpp"

#include"opencv4/opencv2/cudaarithm.hpp"
#include <opencv4/opencv2/cudaimgproc.hpp>
#include <opencv4/opencv2/cudawarping.hpp>


#include "opencv2/core/utility.hpp"

#include "opencv2/cudabgsegm.hpp"

#include <opencv2/core/version.hpp>
#include <opencv2/cudaarithm.hpp>

using namespace std;
using namespace cv;
using namespace cv::cuda;

#define  HISTOGRAM          0                               ///<   直方图测试
#define  CUDA_DEVICE        0                               ///<   cuda设备测试
#define  GPU_THRESHOLD      0
#define  CPU_THRESHOLD !GPU_THRESHOLD


bool  Histogram(const cv::Mat image);                        ///<    直方图测试
void  video();                                               ///<    cuda读取视频
void  data_structure();                                      ///<    数据结构
void  subtract();                                            ///<    两图相减
void  add();                                                 ///<    两图相加
void  addWeighted();
void  bitwise_not();
void  cvtColor();
void  threshold();
#endif // INIT_H
