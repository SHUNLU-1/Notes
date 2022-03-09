#include "include.h"

/**
 * @brief 填充空洞、防止灯光过亮导致灯条出现空洞现象
 */
static void fillHole(Mat srcBw, Mat& dstBw)
{
    Mat broedMat = Mat::zeros(srcBw.rows + 2, srcBw.cols + 2, CV_8UC1);
    srcBw.copyTo(broedMat(Range(1, srcBw.rows + 1), Range(1, srcBw.cols + 1)));
    floodFill(broedMat, Point(0, 0), Scalar(255));
    Mat cutMat;
    broedMat(Range(1, srcBw.rows + 1), Range(1, srcBw.cols + 1)).copyTo(cutMat);
    dstBw = srcBw | (~cutMat);
}
void prosess(Mat& finalImage, Mat _src)
{
    Mat thres_whole;

    cv::cvtColor(_src, thres_whole, COLOR_BGR2GRAY);
    cv::threshold(thres_whole, thres_whole, 50, 255, THRESH_BINARY);

    //    cv::imshow("整图阈值", thres_whole);

    vector<Mat> splited;
    Mat         color, fincolor;
    cv::split(_src, splited);
    cv::subtract(splited[2], splited[0], color);
    cv::threshold(color, color, 50, 255, THRESH_BINARY);

    finalImage = color & thres_whole;
    //    cv::imshow("red", color);
    //    cv::imshow("fincolor", finalImage);
}


