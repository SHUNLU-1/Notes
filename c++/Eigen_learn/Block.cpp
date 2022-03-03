#include <iostream>
#include <Eigen/Dense>
using namespace Eigen;
using namespace std;
/*
    >>>块操作
    块是matrix或array中的矩形子部分。

    >>>使用块
    函数.block()，有两种形式
    -------------------------------------------------------------------
    |operation	          |构建一个动态尺寸的block	|构建一个固定尺寸的block|
    |起点(i,j)块大小(p,q)	|.block(i,j,p,q)	   |.block< p,q >(i,j)  |
    -------------------------------------------------------------------    
    Eigen中，索引从0开始。

    两个版本都可以用于固定尺寸和动态尺寸的matrix/array。功能是等价的，
    只是固定尺寸的版本在block较小时速度更快一些。

*/
void a()
{
    /// MatrixXf
    Eigen::MatrixXf m(4, 4);
    m << 1, 2, 3, 4,
        5, 6, 7, 8,
        9, 10, 11, 12,
        13, 14, 15, 16;
    cout << "Block in the middle" << endl;
    cout << m.block<2, 2>(1, 1) << endl
         << endl;
    for (int i = 1; i <= 4; ++i)
    {
        cout << "Block of size " << i << "x" << i << endl;
        cout << m.block(0, 0, i, i) << endl
             << endl;
    }
}
void a1()
{
    /// Array22f
    Array22f m;
    m << 1, 2,
        3, 4;
    Array44f a = Array44f::Constant(0.6);
    cout << "Here is the array a:" << endl
         << a << endl
         << endl;
    a.block<2, 2>(1, 1) = m;
    cout << "Here is now a with m copied into its central 2x2 block:" << endl
         << a << endl
         << endl;

    a.block(2, 1, 2, 3) = a.block(0, 0, 2, 3);

    // a.block(0, 0, 2, 3) = a.block(2, 1, 2, 3);
    cout << "Here is now a with bottom-right 2x3 block copied into top-left 2x2 block:" << endl
         << a << endl
         << endl;
}
///          行和列
/*  ----------------------------
    |Operation	| Method       |
    |ith row	| matrix.row(i)|
    |jth colum	| matrix.col(j)|
    ----------------------------*/
void b()
{
    Eigen::MatrixXf m(3, 3);
    m << 1, 2, 3,
        4, 5, 6,
        7, 8, 9;
    cout << "Here is the matrix m:" << endl
         << m << endl;
    cout << "2nd Row: " << m.row(1) << endl;
    m.col(2) += 3 * m.col(0);
    cout << "After adding 3 times the first column into the third column, the matrix m is:\n";
    cout << m << endl;
}
/*      角相关操作
------------------------------------------------------------------------------------
|  operation | dynamic-size block	         |  fixed-size block                   |
|  左上角p\*q |	matrix.topLeftCorner(p,q);	  |  matrix.topLeftCorner< p,q >();     |
|  左下角p\*q |	matrix.bottomLeftCorner(p,q); |	matrix.bottomLeftCorner< p,q >();   |
|  右上角p\*q |	matrix.topRightCorner(p,q);   |	matrix.topRightCorner< p,q >();     |
|  右下角p\*q |	matrix.bottomRightCorner(p,q);|	matrix.bottomRightCorner< p,q >();  |
|  前q行	  | matrix.topRows(q);	          |  matrix.topRows< q >();             |
|  后q行	  | matrix.bottomRows(q);	      |  matrix.bottomRows< q >();          |
|  左p列	  | matrix.leftCols(p);	          |  matrix.leftCols< p >();            |
|  右p列	  | matrix.rightCols(p);	      |  matrix.rightCols< p >();           |
------------------------------------------------------------------------------------
*/
void c()
{
    Eigen::Matrix4f m;
    m << 1, 2, 3, 4,
        5, 6, 7, 8,
        9, 10, 11, 12,
        13, 14, 15, 16;
    cout << "m.leftCols(2) =" << endl
         << m.leftCols(2) << endl
         << endl;
    cout << "m.bottomRows<2>() =" << endl
         << m.bottomRows<2>() << endl
         << endl;
    m.topLeftCorner(1, 3) = m.bottomRightCorner(3, 1).transpose();
    cout << "After assignment, m = " << endl
         << m << endl;
}
/*
           vectors的块操作
    --------------------------------------------------------------
    |operation	  |dynamic-size block	|fixed-size block        |
    |前n个	       |vector.head(n);	     |vector.head< n >();     |
    |后n个	       |vector.tail(n);	     |vector.tail< n >();     |
    |i起始的n个元素	|vector.segment(i,n); |vector.segment< n >(i);  |
    ---------------------------------------------------------------
*/
int main()
{
    // a();
    // a1();
    // b();
    c();
}