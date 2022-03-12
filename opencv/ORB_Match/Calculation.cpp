#include <opencv2/opencv.hpp>
#include <fstream>
#include <iostream>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdio>
#include <iomanip>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <wchar.h>
//#include"include.h"

using namespace std;
using namespace cv;

///*左相机内参数矩阵
float leftIntrinsic[3][3] = { 1174.95492, 0, 1173.78210,
0, 1092.81704, 519.24697,
0, 0, 1 };

///*左相机畸变系数
float leftDistortion[1][5] = { 0.01511, -0.07082, -0.00404, -0.00577, 0.00000 };

///左相机旋转矩阵
float leftRotation[3][3] = { 1, 0, 0,
0, 1, 0,
0, 0, 1 };

///左相机平移向量
float leftTranslation[1][3] = { 0, 0, 0 };

///*右相机内参数矩阵
float rightIntrinsic[3][3] = { 1183.78326, 0, 1184.56450,
0, 1146.00981, 524.44355,
0, 0, 1 };

///*右相机畸变系数
float rightDistortion[1][5] = { -0.01510, 0.10386,-0.00263, -0.00270, 0.00000 };

///*右相机旋转矩阵
float rightRotation[3][3] = { 1.0000, 0.0004, -0.0061,
-0.0004, 1.0000, 0.0027,
0.0061, -0.0027, 1.0000 };

///右相机平移向量
float rightTranslation[1][3] = { -40.06365, 0.11260, -0.95004 };

#define M 50
#define N 4

Point2f xyz2uv(Point3f worldPoint, float intrinsic[3][3], float translation[1][3], float rotation[3][3]);

///************************************
/// Description: 坐标系的转化
///************************************
Point3f uv2xyz(Point2f uvLeft, Point2f uvRight)
{
    //  [u1]      |X|					  [u2]      |X|
    //Z*|v1| = Ml*|Y|					Z*|v2| = Mr*|Y|
    //  [ 1]      |Z|					  [ 1]      |Z|
    //			  |1|								|1|
    Mat mLeftRotation = Mat(3, 3, CV_32F, leftRotation);
    Mat mLeftTranslation = Mat(3, 1, CV_32F, leftTranslation);
    Mat mLeftRT = Mat(3, 4, CV_32F);
    hconcat(mLeftRotation, mLeftTranslation, mLeftRT);
    Mat mLeftIntrinsic = Mat(3, 3, CV_32F, leftIntrinsic);
    Mat mLeftM = mLeftIntrinsic * mLeftRT;
    //std::cout<<"mLeftM = "<<endl<<mLeftM<<endl;

    Mat mRightRotation = Mat(3, 3, CV_32F, rightRotation);
    Mat mRightTranslation = Mat(3, 1, CV_32F, rightTranslation);
    Mat mRightRT = Mat(3, 4, CV_32F);
    hconcat(mRightRotation, mRightTranslation, mRightRT);
    Mat mRightIntrinsic = Mat(3, 3, CV_32F, rightIntrinsic);
    Mat mRightM = mRightIntrinsic * mRightRT;
    //std::cout<<"mRightM = "<<endl<<mRightM<<endl;

    Mat A = Mat(4, 3, CV_32F);
    A.at<float>(0, 0) = uvLeft.x * mLeftM.at<float>(2, 0) - mLeftM.at<float>(0, 0);
    A.at<float>(0, 1) = uvLeft.x * mLeftM.at<float>(2, 1) - mLeftM.at<float>(0, 1);
    A.at<float>(0, 2) = uvLeft.x * mLeftM.at<float>(2, 2) - mLeftM.at<float>(0, 2);

    A.at<float>(1, 0) = uvLeft.y * mLeftM.at<float>(2, 0) - mLeftM.at<float>(1, 0);
    A.at<float>(1, 1) = uvLeft.y * mLeftM.at<float>(2, 1) - mLeftM.at<float>(1, 1);
    A.at<float>(1, 2) = uvLeft.y * mLeftM.at<float>(2, 2) - mLeftM.at<float>(1, 2);

    A.at<float>(2, 0) = uvRight.x * mRightM.at<float>(2, 0) - mRightM.at<float>(0, 0);
    A.at<float>(2, 1) = uvRight.x * mRightM.at<float>(2, 1) - mRightM.at<float>(0, 1);
    A.at<float>(2, 2) = uvRight.x * mRightM.at<float>(2, 2) - mRightM.at<float>(0, 2);

    A.at<float>(3, 0) = uvRight.y * mRightM.at<float>(2, 0) - mRightM.at<float>(1, 0);
    A.at<float>(3, 1) = uvRight.y * mRightM.at<float>(2, 1) - mRightM.at<float>(1, 1);
    A.at<float>(3, 2) = uvRight.y * mRightM.at<float>(2, 2) - mRightM.at<float>(1, 2);

    Mat B = Mat(4, 1, CV_32F);
    B.at<float>(0, 0) = mLeftM.at<float>(0, 3) - uvLeft.x * mLeftM.at<float>(2, 3);
    B.at<float>(1, 0) = mLeftM.at<float>(1, 3) - uvLeft.y * mLeftM.at<float>(2, 3);
    B.at<float>(2, 0) = mRightM.at<float>(0, 3) - uvRight.x * mRightM.at<float>(2, 3);
    B.at<float>(3, 0) = mRightM.at<float>(1, 3) - uvRight.y * mRightM.at<float>(2, 3);

    Mat XYZ = Mat(3, 1, CV_32F);
    solve(A, B, XYZ, DECOMP_SVD);
    //std::cout<<"XYZ = "<<endl<<XYZ<<endl;

    Point3f world;
    world.x = XYZ.at<float>(0, 0);
    world.y = XYZ.at<float>(1, 0);
    world.z = XYZ.at<float>(2, 0);

    return world;
}

void Calculation()
{
    int i, j, x;
    float a[M][N] = { 0 };
    FILE *fp1;

    if ((fp1 = fopen("/home/guoheng/code/Match_1/out.txt", "rt")) == nullptr)
    {
        printf("cannot open file\n");
        return ;
    }
    double start_time = getTickCount();
    for (i = 0; i<M; i++)
    {
        for (j = 0; j<N; j++)
            fscanf(fp1, "%f", &a[i][j]);
        fscanf(fp1, "\n");
    }
    fclose(fp1);
    for (x = 0; x < 17; x++) /// x<M
    {
        /// 左右相机图像坐标系的点
        Point2f l = { static_cast<float>(a[x][0])
            , static_cast<float>(a[x][1])
        };
        Point2f r = { static_cast<float>(a[x][2])
            , static_cast<float>(a[x][3])
        };

        /// 图像坐标系转化到世界坐标系
        Point3f worldPoint;
        worldPoint = uv2xyz(l, r);

        /// 最终保存文件路径
        FILE *fp2;
        fp2 = fopen("/home/guoheng/code/Match_1/result.txt", "a");
        fprintf(fp2, "\n(%g):\t%g\t%g\t%g",static_cast<float>(x), worldPoint.x, worldPoint.y, worldPoint.z);
        fclose(fp2);
        cout << "worldPoint:=" << endl << uv2xyz(l, r) << endl;
    }
    double end_time = getTickCount();
    cout << "The run time is:" << (end_time - start_time) << "ms!" << endl;
    system("pause");
    return ;
}


