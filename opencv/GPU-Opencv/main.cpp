#include"init.h"
#include "stdio.h"
#include<iostream>
#include <cuda.h>
#include <cuda_runtime.h>
#define N	5

int main()
{
#if HISTOGRAM
///<    直方图测试
    cv::Mat image = cv::imread("/home/ubuntu/code/GPU-Opencv/5.jpg");
    if (image.empty())
    {
        return -1;
    }
    cv::resize(image,image,Size(500,500));
    Histogram(image);
#endif
#if CUDA_DEVICE
///<   cuda设备测试   #include <opencv2/core/cuda.hpp>
//    int a =cv::cuda::getDevice();
//    int b =cv::cuda::getCudaEnabledDeviceCount();

//    FeatureSet feature_set;
//    if( cv::cuda::deviceSupports(feature_set)==true){
//        cout<<"success"<<endl;
//    }
//    int c,d;
//    cv::cuda::printCudaDeviceInfo(1);
//    cv::cuda::printShortCudaDeviceInfo(1);

//    std::cout<<"a="<<a<<std::endl;
//    std::cout<<"b="<<b<<std::endl;
//    std::cout<<"c="<<c<<std::endl;
#endif



    threshold();
    std::cout<<"hshshs"<<std::endl;
    return 0;

}
