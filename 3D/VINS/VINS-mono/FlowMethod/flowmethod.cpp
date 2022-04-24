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

typedef float DTYPE_FD;
typedef unsigned char DTYPE;

//获取图像高斯金字塔
void build_gauss_Pyramid_cuda(Mat src, DTYPE *gauss_Pyramid, int num)
{
    memcpy(gauss_Pyramid, (DTYPE *)src.data, src.rows * src.cols * sizeof(DTYPE)); //先把第0层的原图拷贝进去
    Mat currentMat = src.clone();
    int len_x = src.cols;
    int len_y = src.rows;
    int img_size = src.rows * src.cols;
    int offset = 0;
    for (int i = 0; i < num; i++)
    {
        Mat nextLayer;
        offset += img_size;
        img_size >>= 2;
        len_x >>= 1;
        len_y >>= 1;
        pyrDown(currentMat, nextLayer, Size(len_x, len_y));
        memcpy(gauss_Pyramid + offset, (DTYPE *)nextLayer.data, img_size * sizeof(DTYPE));
        currentMat = nextLayer.clone();
    }
}

//分别计算单帧图像的x，y方向的梯度
void cal_gradient(DTYPE *src, int row, int col, DTYPE_FD *Fx, DTYPE_FD *Fy)
{
    int index;
    //计算x方向的首列和尾列梯度, i = 0~row-1, j = 0, col-1
    for (int i = 0; i < row; i++)
    {
        index = i * col;
        Fx[index] = (DTYPE_FD)(src[index + 1] - src[index]);                           //首列
        Fx[index + col - 1] = (DTYPE_FD)(src[index + col - 1] - src[index + col - 2]); //尾列
    }

    //计算y方向的首行和尾行梯度, i = 0, row-1, j = 0~col-1
    for (int j = 0; j < col; j++)
    {
        Fy[j] = (DTYPE_FD)(src[col + j] - src[j]); //首行
        index = (row - 1) * col;
        Fy[index + j] = (DTYPE_FD)(src[index + j] - src[index - col + j]); //尾行
    }

    for (int i = 1; i < row - 1; i++)
    {
        for (int j = 1; j < col - 1; j++)
        {
            index = i * col + j;
            Fx[index] = (src[index + 1] - src[index - 1]) / 2.0;
            Fy[index] = (src[index + col] - src[index - col]) / 2.0;
        }
    }
}

//获取图像高斯金字塔的梯度,row和col为原图尺寸
void cal_gauss_Pyramid_gradient_cuda(DTYPE *gauss_Pyramid, int row, int col, DTYPE_FD *Fx, DTYPE_FD *Fy, int num)
{
    cal_gradient(gauss_Pyramid, row, col, Fx, Fy); //计算第0层的梯度，Fx和Fy也是金字塔，是多层图像的梯度
    int len_x = col;
    int len_y = row;
    int img_size = len_x * len_y;
    int offset = 0;
    for (int i = 0; i < num; i++)
    {
        offset += img_size;
        img_size >>= 2;
        len_x >>= 1;
        len_y >>= 1;
        cal_gradient(gauss_Pyramid + offset, len_y, len_x, Fx + offset, Fy + offset); // Fx和Fy也是金字塔，是多层图像的梯度
    }
}

