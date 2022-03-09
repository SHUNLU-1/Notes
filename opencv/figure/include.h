#ifndef IMAGEPROCESS_H
#define IMAGEPROCESS_H
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <map>
#include <opencv2/dnn.hpp>
#include <opencv2/dnn/shape_utils.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv4/opencv2/opencv.hpp>
#include <string>

using namespace std;
using namespace cv;
using namespace cv::dnn;

extern cv::HOGDescriptor    _hog ;
extern cv::Ptr<cv::ml::SVM> _svm ;

void                 dnnn(Mat frame);
int                  calFighur(Mat Inputimg);

void                 prosess(Mat& finalImage, Mat _src);
int                  crossroads(Mat Inputimg);
Point2f              Discriminate_corss(Rect box, Mat frame);

#endif  // IMAGEPROCESS_H
