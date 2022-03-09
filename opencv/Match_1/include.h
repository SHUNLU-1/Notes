#ifndef INCLUDE_H
#define INCLUDE_H
#include <stdio.h>
#include <iostream>
#include <opencv2/opencv.hpp>

//std::string Subpixel_Corner;

//std::string World_Points;
///// 存放亚像素角点信息的文件
//std::string Subpixel_Corner = "/home/guoheng/code/Match_1/out.txt";
///// 存放世界坐标系点的文件
//std::string World_Points = "/home/guoheng/code/Match_1/result.txt";

void Calculation();
void FindCorner(cv::Mat src_img);
void Match(cv::Mat img1,cv::Mat img2);
#endif // INCLUDE_H
