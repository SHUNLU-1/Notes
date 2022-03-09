#include <stdio.h>
#include <iostream>
#include <opencv2/opencv.hpp>
#include"include.h"

using namespace cv;
using namespace std;

RNG random_number_generator_1;

void selectMax(int window, std::vector<KeyPoint>& kp) {
    /// window是局部极大值抑制的窗口大小，r为半径
    int r = window / 2;
    if (window != 0) {
        /// 对kp中的点进行局部极大值筛选
        for (int i = 0; i < kp.size(); i++) {
            for (int j = i + 1; j < kp.size(); j++) {
                /// 如果两个点的距离小于半径r，则删除其中响应值较小的点
                if (abs(kp[i].pt.x - kp[j].pt.x) + abs(kp[i].pt.y - kp[j].pt.y) <= 2 * r) {
                    if (kp[i].response < kp[j].response) {
                        std::vector<KeyPoint>::iterator it = kp.begin() + i;
                        kp.erase(it);
                        //selectMax(window, kp);
                    }
                    else {
                        std::vector<KeyPoint>::iterator it = kp.begin() + j;
                        kp.erase(it);
                        //selectMax(window, kp);
                    }
                }
            }
        }
    }
}
void Match(Mat img1,Mat img2)
{
    /// 定义写入txt的文件
    ofstream outfile("/home/guoheng/code/Match_1/out.txt", ios::trunc);

    cv::resize(img1,img1,Size(960,720));
    cv::resize(img2,img2,Size(960,720));

    Mat img1Gray, img2Gray;
    cvtColor(img1, img1Gray, COLOR_BGR2GRAY);
    cvtColor(img2, img2Gray, COLOR_BGR2GRAY);

    /// 初始化
    vector<KeyPoint> keypoints_1, keypoints_2;
    Mat description_1, description_2;

    Ptr<ORB> orb = ORB::create(500, 2.8f, 8, 31, 0, 2, ORB::HARRIS_SCORE, 31, 20);

    /// 第一步选择角点
    orb->detect(img1, keypoints_1);
    orb->detect(img2, keypoints_2);

    selectMax(50,keypoints_1);
    selectMax(50,keypoints_2);

    /// 第二步计算描述子
    orb->compute(img1, keypoints_1, description_1);
    orb->compute(img2, keypoints_2, description_2);

    /// 定义Point2f的存储容器
    vector<Point2f> orbpoints_1, orbpoints_2;

    /// 将keypoints格式转化成Point2f格式
    KeyPoint::convert(keypoints_1, orbpoints_1);
    KeyPoint::convert(keypoints_2, orbpoints_2);

    /// 指定亚像素计算迭代标注
    cv::TermCriteria criteria = cv::TermCriteria(
        cv::TermCriteria::MAX_ITER + cv::TermCriteria::EPS, 40, 0.01);

    /// 亚像素检测
    cv::cornerSubPix(img1Gray, orbpoints_1, cv::Size(5, 5), cv::Size(-1, -1), criteria);
    cv::cornerSubPix(img2Gray, orbpoints_2, cv::Size(5, 5), cv::Size(-1, -1), criteria);

    /// 显示找到的角点
    Mat outimg1, outimg2;
    drawKeypoints(img1, keypoints_1, outimg1, Scalar::all(-1), DrawMatchesFlags::DRAW_RICH_KEYPOINTS);
    drawKeypoints(img2, keypoints_2, outimg2, Scalar::all(-1), DrawMatchesFlags::DRAW_RICH_KEYPOINTS);

//    imshow("ORB特征点_1", outimg1);
//    imshow("ORB特征点_2", outimg2);
    /// 第三步对图像的描述子进行匹配
    vector<DMatch> matches;
    BFMatcher matcher(NORM_HAMMING);
    matcher.match(description_1, description_2, matches);

    /// 第四步对匹配点进行筛选
    double min_dist = 10000, max_dist = 0;
    /// 找出所有匹配中最小距离和最大距离
    for (int i = 0; i < description_1.rows; i++)
    {
        double dist = matches[i].distance;
        if (dist < min_dist) { min_dist = dist; }
        if (dist > max_dist) { max_dist = dist; }
    }
    cout << min_dist << "\t" << max_dist << endl;
    /// 当描述子之间的距离大于两倍的最小距离时，即认为匹配错误
    /// 但有时候最小距离会非常小，需要设置一个经验值作为下限
    vector<DMatch> good_match;
    for (int j = 0; j < description_1.rows; j++) {
//        if (matches[j].distance <= max(2 * min_dist, 10.0))
        {
            int dx = abs(keypoints_1[matches[j].queryIdx].pt.x - keypoints_2[matches[j].trainIdx].pt.x);
            int dy = abs(keypoints_1[matches[j].queryIdx].pt.y - keypoints_2[matches[j].trainIdx].pt.y);
            if ((dx < 0.05 * img1.cols) && (dy < 0.02 * img1.rows)) {
                circle(img1, orbpoints_1[matches[j].queryIdx], 20, Scalar(random_number_generator_1.uniform(0, 255), random_number_generator_1.uniform(0, 255), random_number_generator_1.uniform(0, 255)), 3, 8, 0);
                circle(img2, orbpoints_2[matches[j].trainIdx], 20, Scalar(random_number_generator_1.uniform(0, 255), random_number_generator_1.uniform(0, 255), random_number_generator_1.uniform(0, 255)), 3, 8, 0);
//                cv::putText(img1, std::to_string(j+1), cv::Point2f(orbpoints_1[matches[j].queryIdx].x,orbpoints_1[matches[j].queryIdx].y), cv::FONT_HERSHEY_COMPLEX, 0.7, cv::Scalar(0, 255, 0), 1);
//                cv::putText(img2, std::to_string(j+1), cv::Point2f(orbpoints_2[matches[j].queryIdx].x,orbpoints_2[matches[j].queryIdx].y), cv::FONT_HERSHEY_COMPLEX, 0.7, cv::Scalar(0, 255, 0), 1);

                /// 输出亚像素角点信息
                outfile << orbpoints_1[matches[j].queryIdx].x << " " << orbpoints_1[matches[j].queryIdx].y << " ";
                outfile << orbpoints_2[matches[j].trainIdx].x << " " << orbpoints_2[matches[j].trainIdx].y << endl;
                good_match.push_back(matches[j]);
            }
        }
    }

    for (auto j = 0; j < good_match.size(); j++) {

        cv::putText(img1, std::to_string(j), cv::Point2f(orbpoints_1[good_match[j].queryIdx].x,orbpoints_1[good_match[j].queryIdx].y), cv::FONT_HERSHEY_COMPLEX, 1.3, Scalar(random_number_generator_1.uniform(0, 255), random_number_generator_1.uniform(0, 255), random_number_generator_1.uniform(0, 255)), 1.5);
        cv::putText(img2, std::to_string(j+1), cv::Point2f(orbpoints_2[good_match[j].trainIdx].x,orbpoints_2[good_match[j].trainIdx].y), cv::FONT_HERSHEY_COMPLEX, 1.3, Scalar(random_number_generator_1.uniform(0, 255), random_number_generator_1.uniform(0, 255), random_number_generator_1.uniform(0, 255)), 1.5);
    }
    /// 第五步显示匹配结果

    Mat img_goodmatch;
    drawMatches(img1, keypoints_1, img2, keypoints_2, good_match, img_goodmatch);

    resize(img_goodmatch, img_goodmatch, Size(int(0.6 * img_goodmatch.cols), int(0.6 * img_goodmatch.rows)));
    cv::putText(img_goodmatch, "Number of matches :"+std::to_string (good_match.size()), cv::Point2f(10,400), cv::FONT_HERSHEY_COMPLEX, 0.7, cv::Scalar(0, 255, 0), 1);

    /// 计算
    Calculation();

    imshow("left", img1);
    imshow("right", img2);
    imshow("匹配", img_goodmatch);

    waitKey(0);
}



