#include"init.h"
///<    直方图测试
bool Histogram(const cv::Mat image)
{
    // 转换为单通道的灰度图像
    cv::Mat grayImage;
    cv::cvtColor(image, grayImage, cv::COLOR_BGR2GRAY);

    cv::imshow("image", image);

    cv::threshold(grayImage, grayImage, 10, 255, cv::THRESH_BINARY);

    cv::imshow("grayImage", grayImage);

    // 直方图均衡化
    cv::Mat resultImage;
    cv::equalizeHist(grayImage, resultImage);

    // 显示原始图像及经过直方图均衡化的图像
    cv::imshow("Result image", resultImage);

    cv::waitKey(0);
    return true;
}
