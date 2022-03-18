#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string>

#include <fstream>
#include <iomanip>

using namespace std;
#include <opencv2/highgui/highgui_c.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc_c.h>
using namespace cv;
#include <librealsense2/rs.hpp>
int main()
try
{
    // 声明彩色图
    rs2::colorizer color;

    //
    rs2::pipeline pipe;
    rs2::config pipe_config;
    pipe_config.enable_stream(RS2_STREAM_DEPTH, 640, 480, RS2_FORMAT_Z16, 30);
    pipe_config.enable_stream(RS2_STREAM_COLOR, 640, 480, RS2_FORMAT_BGR8, 30); // rgb

    rs2::pipeline_profile profile = pipe.start(pipe_config);
    const char *depth_win = "depth_Image";
    const char *color_win = "color_Image";
    namedWindow(depth_win, WINDOW_AUTOSIZE);
    namedWindow(color_win, WINDOW_AUTOSIZE);

    int frame_num = 0;

    ofstream out_txt_file;
    out_txt_file.open("./0.9.txt", ios::out | ios::trunc);
    out_txt_file << fixed;

    while (getWindowProperty(depth_win, WND_PROP_AUTOSIZE) /*&& getWindowProperty(color_win, WND_PROP_AUTOSIZE)*/)
    {
        rs2::frameset data = pipe.wait_for_frames(); //等待下一帧
        rs2::depth_frame depth_ = data.get_depth_frame();
        rs2::frame color = data.get_color_frame();

        // rs2::frame depth = data.get_depth_frame();
        // rs2::frame depth_color = data.get_depth_frame().apply_filter(color);

        const int depth_w = depth_.as<rs2::video_frame>().get_width();
        const int depth_h = depth_.as<rs2::video_frame>().get_height();
        const int color_w = color.as<rs2::video_frame>().get_width();
        const int color_h = color.as<rs2::video_frame>().get_height();

        // 获取图像中心的深度 get_distance(获取某一特定像素点的深度)
        // Query the distance from the camera to the object in the center of the image
        // float dist_to_center = depth_.get_distance(depth_w / 2, depth_h / 2);

        Mat depth_image(Size(depth_w, depth_h), CV_8UC3, (void *)depth_.get_data(), Mat::AUTO_STEP);
        Mat color_image(Size(color_w, color_h), CV_8UC3, (void *)color.get_data(), Mat::AUTO_STEP);
        // Mat depth_color_image(Size(depth_w, depth_h), CV_8UC3, (void *)depth_color.get_data(), Mat::AUTO_STEP);

        cv::circle(color_image, Point2f(depth_w / 2, depth_h / 2), 2, cv::Scalar(0, 255, 255));

        cv::Rect2d rect_dist = Rect2d(Point2f((depth_image.cols / 2) - 20, (depth_image.rows / 2) - 20), Point2f((depth_image.cols / 2) + 20, (depth_image.rows / 2) + 20));
        cv::rectangle(color_image, rect_dist, cv::Scalar(0, 255, 255));

        cv::circle(color_image, Point2f(rect_dist.br().x, rect_dist.br().y), 2, cv::Scalar(0, 255, 255));
        
        if (frame_num < 100)
        {
            cout << "开始记录第" << frame_num << "次数据" << endl;
            for (int i = rect_dist.tl().x; i < rect_dist.height + rect_dist.tl().x; i++)
            {
                for (int j = rect_dist.tl().y; j < rect_dist.width + rect_dist.tl().y; j++)
                {
                    float dist_to_center = depth_.get_distance(i, j);
                    // if ((waitKey(1) == 32))
                    // {
                    out_txt_file << dist_to_center << endl;
                    cout << "第(" << i << "," << j << ")的深度值" << dist_to_center << endl;
                    // }
                }
            }
        }
        
        // float dist_to_center = depth_.get_distance(depth_w / 2, depth_h / 2);
        // cv::putText(color_image, "dist_to_center" + to_string(dist_to_center), Point2f(depth_w / 2, depth_h / 2), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 0, 255), 1, 1, false);

        // imshow(depth_win, depth_image);
        // imshow(color_win, color_image);
        // imshow("depth_color_image", depth_color_image);
        frame_num++;
        waitKey(1);
    }
    
    out_txt_file.close();
    return EXIT_SUCCESS;
}
catch (const rs2::error &e)
{
    std::cerr << "RealSense error calling " << e.get_failed_function() << "(" << e.get_failed_args() << "):\n    " << e.what() << std::endl;
    return EXIT_FAILURE;
}
catch (const std::exception &e)
{
    std::cerr << e.what() << std::endl;
    return EXIT_FAILURE;
}