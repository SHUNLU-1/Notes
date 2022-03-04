#include"init.h"
///<    两图相加
void add(){
    int count = cuda::getCudaEnabledDeviceCount();
    printf("GPU Device Count : %d \n", count);
    //Read Two Images
    cv::Mat h_img1 = cv::imread("/home/ubuntu/code/GPU-Opencv/files/1.jpg");
    cv::Mat h_img2 = cv::imread("/home/ubuntu/code/GPU-Opencv/files/3.jpg");
    cv::resize(h_img1,h_img1,Size(500,500));
    cv::resize(h_img2,h_img2,Size(500,500));
    //Create Memory for storing Images on device
    cv::cuda::GpuMat d_result1,d_img1, d_img2;
    cv::Mat h_result1;
    //    Upload Images to device
    d_img1.upload(h_img1);
    d_img2.upload(h_img2);
    cv::cuda::add(d_img1,d_img2, d_result1);
    //Download Result back to host
    d_result1.download(h_result1);
    cv::imshow("Image1 ", h_img1);
    cv::imshow("Image2 ", h_img2);
    cv::imshow("Result addition ", h_result1);
    cv::imwrite("images/result_add.png", h_result1);
    cv::waitKey(0);
}
///<    两图相减
void subtract(){
    int count = cuda::getCudaEnabledDeviceCount();
    printf("GPU Device Count : %d \n", count);
    //Read Two Images
    cv::Mat h_img1 = cv::imread("/home/ubuntu/code/GPU-Opencv/files/1.jpg");
    cv::Mat h_img2 = cv::imread("/home/ubuntu/code/GPU-Opencv/files/3.jpg");
    cv::resize(h_img1,h_img1,Size(500,500));
    cv::resize(h_img2,h_img2,Size(500,500));
    //Create Memory for storing Images on device
    cv::cuda::GpuMat d_result1,d_img1, d_img2;
    cv::Mat h_result1;
    //Upload Images to device
    d_img1.upload(h_img1);
    d_img2.upload(h_img2);

    cv::cuda::subtract(d_img1, d_img2,d_result1);
    //Download Result back to host
    d_result1.download(h_result1);
    cv::imshow("Image1 ", h_img1);
    cv::imshow("Image2 ", h_img2);
    cv::imshow("Result Subtraction ", h_result1);
    cv::imwrite("images/result_add.png", h_result1);
    cv::waitKey(0);
}
///<
void  addWeighted(){

    int count = cuda::getCudaEnabledDeviceCount();
    printf("GPU Device Count : %d \n", count);
    //Read Two Images
    cv::Mat h_img1 = cv::imread("/home/ubuntu/code/GPU-Opencv/files/1.jpg");
    cv::Mat h_img2 = cv::imread("/home/ubuntu/code/GPU-Opencv/files/3.jpg");
    cv::resize(h_img1,h_img1,Size(500,500));
    cv::resize(h_img2,h_img2,Size(500,500));
    //Create Memory for storing Images on device
    cv::cuda::GpuMat d_result1,d_img1, d_img2;
    cv::Mat h_result1;
    //Upload Images to device
    d_img1.upload(h_img1);
    d_img2.upload(h_img2);

    cv::cuda::addWeighted(d_img1,0.7,d_img2,0.3,0,d_result1);
    //Download Result back to host
    d_result1.download(h_result1);
    cv::imshow("Image1 ", h_img1);
    cv::imshow("Image2 ", h_img2);
    cv::imshow("Result blending ", h_result1);
    cv::imwrite("images/result_add.png", h_result1);
    cv::waitKey(0);

}
///<
void  bitwise_not(){

    int count = cuda::getCudaEnabledDeviceCount();
    printf("GPU Device Count : %d \n", count);

    cv::Mat h_img1 = cv::imread("/home/ubuntu/code/GPU-Opencv/files/1.jpg");
    cv::resize(h_img1,h_img1,Size(500,500));

    //Create Device variables
    cv::cuda::GpuMat d_result1,d_img1;
    cv::Mat h_result1;
    //Upload Image to device
    d_img1.upload(h_img1);

    cv::cuda::bitwise_not(d_img1,d_result1);

    //Download result back  to host
    d_result1.download(h_result1);
    cv::imshow("Result inversion ", h_result1);
    cv::imwrite("images/result_inversion.png", h_result1);
    cv::waitKey(0);
}
///<
void cvtColor(){

    int count = cuda::getCudaEnabledDeviceCount();
    printf("GPU Device Count : %d \n", count);

    cv::Mat h_img1 = cv::imread("/home/ubuntu/code/GPU-Opencv/files/1.jpg");
    cv::resize(h_img1,h_img1,Size(500,500));

    //Define device variables
    cv::cuda::GpuMat d_result1,d_result2,d_result3,d_result4,d_img1;
    //Upload Image to device
    d_img1.upload(h_img1);

    //Convert image to different color spaces
    cv::cuda::cvtColor(d_img1, d_result1,cv::COLOR_BGR2GRAY);
    cv::cuda::cvtColor(d_img1, d_result2,cv::COLOR_BGR2RGB);
    cv::cuda::cvtColor(d_img1, d_result3,cv::COLOR_BGR2HSV);
    cv::cuda::cvtColor(d_img1, d_result4,cv::COLOR_BGR2YCrCb);

    cv::Mat h_result1,h_result2,h_result3,h_result4;
    //Download results back to host
    d_result1.download(h_result1);
    d_result2.download(h_result2);
    d_result3.download(h_result3);
    d_result4.download(h_result4);

    cv::imshow("Result in Gray ", h_result1);
    cv::imshow("Result in RGB", h_result2);
    cv::imshow("Result in HSV ", h_result3);
    cv::imshow("Result in YCrCb ", h_result4);

    cv::waitKey();

}
void threshold(){

#if CPU_THRESHOLD
    cv::Mat src = cv::imread("/home/ubuntu/code/GPU-Opencv/files/1.jpg");
    cv::resize(src,src,Size(500,500));
    cv::Mat result_host1,result_host2,result_host3,result_host4,result_host5;
    //Get initial time in miliseconds
    int64 work_begin = cv::getTickCount();
    cv::threshold(src, result_host1, 128.0, 255.0, cv::THRESH_BINARY);
    cv::threshold(src, result_host2, 128.0, 255.0, cv::THRESH_BINARY_INV);
    cv::threshold(src, result_host3, 128.0, 255.0, cv::THRESH_TRUNC);
    cv::threshold(src, result_host4, 128.0, 255.0, cv::THRESH_TOZERO);
    cv::threshold(src, result_host5, 128.0, 255.0, cv::THRESH_TOZERO_INV);

    cv::imshow("Result Threshhold binary ", result_host1);
    cv::imshow("Result Threshhold binary inverse ", result_host2);
    cv::imshow("Result Threshhold truncated ", result_host3);
    cv::imshow("Result Threshhold truncated to zero ", result_host4);
    cv::imshow("Result Threshhold truncated to zero inverse ", result_host5);

    //Get time after work has finished
    int64 delta = cv::getTickCount() - work_begin;
    //Frequency of timer
    double freq = cv::getTickFrequency();
    double work_fps = freq / delta;
    std::cout<<"Performance of Thresholding on CPU: " <<std::endl;
    std::cout <<"Time: " << (1/work_fps) <<std::endl;
    std::cout <<"FPS: " <<work_fps <<std::endl;
    cv::waitKey();

#endif

#if GPU_THRESHOLD
    int64 work_begin = cv::getTickCount();

    int count = cuda::getCudaEnabledDeviceCount();
    printf("GPU Device Count : %d \n", count);

    cv::Mat h_img1 = cv::imread("/home/ubuntu/code/GPU-Opencv/files/1.jpg");
    cv::resize(h_img1,h_img1,Size(500,500));

    //Define device variables
    cv::cuda::GpuMat d_result1,d_result2,d_result3,d_result4,d_result5, d_img1;
    //Upload image on device
    d_img1.upload(h_img1);

    //Perform different thresholding techniques on device
    cv::cuda::threshold(d_img1, d_result1, 128.0, 255.0, cv::THRESH_BINARY);
    cv::cuda::threshold(d_img1, d_result2, 128.0, 255.0, cv::THRESH_BINARY_INV);
    cv::cuda::threshold(d_img1, d_result3, 128.0, 255.0, cv::THRESH_TRUNC);
    cv::cuda::threshold(d_img1, d_result4, 128.0, 255.0, cv::THRESH_TOZERO);
    cv::cuda::threshold(d_img1, d_result5, 128.0, 255.0, cv::THRESH_TOZERO_INV);

    cv::Mat h_result1,h_result2,h_result3,h_result4,h_result5;
    //Copy results back to host
    d_result1.download(h_result1);
    d_result2.download(h_result2);
    d_result3.download(h_result3);
    d_result4.download(h_result4);
    d_result5.download(h_result5);
    cv::imshow("Result Threshhold binary ", h_result1);
    cv::imshow("Result Threshhold binary inverse ", h_result2);
    cv::imshow("Result Threshhold truncated ", h_result3);
    cv::imshow("Result Threshhold truncated to zero ", h_result4);
    cv::imshow("Result Threshhold truncated to zero inverse ", h_result5);

    int64 delta = cv::getTickCount() - work_begin;
    double freq = cv::getTickFrequency();
    //Measure frames per second
    double work_fps = freq / delta;
    std::cout <<"Performance of Thresholding on GPU: " <<std::endl;
    std::cout <<"Time: " << (1/work_fps) <<std::endl;
    std::cout <<"FPS: " <<work_fps <<std::endl;

    cv::waitKey();
#endif
}
///<   数据结构
void data_structure(){

    InputArray arra(arra);
    GpuMat src = arra.getGpuMat();
    cv::Mat a;
    cv::cuda::createContinuous(5,5,1,a);

    setBufferPoolUsage(true);                               // Tell OpenCV that we are going to utilize BufferPool
    setBufferPoolConfig(getDevice(), 1024 * 1024 * 64, 2);  // Allocate 64 MB, 2 stacks (default is 10 MB, 5 stacks)
    Stream stream1, stream2;                                // Each stream uses 1 stack
    BufferPool pool1(stream1), pool2(stream2);
    GpuMat d_src1 = pool1.getBuffer(4096, 4096, CV_8UC1);   // 16MB
    GpuMat d_dst1 = pool1.getBuffer(4096, 4096, CV_8UC3);   // 48MB, pool1 is now full
    GpuMat d_src2 = pool2.getBuffer(1024, 1024, CV_8UC1);   // 1MB
    GpuMat d_dst2 = pool2.getBuffer(1024, 1024, CV_8UC3);   // 3MB
    cvtColor(d_src1, d_dst1, CV_GRAY2BGR, 0, stream1);
    cvtColor(d_src2, d_dst2, CV_GRAY2BGR, 0, stream2);

    cout<<"sucess"<<endl;
}

