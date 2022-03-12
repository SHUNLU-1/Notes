#include"include.h"
int main()
{
    /// 两张图片路径
    cv::Mat src_img1 = cv::imread("/home/guoheng/code/Match_1/left1.JPG");
    cv::Mat src_img2 = cv::imread("/home/guoheng/code/Match_1/right1.JPG");


    /// 单张图片寻找角点 (外加滑动条控制角点个数)
    // FindCorner(src_img1);

    /// 两张图片匹配
    Match(src_img1,src_img2);

    return 0;
}
