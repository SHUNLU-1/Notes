#include "include.h"
Point2f Discriminate_corss(Rect box, Mat frame)
{
    Mat ROI, ROI_1, gray, edge;
    ROI   = frame(box);
    ROI_1 = frame(box);

    cv::cvtColor(ROI, ROI, COLOR_BGR2GRAY);
    cv::threshold(ROI, ROI, 50, 255, THRESH_BINARY);

    //    cv::imshow("整图阈值", ROI);

    vector<Mat> splited;
    Mat         color, fincolor;
    cv::split(ROI_1, splited);
    cv::subtract(splited[2], splited[0], color);
    cv::threshold(color, color, 50, 255, THRESH_BINARY);

    gray = color & ROI;

    //    cv::imshow("red", color);
    //    cv::imshow("fincolor", gray);

    //    cvtColor(ROI, gray, COLOR_BGR2GRAY);
    //    threshold(gray, gray, 100, 255, THRESH_BINARY);
    //    imshow("gray", gray);

    Canny(gray, edge, 5, 9);
    vector<Vec2f> lines;
    HoughLines(edge, lines, 1, CV_PI / 180, 40, 0, 0);

    //    imshow("edge", edge);

    //下面这一段是画出所有不分组的霍夫变换得到的直线，用于测试

    for (size_t i = 0; i < lines.size(); i++)
    {
        float  rho = lines[i][0], theta = lines[i][1];
        Point  pt1, pt2;
        double a = cos(theta), b = sin(theta);
        Point  box_point = box.tl();
        double x0 = (a * rho) + box_point.x, y0 = (b * rho) + box_point.y;
        pt1.x = cvRound(x0 + 1000 * (-b));
        pt1.y = cvRound(y0 + 1000 * (a));
        pt2.x = cvRound(x0 - 1000 * (-b));
        pt2.y = cvRound(y0 - 1000 * (a));
        //        line(frame, pt1, pt2, Scalar(55, 100, 195), 1, LINE_AA);
    }

    vector<Vec2f> lines_mix, lines1, lines2;
    float         theta_min = 8;
    for (size_t i = 0; i < lines.size(); i++)
    {
        if (i == 0)
        {
            lines_mix.push_back(lines[i]);
        }
        else  //进行转角比较
        {
            for (size_t j = 0; j < lines_mix.size(); j++)
            {
                float theta_count = abs(lines[i][1] - lines_mix[j][1]);
                if (theta_count < (CV_PI / 2) + 0.4 && theta_count > (CV_PI / 2) - 0.4)  //可适当调整允许误差转角范围
                    lines1.push_back(lines[i]);
                else if (theta_count < (CV_PI * 3 / 2) + 0.4 && theta_count > (CV_PI * 3 / 2) - 0.4)  //可适当调整允许误差转角范围
                    lines1.push_back(lines[i]);
                else
                    lines2.push_back(lines[i]);
            }
        }
    }

    Vec4f           point_line1, point_line2;
    vector<Point2f> point1, point2;
    Point           point1_0, point1_1, point1_2;
    Point           point2_0, point2_1, point2_2;
    Point2i         crosspoint;  /// 交点坐标

    //第一线集的所有端点拟合直线对
    for (size_t i = 0; i < lines1.size(); i++)
    {
        float  rho = lines1[i][0], theta = lines1[i][1];
        Point  pt1, pt2;
        double a = cos(theta), b = sin(theta);
        Point  box_point = box.tl();
        double x0 = (a * rho) + box_point.x, y0 = (b * rho) + box_point.y;
        pt1.x = cvRound(x0 + 1000 * (-b));
        pt1.y = cvRound(y0 + 1000 * (a));
        pt2.x = cvRound(x0 - 1000 * (-b));
        pt2.y = cvRound(y0 - 1000 * (a));
        //        line(frame, pt1, pt2, Scalar(255, 255, 0), 1, LINE_AA);
        point1.push_back(pt1);
        point1.push_back(pt2);
    }
    if (point1.size() != 0)
    {
        fitLine(point1, point_line1, cv::DIST_L2, 0, 0.01, 0.01);
        point1_0.x = point_line1[2];
        point1_0.y = point_line1[3];
        point1_1.x = point1_0.x + 1000 * point_line1[0];
        point1_1.y = point1_0.y + 1000 * point_line1[1];
        point1_2.x = point1_0.x - 1000 * point_line1[0];
        point1_2.y = point1_0.y - 1000 * point_line1[1];
        //        line(frame, point1_1, point1_2, Scalar(0, 0, 255), 2, LINE_AA);
    }

    //对第二线集的所有端点拟合直线
    for (size_t i = 0; i < lines2.size(); i++)
    {
        float  rho = lines2[i][0], theta = lines2[i][1];
        Point  pt1, pt2;
        double a = cos(theta), b = sin(theta);
        Point  box_point = box.tl();
        double x0 = (a * rho) + box_point.x, y0 = (b * rho) + box_point.y;
        pt1.x = cvRound(x0 + 1000 * (-b));
        pt1.y = cvRound(y0 + 1000 * (a));
        pt2.x = cvRound(x0 - 1000 * (-b));
        pt2.y = cvRound(y0 - 1000 * (a));
        //        line(frame, pt1, pt2, Scalar(55, 100, 195), 1, LINE_AA);
        point2.push_back(pt1);
        point2.push_back(pt2);
    }
    if (point2.size() != 0)
    {
        fitLine(point2, point_line2, cv::DIST_L2, 0, 0.01, 0.01);
        point2_0.x       = point_line2[2];
        point2_0.y       = point_line2[3];
        point2_1.x       = point2_0.x + 1000 * point_line2[0];
        point2_1.y       = point2_0.y + 1000 * point_line2[1];
        point2_2.x       = point2_0.x - 1000 * point_line2[0];
        point2_2.y       = point2_0.y - 1000 * point_line2[1];
        double distance  = sqrt((point2_1.x - point2_2.x) * (point2_1.x - point2_2.x) + (point2_1.y - point2_2.y) * (point2_1.x - point2_2.y));
        double cos_thera = cos((abs(point2_1.y) / abs(distance)));
        cv::putText(frame, "cos_thera  = " + to_string(static_cast<int>(cos_thera)), Point2f(200, 75), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(165, 155, 238), 1);
        cv::putText(frame, "distance  = " + to_string(static_cast<int>(distance)), Point2f(200, 95), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(165, 155, 238), 1);
        cv::putText(frame, "point2_1.y  = " + to_string(static_cast<int>(point2_1.y)), Point2f(200, 115), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(165, 155, 238), 1);

        line(frame, point2_1, point2_2, Scalar(0, 0, 255), 2, LINE_AA);
    }
    if (point1.size() == 0 || point2.size() == 0)
    {
        //输出：该点识别不到两组直线数据
        cout << " \t>>这一帧识别不到两组相交的直线" << endl;
        box = box + Point(0, 0);
    }
    else
    {
        //计算两条红线的交点并输出交点坐标
        double ka, kb;
        ka = ( double )(point1_2.y - point1_1.y) / ( double )(point1_2.x - point1_1.x);
        kb = ( double )(point2_2.y - point2_1.y) / ( double )(point2_2.x - point2_1.x);

        crosspoint.x = (ka * point1_1.x - point1_1.y - kb * point2_1.x + point2_1.y) / (ka - kb);
        crosspoint.y = (ka * kb * (point1_1.x - point2_1.x) + ka * point2_1.y - kb * point1_1.y) / (ka - kb);
        circle(frame, crosspoint, 4, Scalar(0, 255, 0), -1, 8, 0);
        cout << " \t>>由直线求得的交点坐标(" << crosspoint.x << "," << crosspoint.y << ")" << endl;
    }
    imshow("video", frame);
    return crosspoint;
}
