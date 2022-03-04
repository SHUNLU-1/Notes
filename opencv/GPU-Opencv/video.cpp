#include "init.h"
///< 读取视频测试
enum Method
{
    MOG,
    MOG2,
};

void video()
{
    Method m = MOG;

    int count = cuda::getCudaEnabledDeviceCount();
    printf("GPU Device Count : %d \n", count);

    VideoCapture cap;
    cap.open("/home/ubuntu/code/GPU-Opencv/files/energy.mp4");

    Mat frame;
    cap >> frame;

    GpuMat d_frame(frame);

    Ptr<BackgroundSubtractor> mog = cuda::createBackgroundSubtractorMOG();
    Ptr<BackgroundSubtractor> mog2 = cuda::createBackgroundSubtractorMOG2();

    GpuMat d_fgmask;
    GpuMat d_fgimg;
    GpuMat d_bgimg;

    Mat fgmask;
    Mat fgimg;
    Mat bgimg;

    switch (m)
    {
    case MOG:
        mog->apply(d_frame, d_fgmask, 0.01);
        break;

    case MOG2:
        mog2->apply(d_frame, d_fgmask);
        break;
    }

    namedWindow("image", WINDOW_AUTOSIZE);
    namedWindow("foreground mask", WINDOW_AUTOSIZE);
    namedWindow("foreground image", WINDOW_AUTOSIZE);
    namedWindow("mean background image", WINDOW_AUTOSIZE);

    for (;;)
    {
        cap >> frame;
        if (frame.empty())
            break;
        int64 start = cv::getTickCount();
        d_frame.upload(frame);


        //update the model
        switch (m)
        {
        case MOG:
            mog->apply(d_frame, d_fgmask, 0.01);
            mog->getBackgroundImage(d_bgimg);
            break;

        case MOG2:
            mog2->apply(d_frame, d_fgmask);
            mog2->getBackgroundImage(d_bgimg);
            break;
        }


        d_fgimg.create(d_frame.size(), d_frame.type());
        d_fgimg.setTo(Scalar::all(0));
        d_frame.copyTo(d_fgimg, d_fgmask);

        d_fgmask.download(fgmask);
        d_fgimg.download(fgimg);
        if (!d_bgimg.empty())
            d_bgimg.download(bgimg);

        imshow("foreground mask", fgmask);
        imshow("foreground image", fgimg);
        if (!bgimg.empty())
            imshow("mean background image", bgimg);

        double fps = cv::getTickFrequency() / (cv::getTickCount() - start);
        std::cout << "FPS : " << fps << std::endl;
        putText(frame, format("FPS : %.2f", fps), Point(50, 50), FONT_HERSHEY_SIMPLEX, 1.0, Scalar(0, 0, 255), 2, 8);

        imshow("image", frame);
        char key = (char)waitKey(1);
        if (key == 27)
            break;
    }
//    VideoCapture capture;
//    Mat frame;
//    frame= capture.open("/home/ubuntu/code/GPU-Opencv/files/energy.mp4");
//    if(!capture.isOpened())
//    {
//        printf("can not open ...\n");
//        return ;
//    }
//    namedWindow("output", 1);

//    while (capture.read(frame))
//    {
//        int64 start = cv::getTickCount();

//        imshow("output", frame);
//        double fps = cv::getTickFrequency() / (cv::getTickCount() - start);
//        std::cout << "FPS : " << fps << std::endl;
//        putText(frame, format("FPS : %.2f", fps), Point(50, 50), FONT_HERSHEY_SIMPLEX, 1.0, Scalar(255, 0, 255), 2, 8);

//        waitKey(10);

//    }
//    capture.release();
}
