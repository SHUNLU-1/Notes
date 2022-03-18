#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string>
using namespace std;
#include <opencv2/highgui/highgui_c.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
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
    pipe_config.enable_stream(RS2_STREAM_COLOR, 640, 480, RS2_FORMAT_BGR8, 30);

    rs2::pipeline_profile profile = pipe.start(pipe_config);
    const char *depth_win = "depth_Image";
    const char *color_win = "color_Image";
    namedWindow(depth_win, WINDOW_AUTOSIZE);
    namedWindow(color_win, WINDOW_AUTOSIZE);
    // while (waitKey(1) && getWindowProperty(depth_win, WND_PROP_AUTOSIZE))

    while (getWindowProperty(depth_win, WND_PROP_AUTOSIZE) && getWindowProperty(color_win, WND_PROP_AUTOSIZE))
    {
        rs2::frameset data = pipe.wait_for_frames(); //等待下一帧
        rs2::frame depth = data.get_depth_frame();
        rs2::frame depth_color = data.get_depth_frame().apply_filter(color);
        rs2::frame color = data.get_color_frame();

        const int depth_w = depth.as<rs2::video_frame>().get_width();
        const int depth_h = depth.as<rs2::video_frame>().get_height();
        const int color_w = depth.as<rs2::video_frame>().get_width();
        const int color_h = depth.as<rs2::video_frame>().get_height();

        Mat depth_image(Size(depth_w, depth_h), CV_8UC3, (void *)depth.get_data(), Mat::AUTO_STEP);
        Mat color_image(Size(color_w, color_h), CV_8UC3, (void *)color.get_data(), Mat::AUTO_STEP);
        Mat depth_color_image(Size(depth_w, depth_h), CV_8UC3, (void *)depth_color.get_data(), Mat::AUTO_STEP);

        imshow(depth_win, depth_image);
        imshow(color_win, color_image);
        imshow("depth_color_image", depth_color_image);
        waitKey(1);
    }
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

// #include <iostream>
// #include<stdlib.h>
// #include<stdio.h>
// #include<string>
// using namespace std;
// #include<opencv2/imgproc/imgproc.hpp>
// #include<opencv2/core/core.hpp>
// #include<opencv2/highgui/highgui.hpp>
// using namespace cv;

// #include<librealsense2/rs.hpp>

// int main() try
// {
//     //声明彩色图
//     rs2::colorizer color_map;

//     //声明realsense管道，
//     rs2::pipeline pipe;
//     //数据流配置信息【这步其实很重要】
//     rs2::config pipe_config;
//     pipe_config.enable_stream(RS2_STREAM_DEPTH,640,480,RS2_FORMAT_Z16,30);
//     pipe_config.enable_stream(RS2_STREAM_COLOR,640,480,RS2_FORMAT_BGR8,30);
//     //开始传送数据流
//     rs2::pipeline_profile profile=pipe.start(pipe_config);
//     const char* depth_win="depth_Image";
//     namedWindow(depth_win,WINDOW_AUTOSIZE);
//     const char* color_win="color_Image";
//     namedWindow(color_win,WINDOW_AUTOSIZE);

// //    //获取深度像素与长度单位的关系
// //    float depth_scale = get_depth_scale(profile.get_device());
// //    rs2_stream align_to = find_stream_to_align(profile.get_streams());

//     while(waitKey(1)&&getWindowProperty(depth_win, WND_PROP_AUTOSIZE)){
//         rs2::frameset data=pipe.wait_for_frames();//等待下一帧

//         rs2::frame depth=data.get_depth_frame().apply_filter(color_map);//获取深度图，加颜色滤镜
//         rs2::frame color=data.get_color_frame();

//         //获取宽高
//         const int depth_w=depth.as<rs2::video_frame>().get_width();
//         const int depth_h=depth.as<rs2::video_frame>().get_height();
//         const int color_w=color.as<rs2::video_frame>().get_width();
//         const int color_h=color.as<rs2::video_frame>().get_height();

//         //创建OPENCV类型 并传入数据
//         Mat depth_image(Size(depth_w,depth_h),CV_8UC3,(void*)depth.get_data(),Mat::AUTO_STEP);
//         Mat color_image(Size(color_w,color_h),CV_8UC3,(void*)color.get_data(),Mat::AUTO_STEP);
//         //显示
//         imshow(depth_win,depth_image);
//         imshow(color_win,color_image);
//     }
//     return EXIT_SUCCESS;
// }
// catch (const rs2::error &e){
//     std::cout<<"RealSense error calling"<<e.get_failed_function()<<"("<<e.get_failed_args()<<"):\n"
//             <<e.what()<<endl;
//     return EXIT_FAILURE;
// }
// catch (const std::exception &e){
//     std::cout<<e.what()<<endl;
//     return EXIT_FAILURE;

// }