//计算前后帧的高斯金字塔的差值
void cal_diff(DTYPE *pre_gauss_Pyramid, DTYPE *cur_gauss_Pyramid, int length, DTYPE_FD *diff)
{
    for (int i = 0; i < length; i++)
    {
        diff[i] = (DTYPE_FD)(pre_gauss_Pyramid[i] - cur_gauss_Pyramid[i]);
    }
}
//row*col为原图尺寸
//加上原图(第0层)，有num+1层金字塔
//获取高斯金字塔所占的一维内存大小，单位字节byte
int get_gauss_Pyramid_memory_len(int row, int col, int num)
{
	int data_len = 0;
	//int len_x = col;
	//int len_y = row;
	int img_size = row*col;
	for (int i = 0; i <= num; i++)   //从第0层开始，共num+1层，每向上一层，宽和高都缩小1/2
	{
		data_len += img_size;
		img_size >>= 2;
	}
 
	data_len *= sizeof(DTYPE);
 
	return data_len;
}
vector<Point2f> lk_track_ori1(Mat preFrame, Mat curFrame, vector<Point2f> keyPoints, vector<uchar> &status, int maxPyramidLayer, int maxIteration, int winsize, DTYPE_FD opticalflowResidual)
{

    status.clear();

    int gaussian_len = get_gauss_Pyramid_memory_len(preFrame.rows, preFrame.cols, maxPyramidLayer); //总共maxPyramidLayer+1层
    DTYPE *pre_gauss_Pyramid_memory = (DTYPE *)malloc(gaussian_len);
    DTYPE *cur_gauss_Pyramid_memory = (DTYPE *)malloc(gaussian_len);
    DTYPE_FD *cur_Fx = (DTYPE_FD *)malloc(gaussian_len / sizeof(DTYPE) * sizeof(DTYPE_FD));
    DTYPE_FD *cur_Fy = (DTYPE_FD *)malloc(gaussian_len / sizeof(DTYPE) * sizeof(DTYPE_FD));
    DTYPE_FD *diff = (DTYPE_FD *)malloc(gaussian_len / sizeof(DTYPE) * sizeof(DTYPE_FD));

    build_gauss_Pyramid_cuda(preFrame, pre_gauss_Pyramid_memory, maxPyramidLayer); //计算图像金字塔
    build_gauss_Pyramid_cuda(curFrame, cur_gauss_Pyramid_memory, maxPyramidLayer);
    cal_gauss_Pyramid_gradient_cuda(cur_gauss_Pyramid_memory, curFrame.rows, curFrame.cols, cur_Fx, cur_Fy, maxPyramidLayer);

    cal_diff(pre_gauss_Pyramid_memory, cur_gauss_Pyramid_memory, gaussian_len / sizeof(DTYPE), diff);

    vector<Point2f> tPoints;
    int width, height;
    DTYPE_FD delta[2];

    const int winsize_2_1 = 2 * winsize + 1;
    const int img_size = preFrame.rows * preFrame.cols;

    DTYPE_FD *dd = (DTYPE_FD *)malloc(winsize_2_1 * winsize_2_1 * sizeof(DTYPE_FD));
    float coeff[16];

    const DTYPE_FD maxPyramidLayer_coeff = (float)(1. / (1 << maxPyramidLayer));

    for (unsigned int i = 0; i < keyPoints.size(); i++)
    {
        DTYPE_FD g[2] = {0};
        bool isValid = true;

        float prePoint_x; //最顶层的初始跟踪点
        float prePoint_y;
        prePoint_x = keyPoints[i].x * maxPyramidLayer_coeff;
        prePoint_y = keyPoints[i].y * maxPyramidLayer_coeff;

        for (int j = maxPyramidLayer; j >= 0; j--)
        {

            // int offset = get_gauss_Pyramid_memory_offset_size(preFrame.rows, preFrame.cols, j); //, height, width);
            int offset = (j > 0) ? ((int)(img_size * (4 - 1.0 / (1 << (2 * j - 2))) / 3.0)) : 0;
            height = preFrame.rows >> j; // row/pow(2.0, index);
            width = preFrame.cols >> j;  // col/pow(2.0, index);

            DTYPE_FD *fx = &cur_Fx[offset];
            DTYPE_FD *fy = &cur_Fy[offset];
            DTYPE_FD *d = &diff[offset];

            DTYPE_FD x, y, curX, curY, ix, iy;
            for (int t1 = -winsize; t1 <= winsize; t1++) // row
            {
                for (int t2 = -winsize; t2 <= winsize; t2++) // col
                {
                    x = prePoint_x + t2;
                    y = prePoint_y + t1;

                    int floorRow = floor(y); //δI=A(x,y)-B(x,y)，而不是δI=A(x,y)-B(x+Δx,y+Δy)，所以这样做会更准确一点
                    int floorCol = floor(x);
                    //双线性插值
                    int ceilRow = floorRow + 1;
                    int ceilCol = floorCol + 1;

                    if (floorCol >= 0 && floorCol < width - 1 && floorRow >= 0 && floorRow < height - 1)
                    {
                        DTYPE_FD fracRow = y - floorRow;
                        DTYPE_FD fracCol = x - floorCol;

                        float k0 = 1.0 - fracRow;
                        float k1 = 1.0 - fracCol;

                        dd[(t1 + winsize) * (2 * winsize + 1) + t2 + winsize] = (k0 * k1 * d[floorRow * width + floorCol] + fracRow * k1 * d[ceilRow * width + floorCol] + k0 * fracCol * d[floorRow * width + ceilCol] + fracRow * fracCol * d[ceilRow * width + ceilCol]);
                    }
                    else
                    {
                        dd[(t1 + winsize) * (2 * winsize + 1) + t2 + winsize] = 0;
                    }
                }
            }

            DTYPE_FD v[2] = {0}; //[x y]
            int iterCount = 0;
            DTYPE_FD residual;

            while (iterCount < maxIteration) //迭代计算剩余光流
            {
                iterCount++;

                DTYPE_FD G[4] = {0}; //[Ix*Ix, Ix*Iy, Ix*Iy, Iy*Iy]
                DTYPE_FD b[2] = {0}; //[x y]

                for (int t1 = -winsize; t1 <= winsize; t1++) // row
                {
                    for (int t2 = -winsize; t2 <= winsize; t2++) // col
                    {
                        x = prePoint_x + t2;
                        y = prePoint_y + t1;

                        curX = x + g[0] + v[0]; //这里需注意：后一帧图像的点坐标是变化的
                        curY = y + g[1] + v[1];

                        // 插值 //

                        int floorRow = floor(curY);
                        int floorCol = floor(curX);

                        if (floorCol >= 0 && floorCol < width - 1 && floorRow >= 0 && floorRow < height - 1)
                        {
                            int ceilRow = floorRow + 1;
                            int ceilCol = floorCol + 1;

                            DTYPE_FD fracRow = curY - floorRow;
                            DTYPE_FD fracCol = curX - floorCol;

                            DTYPE_FD k0 = 1.0 - fracRow;
                            DTYPE_FD k1 = 1.0 - fracCol;
                            DTYPE_FD a0 = k0 * k1;
                            DTYPE_FD a1 = fracRow * k1;
                            DTYPE_FD a2 = k0 * fracCol;
                            DTYPE_FD a3 = fracRow * fracCol;

                            int idx0 = floorRow * width + floorCol;
                            int idx1 = ceilRow * width + floorCol;
                            int idx2 = floorRow * width + ceilCol;
                            int idx3 = ceilRow * width + ceilCol;

                            ix = a0 * fx[idx0] + a1 * fx[idx1] + a2 * fx[idx2] + a3 * fx[idx3];
                            iy = a0 * fy[idx0] + a1 * fy[idx1] + a2 * fy[idx2] + a3 * fy[idx3];
                        }
                        else
                        {
                            ix = 0;
                            iy = 0;
                        }

                        G[0] += ix * ix; //计算G
                        G[1] += ix * iy;
                        G[3] += iy * iy;

                        int idx = (t1 + winsize) * winsize_2_1 + t2 + winsize;
                        b[0] += dd[idx] * ix; //计算b
                        b[1] += dd[idx] * iy;
                    }
                }
                G[2] = G[1];

                DTYPE_FD abs_G = 1.f / (G[0] * G[3] - G[1] * G[2]); //求矩阵的行列式的倒数

                delta[0] = (G[3] * b[0] - G[2] * b[1]) * abs_G;
                delta[1] = (-G[1] * b[0] + G[0] * b[1]) * abs_G;

                v[0] += delta[0];
                v[1] += delta[1];

                residual = delta[0] * delta[0] + delta[1] * delta[1];

                if (residual <= opticalflowResidual * opticalflowResidual)
                    break;
            }

            if (iterCount >= maxIteration)
            {
                isValid = false;
                break;
            }

            if (j == 0)
            {
                g[0] += v[0]; //最终光流
                g[1] += v[1];
            }
            else
            {
                g[0] = 2 * (g[0] + v[0]); //金字塔中间层光流
                g[1] = 2 * (g[1] + v[1]);
            }

            prePoint_x = prePoint_x * 2.f; //下一层的初始跟踪点，迭代的时候已经加上了猜测光流，所以此处不需要再加了
            prePoint_y = prePoint_y * 2.f;
        }

        Point2f dstPoint(keyPoints[i].x + g[0], keyPoints[i].y + g[1]); //得到跟踪点
        tPoints.push_back(dstPoint);

        if (isValid && dstPoint.x >= 0 && dstPoint.x < curFrame.cols && dstPoint.y >= 0 && dstPoint.y < curFrame.rows)
        {
            status.push_back(1);
        }
        else
        {
            status.push_back(0);
        }
    }

    free(pre_gauss_Pyramid_memory);
    free(cur_gauss_Pyramid_memory);
    free(cur_Fx);
    free(cur_Fy);
    free(diff);
    free(dd);
    return tPoints;
}

int main()
{
    return 0;
}