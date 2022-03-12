#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui_c.h>
#include <iostream>

using namespace cv;
using namespace std;

int max_corners = 20;
int max_count = 100;//50
Mat src_img,gray_img;
const string output_winName = "Subpixel Point Detection";
/// 定义一个随机数发生器
RNG random_number_generator;
void SubPixel_Demo(int, void *);

void FindCorner(cv::Mat srcimg)
{
    src_img = srcimg.clone();

    if (src_img.empty())
    {
        printf("could not load the image...\n");
        return ;
    }
    namedWindow("source image", CV_WINDOW_AUTOSIZE);
    cv::Mat src_resized;
    cv::resize(src_img, src_resized, cv::Size(1024, 768));
    imshow("source image", src_resized);
    cvtColor(src_img, gray_img, COLOR_BGR2GRAY);
    namedWindow(output_winName, CV_WINDOW_AUTOSIZE);
    // 创建TrackBar
    createTrackbar("conner point count", output_winName, &max_corners, max_count, SubPixel_Demo);
    SubPixel_Demo(0, 0);

    waitKey(0);
    return ;
}

void SubPixel_Demo(int, void *)
{
    if (max_corners < 5)
    {
        /// 控制下限
        max_corners = 5;
    }
    /// corners是一个Vector，里面存放找到的角点坐标，即float的Point值
    vector<Point2f> corners;
    /// 检测到的角点的质量水平（通常是0.10到0.01之间的数值，不能大于1.0）。
    double qualityLevel = 0.1;// 0.01
    /// 角点距离
    double minDistance = 50;//10
    int blockSize = 3;
    double k = 0.04;
    cout << "************************************************************" << endl;

    /// 调用goodFeaturesToTrack进行shi-Tomasi角点检测
    /// 用于指定角点检测的方法，如果是true则使用Harris角点检测，false则使用Shi Tomasi算法。
//    goodFeaturesToTrack(gray_img, corners, max_corners, qualityLevel, minDistance, Mat(), blockSize, false, k);
    goodFeaturesToTrack(gray_img, corners, max_corners, qualityLevel, minDistance, Mat(), blockSize, true, k);

    cout << "conner count: " << corners.size() << endl;
    Mat result_img = src_img.clone();
    int font_face = cv::FONT_HERSHEY_COMPLEX;
    double font_scale = 0.7;
    int thickness = 2;
    int baseline;

//    for (auto t = 0; t < corners.size(); ++t)
//    {
//        circle(result_img, corners[t], 20,
//            Scalar(random_number_generator.uniform(0, 255), random_number_generator.uniform(0, 255), random_number_generator.uniform(0, 255)),
//            10, 8, 0); //   注意corners[t]就是一个Point类型的坐标
//        cv::Size text_size = cv::getTextSize(std::to_string(1), font_face, font_scale, thickness, &baseline);
//        cv::Point2f point(corners[t].x-20+ int(text_size.width/2),corners[t].y+20-int(text_size.height/2));
//        //cv::Point2f point(corners[t].x - 20, corners[t].y + 20);
//        cv::putText(result_img, std::to_string(t+1), point, font_face, font_scale, cv::Scalar(0, 255, 0), thickness);
//    }

    /// 参数设置
    Size winSize = Size(5, 5);
    Size zerozone = Size(-1, -1);
    TermCriteria criteria = TermCriteria(TermCriteria::EPS + TermCriteria::MAX_ITER, 40, 0.001);

    /// 调用cornerSubPix函数计算出亚像素角点的位置
    cornerSubPix(gray_img, corners, winSize, zerozone, criteria);

    /// 输出亚像素角点信息
    for (auto t = 0; t < corners.size(); ++t)
    {
        cout << "Precise angular coordinates[" << t + 1 << "]"
             << " point[x, y] = " << corners[t].x << " , " << corners[t].y << endl;
        circle(result_img, corners[t], 20,
            Scalar(random_number_generator.uniform(0, 255), random_number_generator.uniform(0, 255), random_number_generator.uniform(0, 255)),
            10, 8, 0); //   注意corners[t]就是一个Point类型的坐标
        cv::Size text_size = cv::getTextSize(std::to_string(1), font_face, font_scale, thickness, &baseline);
        cv::Point2f point(corners[t].x-20+ int(text_size.width/2),corners[t].y+20-int(text_size.height/2));
        cv::putText(result_img, std::to_string(t+1), point, font_face, font_scale, cv::Scalar(0, 255, 0), thickness);
    }
    cv::Mat resized_img;
    cv::resize(result_img, resized_img, cv::Size(1024, 768));
    cv::imshow(output_winName, resized_img);
}
