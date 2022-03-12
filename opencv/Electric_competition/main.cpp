#include "include.h"
#include "serial.h"
cv::HOGDescriptor    _hog ;
cv::Ptr<cv::ml::SVM> _svm ;

int main()
{

    //    VideoCapture cap("/home/guoheng/code/figure/1.avi");
    VideoCapture cap(0);
    if (!cap.isOpened())  // 如果视频不能正常打开则返回
    {
        cout << "Vdieo open fail" << endl;
        return -1;
    }
    Mat frame;
    Mat Gray, ThreImage;

    _hog = cv::HOGDescriptor(cv::Size(48, 48), cv::Size(8, 8), cv::Size(4, 4), cv::Size(4, 4), 9);
    _svm = cv::ml::SVM::load("/home/guoheng/code/figure/svm/svm_1.xml");

    //-----------------开始初始化串口--------------
    Uart              InfoPort;   //声明串口
    HostComputerData  RobotInfo;  //发送数据
    GroundChassisData MainControlInfo;
    int               num        = 0;
    int               fd_serial0 = 0;
    InfoPort.Init_serial(fd_serial0, 115200);  //串口初始化

    bool FirstFind           = true;   ///<判断是不是识别到第一个数字
    int  FirstFigure         = 1;      ///<初始识别数字
    int  crossroad_frame     = 0;      ///<记录进入路口帧数
    bool crossroad_sign      = false;  ///<路口标志位
    int  Intersection_number = 0;      ///<表示此时为第几个路口
    while (1)
    {
        cap >> frame;
        if (frame.empty())  // 如果某帧为空则退出循环
            break;
        //比赛刚开始、识别记录数据
        InfoPort.GetMode(fd_serial0, MainControlInfo);

        if (FirstFind == true)
        {
            Mat src, dst, img, dst1, frame_rect, frame_number;

            Rect2d rect_test(180, 100, 80, 60);

            rectangle(frame, rect_test, Scalar(100, 255, 255), 2, 8);
            frame_rect = frame(rect_test);

            imshow("frame_rect", frame_rect);

            cv::cvtColor(frame_rect, src, COLOR_BGR2GRAY);
            cv::threshold(src, dst, 130, 255, THRESH_BINARY /*| THRESH_OTSU*/);  // 100
                                                                                 //            cv::equalizeHist(dst, dst);
            //            cvtColor(frame, src, COLOR_BGR2HSV);
            //            inRange(src, Scalar(0, 0, 0), Scalar(180, 255, 46), img);
            //            imshow("img", img);
            Mat element = getStructuringElement(MORPH_ELLIPSE, Size(5, 5));
            dilate(dst, dst, element);
            //            fillHole(dst, dst);
            imshow("dst", dst);

            vector<Vec4i>         Vec;       //轮廓层次结构
            vector<vector<Point>> contours;  //识别到的轮廓
            findContours(dst, contours, Vec, RETR_TREE, CHAIN_APPROX_SIMPLE, Point());
            Rect         rect;
            vector<Rect> rects;
            for (size_t i = 0; i < contours.size(); i++)
            {

                RotatedRect Rects = minAreaRect(contours[i]);

                int rect_area = rect.height * rect.width;
                rect          = cv::boundingRect(contours[i]);

                if (rect_area > 20000)
                    continue;

                if (rect_area < 5000)
                    continue;

                //                for (size_t j = 0; j < contours[i].size(); j++)
                //                {
                //                    contours[i][j].x += 180;
                //                    contours[i][j].y += 100;
                //                }
                rects.push_back(rect);
            }

            //            for (int i = 0; i < rects.size(); i++)
            //            {
            //                rectangle(frame, rects[i], Scalar(0, 255, 255), 2, 8);
            //                frame_number = frame_rect(rects[i]);
            //                imshow("frame_number", frame_number);
            //            }
            //            drawContours(frame, contours, -1, Scalar(0, 255, 0), 2);  // 绘制轮廓：-1代表绘制所有轮廓

            //            int frame_number_1 = 0;

            //            for (int save_number = 30; save_number < 60; save_number++)
            //            {
            //                if (frame_number_1 % 500 == 0)
            //                {
            //                    string img_Name = "/home/cheng/code/figure/figure/picture1/1/" + to_string(save_number) + ".jpg";
            //                    imwrite(img_Name, frame_rect);
            //                }
            //            }
            //            frame_number_1++;

            //            vector<int> number_FirstFigure;
            //            if (number_FirstFigure.size() < 300)
            //            {
            //                FirstFigure = calFighur(frame_rect);  ///< 记录识别到的数字
            //                number_FirstFigure.push_back(FirstFigure);
            //                cout << "FirstFigure" << FirstFigure << endl;
            //            }
            //            else
            //            {
            //                // map的key存放数组中的数字，value存放该数字出现的次数
            //                map<int, int>* map_number = new map<int, int>();
            //                for (auto i = number_FirstFigure.begin(); i < number_FirstFigure.end(); i++)
            //                {
            //                    if (map_number.containsKey(array[i]))
            //                    {
            //                        int formerValue = map_number.get(array[i]);
            //                        map_number.put(array[i], formerValue + 1);  // 该数字出现的次数加1
            //                    }
            //                    else
            //                    {
            //                        map_number.put(array[i], 1);  // 该数字第一次出现
            //                    }
            //                }
            //                Collection<Integer> count = map.values();
            //                // 找出map的value中最大值，也就是数组中出现最多的数字所出现的次数
            //                int maxCount  = Collections.max(count);
            //                int maxNumber = 0;
            //                for (Map.Entry<Integer, Integer> entry : map.entrySet())
            //                {
            //                    //得到value为maxCount的key，也就是数组中出现次数最多的数字
            //                    if (entry.getValue() == maxCount)
            //                    {
            //                        maxNumber = entry.getKey();
            //                    }
            //                }

            //                for (auto i = number_FirstFigure.begin(); i < number_FirstFigure.end(); i++)
            //                {
            //                    vector<int> temp_number;
            //                    if (i)
            //                        temp_number.begin();
            //                    for (int j = i; j < (number_FirstFigure.size() - 1); j++)
            //                    {
            //                    }
            //                }
            //            }

            FirstFigure = calFighur(frame_rect);  ///< 记录识别到的数字
            cout << "FirstFigure" << FirstFigure << endl;

            RobotInfo.Number = FirstFigure;

            //            if (FirstFigure == 1 || FirstFigure == 2)
            //            {
            //                RobotInfo.Number = FirstFigure;
            //                InfoPort.TransformTarPos(fd_serial0, RobotInfo);  //发送数据
            //            }
            if (FirstFigure != 0)
            {
                FirstFind = false;
            }
        }
        // 表示可以开始进行匹配
        if (FirstFind == false)
        {
            cv::Mat m_roi = frame(cv::Rect(200, 0, 220, 480));
            prosess(ThreImage, m_roi);

            vector<Vec4i>         Vec;       //轮廓层次结构
            vector<vector<Point>> contours;  //识别到的轮廓
            findContours(ThreImage, contours, Vec, RETR_TREE, CHAIN_APPROX_SIMPLE, Point());
            vector<RotatedRect> rect_all;
            Point2f             corssload_center;  //交点中心
            Rect                rect;              // 红线的正矩形
            Point2i             left(1000, 0), right(0, 0);
            for (size_t i = 0; i < contours.size(); i++)
            {
                RotatedRect Rects = minAreaRect(contours[i]);

                float RectAngle = Rects.angle;
                /// 轮廓右移
                for (size_t j = 0; j < contours[i].size(); j++)
                {
                    contours[i][j].x += 200;
                }
                for (const auto& contour : contours[i])
                {
                    if (contour.x < left.x && contour.y > left.y)
                        left = contour;
                    if (contour.x > right.x && contour.y > right.y)
                        right = contour;
                }
                float long_axis  = max(Rects.size.width, Rects.size.height);
                float short_axis = min(Rects.size.width, Rects.size.height);
                float areas      = long_axis * short_axis;

                if (areas < 800)
                    continue;

                rect            = cv::boundingRect(contours[i]);
                float area_rect = rect.width * rect.height;

                if (rect.height < 120)
                {
                    continue;
                }
                if (area_rect < 1200)
                {
                    continue;
                }

                /// 画出最小正矩形框

                //                rectangle(frame, rect, Scalar(0, 255, 255), 2, 8);

                /// 画出最小旋转矩形
                Point2f Rects_four_corners[4];
                Rects.points(Rects_four_corners);

                //                for (size_t k = 0; k < 4; k++)
                //                {
                //                    Rects_four_corners[k].x += 200;
                //                    line(frame, Rects_four_corners[k], Rects_four_corners[(k + 1) % 4], Scalar(255, 255, 0), 1, 8);
                //                    putText(frame, to_string(k), Rects_four_corners[k], 1, 1, Scalar(255, 255, 0));
                //                }

                float long_rect_1  = max(rect.width, rect.height);
                float short_rect_1 = min(rect.width, rect.height);
                cv::putText(frame, "rect.widht  = " + to_string(static_cast<int>(short_rect_1)), Point2f(10, 75), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(165, 155, 238), 1);
                cv::putText(frame, "rect.height = " + to_string(static_cast<int>(long_rect_1)), Point2f(10, 95), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(165, 155, 238), 1);

                /// 如果最小正矩形的宽度大于200 进入十字中心拟合
                if (short_rect_1 > 200)
                {
                    corssload_center = Discriminate_corss(rect, frame);
                }
            }
            /// 进入十字路口 计数帧数增加
            if (corssload_center.x > 0 && corssload_center.y > 0 && crossroad_frame < 1000)
            {
                crossroad_sign = true;
                crossroad_frame++;
            }
            else
            {
                crossroad_sign  = false;
                crossroad_frame = 0;
            }
            cv::putText(frame, "crossroad_frame  = " + to_string(static_cast<int>(crossroad_frame)), Point2f(10, 115), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(165, 155, 238), 1);
            cv::putText(frame, "crossroad_sign  = " + to_string(static_cast<int>(crossroad_sign)), Point2f(10, 135), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(165, 155, 238), 1);
            cv::putText(frame, "Intersection_number  = " + to_string(static_cast<int>(Intersection_number)), Point2f(10, 155), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(165, 155, 238), 1);

            circle(frame, corssload_center, 10, (255, 0, 0), 3);

            Rect2d rect_test(300, 220, 40, 40);
            Rect2d rect_test_1(300, 140, 40, 40);

            rectangle(frame, rect_test, Scalar(100, 255, 255), 2, 8);
            rectangle(frame, rect_test_1, Scalar(100, 255, 255), 2, 8);

            ///< 已经进入到十字路口
            if (crossroad_frame > 10)
            {
                /// 判别路口
                if (Intersection_number == 0 && crossroad_sign == true)
                {
                    /// 第一个路口右转
                    if (FirstFigure == 1)
                    {
                        RobotInfo.Turn = 1;
                        if ((crossroad_frame / 200) > 1)
                        {
                            Intersection_number++;
                            crossroad_sign = false;
                        }
                    }

                    /// 第一个路口左
                    if (FirstFigure == 2)
                    {
                        RobotInfo.Turn = 0;
                        if ((crossroad_frame / 200) > 1)
                        {
                            Intersection_number++;
                            crossroad_sign = false;
                        }
                    }
                }
                ///< 此时为第二个路口
                else if (Intersection_number == 1 && crossroad_sign == true)
                {

                    if (corssload_center.x < 340 && corssload_center.x > 300 && corssload_center.y > 220 && corssload_center.y < 260)
                    {
                        //第二个路口的两个ROI区域

                        cv::Mat m2_roi_1 = frame(cv::Rect(int(corssload_center.x + 20), corssload_center.y - 5, 140, 125));

                        cv::Mat m2_roi_2 = frame(cv::Rect(int(corssload_center.x - 160), corssload_center.y - 5, 140, 125));

                        //                            cv::Mat m2_roi_1 = frame(cv::Rect(int(CrossCenter.x + 15), CrossCenter.y-5, 188, 180));

                        //                            cv::Mat m2_roi_2 = frame(cv::Rect(int(CrossCenter.x - 208), CrossCenter.y-5, 188, 180));

                        int    m2_roi_2_center_x = m2_roi_1.rows / 2;
                        Rect2d rect_test_roi_1   = cv::Rect(int(corssload_center.x + 20), corssload_center.y - 5, 140, 125);
                        Rect2d rect_test_roi_2   = cv::Rect(int(corssload_center.x - 160), corssload_center.y - 5, 140, 125);

                        rectangle(frame, rect_test_roi_1, Scalar(0, 0, 255), 2, 8);
                        rectangle(frame, rect_test_roi_2, Scalar(0, 255, 0), 2, 8);

                        //        int frame_number = 0;
                        //        if (frame_number % 20 == 0)
                        //        {
                        //            for (int save_number = 0; save_number < 10; save_number++)
                        //            {
                        //                save_number++;
                        //                string img_Name = "/home/cheng/code/figure/figure/picture/1/" + to_string(save_number) + ".jpg";
                        //                imwrite(img_Name, frame);
                        //            }
                        //        }
                        //        frame_number++;

                        imshow("m2_roi_1", m2_roi_1);
                        imshow("m2_roi_2", m2_roi_2);

                        ///< 识别到的数字
                        int Temp_Number_01 = calFighur(m2_roi_1);
                        cout << "Temp_Number_01===" << Temp_Number_01 << endl;
                        int Temp_Number_02 = calFighur(m2_roi_2);
                        cout << "Temp_Number_02===" << Temp_Number_02 << endl;
                        if (Temp_Number_01 == FirstFigure)
                        {
                            RobotInfo.Turn = 1;
                            if ((crossroad_frame / 200) > 1)
                            {
                                Intersection_number++;
                                crossroad_sign = false;
                            }
                        }
                        else if (Temp_Number_02 == FirstFigure)
                        {
                            RobotInfo.Turn = 0;
                            if ((crossroad_frame / 200) > 1)
                            {
                                Intersection_number++;
                                crossroad_sign = false;
                            }
                        }
                        else
                        {

                            if ((crossroad_frame / 200) > 1)
                            {
                                Intersection_number++;
                                crossroad_sign = false;
                            }
                        }
                    }
                }
                ///< 此时为第三个路口
                else if (Intersection_number = 2 && crossroad_sign == true)
                {
                    if (corssload_center.x < 340 && corssload_center.x > 300 && corssload_center.y > 140 && corssload_center.y < 180)
                    {
                        //第三个路口的四个ROI区域
                        cv::Mat m3_roi_1 = frame(cv::Rect(int(corssload_center.x + 15), corssload_center.y + 10, 120, 110));

                        cv::Mat m3_roi_2 = frame(cv::Rect(int(corssload_center.x + 170), corssload_center.y + 10, 120, 110));

                        cv::Mat m3_roi_3 = frame(cv::Rect(int(corssload_center.x - 150), corssload_center.y + 10, 120, 110));

                        cv::Mat m3_roi_4 = frame(cv::Rect(int(corssload_center.x - 290), corssload_center.y + 10, 120, 110));

                        Rect2d rect_test_roi_1 = cv::Rect(int(corssload_center.x + 15), corssload_center.y + 10, 120, 110);
                        Rect2d rect_test_roi_2 = cv::Rect(int(corssload_center.x + 170), corssload_center.y + 10, 120, 110);
                        Rect2d rect_test_roi_3 = cv::Rect(int(corssload_center.x - 150), corssload_center.y + 10, 120, 110);
                        Rect2d rect_test_roi_4 = cv::Rect(int(corssload_center.x - 290), corssload_center.y + 10, 120, 110);

                        rectangle(frame, rect_test_roi_1, Scalar(0, 0, 255), 2, 8);
                        rectangle(frame, rect_test_roi_3, Scalar(255, 0, 0), 2, 8);

                        rectangle(frame, rect_test_roi_2, Scalar(0, 255, 0), 2, 8);
                        rectangle(frame, rect_test_roi_4, Scalar(100, 255, 255), 2, 8);

                        imshow("m3_roi_4", m3_roi_4);
                        imshow("m3_roi_3", m3_roi_3);
                        imshow("m3_roi_2", m3_roi_2);
                        imshow("m3_roi_1", m3_roi_1);

                        ///< 识别到的数字
                        int Temp_Number_01 = calFighur(m3_roi_1);
                        cout << "Temp_Number_01===" << Temp_Number_01 << endl;
                        int Temp_Number_02 = calFighur(m3_roi_2);
                        cout << "Temp_Number_02===" << Temp_Number_02 << endl;
                        int Temp_Number_03 = calFighur(m3_roi_3);
                        cout << "Temp_Number_03===" << Temp_Number_03 << endl;
                        int Temp_Number_04 = calFighur(m3_roi_4);
                        cout << "Temp_Number_04===" << Temp_Number_04 << endl;

                        if (Temp_Number_01 == FirstFigure)
                        {  //第二个路口右转
                            RobotInfo.Turn = 1;
                            if ((crossroad_frame / 200) > 1)
                            {
                                Intersection_number++;
                                crossroad_sign = false;
                            }
                        }

                        else if (Temp_Number_02 == FirstFigure)
                        {  //第二个路口左转
                            RobotInfo.Turn = 1;
                            if ((crossroad_frame / 200) > 1)
                            {
                                Intersection_number++;
                                crossroad_sign = false;
                            }
                        }
                        else if (Temp_Number_03 == FirstFigure)
                        {  //第二个路口左转
                            RobotInfo.Turn = 0;
                            if ((crossroad_frame / 200) > 1)
                            {
                                Intersection_number++;
                                crossroad_sign = false;
                            }
                        }
                        else if (Temp_Number_04 == FirstFigure)
                        {  //第二个路口左转
                            RobotInfo.Turn = 0;
                            if ((crossroad_frame / 200) > 1)
                            {
                                Intersection_number++;
                                crossroad_sign = false;
                            }
                        }
                        else
                        {
                            if ((crossroad_frame / 200) > 1)
                            {
                                Intersection_number++;
                                crossroad_sign = false;
                            }
                        }
                    }
                }
                ///< 此时为第四个路口
                else if (Intersection_number == 3)
                {
                    if (corssload_center.x < 340 && corssload_center.x > 300 && corssload_center.y > 220 && corssload_center.y < 260)
                    {

                        cv::Mat m4_roi_1 = frame(cv::Rect(int(corssload_center.x + 20), corssload_center.y - 5, 140, 125));
                        cv::Mat m4_roi_2 = frame(cv::Rect(int(corssload_center.x - 160), corssload_center.y - 5, 140, 125));

                        imshow("m3_roi_2", m4_roi_2);
                        imshow("m3_roi_1", m4_roi_1);

                        ///< 识别到的数字
                        int Temp_Number_01 = calFighur(m4_roi_1);
                        cout << "Temp_Number_01===" << Temp_Number_01 << endl;
                        int Temp_Number_02 = calFighur(m4_roi_2);
                        cout << "Temp_Number_02===" << Temp_Number_02 << endl;
                        if (Temp_Number_01 == FirstFigure)
                        {  //第二个路口右转
                            RobotInfo.Turn = 1;
                            if ((crossroad_frame / 200) > 1)
                            {
                                Intersection_number++;
                                crossroad_sign = false;
                            }
                        }
                        else if (Temp_Number_02 == FirstFigure)
                        {  //第二个路口左转
                            RobotInfo.Turn = 0;
                            if ((crossroad_frame / 200) > 1)
                            {
                                Intersection_number++;
                                crossroad_sign = false;
                            }
                        }
                        else
                        {
                            if ((crossroad_frame / 200) > 1)
                            {
                                Intersection_number++;
                                crossroad_sign = false;
                            }
                        }
                    }
                }
            }

            else
            {
                std::cout << "还没有到十字路口" << std::endl;
            }
            drawContours(frame, contours, -1, Scalar(0, 255, 0), 2);  // 绘制轮廓：-1代表绘制所有轮廓
        }
        // 此时还没有识别到第一章数字
        else
        {
            std::cout << "Not Find The First Figure" << endl;
        }

        RobotInfo.Turn      = 20;
        RobotInfo.Direction = 10;
        InfoPort.TransformTarPos(fd_serial0, RobotInfo);  //发送数据

        imshow("frame", frame);
        waitKey(30);
    }
    return 0;
}





