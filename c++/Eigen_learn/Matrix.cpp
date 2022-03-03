#include <iostream>
#include <Eigen/Dense>

// using namespace Eigen::MatrixXd;
using namespace Eigen;
using namespace std;
/// 认知 Eigen
void Cognition()
{
    MatrixXd m(2, 2);
    m(0, 0) = 3;
    m(1, 0) = 2.5;
    m(0, 1) = -1;

    m(1, 1) = m(1, 0) + m(0, 1);
    std::cout << m << std::endl;
}
/// 矩阵和向量
void a()
{
    /// 创建一个 3*3 随机化矩阵
    MatrixXd m = MatrixXd::Random(3, 3);
    /// 创建一个 3*3 的常量矩阵
    MatrixXd M = MatrixXd::Constant(3, 3, 1.2);
    MatrixXd Mm = (m + MatrixXd::Constant(3, 3, 1.2)) * 50;
    std::cout << "m =" << std::endl
              << m << std::endl;
    std::cout << "M =" << std::endl
              << M << std::endl;
    std::cout << "Mm =" << std::endl
              << Mm << std::endl;
    /// 创建一维三列的向量
    Eigen::VectorXd v(3);
    v << 1, 2, 3;
    std::cout << "m * v =" << std::endl
              << m * v << std::endl;
}
/// 在Eigen，所有的矩阵和向量都是Matrix模板类的对象，Vector只是一种特殊的矩阵（一行或者一列）。
/// 获取元素
void b()
{
    MatrixXd m(2, 2);
    m(0, 0) = 3;
    m(1, 0) = 2.5;
    m(0, 1) = -1;
    m(1, 1) = m(1, 0) + m(0, 1);
    std::cout << "Here is the matrix m:\n"
              << m << std::endl;
    VectorXd v(2);
    v(0) = 4;
    v(1) = v(0) - 1;
    std::cout << "Here is the vector v:\n"
              << v << std::endl;
}
/// resize
void c()
{
    MatrixXd m(2, 5);
    m.resize(4, 3);
    std::cout << "The matrix m is of size "
              << m.rows() << "x" << m.cols() << std::endl;
    std::cout << "It has " << m.size() << " coefficients" << std::endl;
    VectorXd v(2);
    v.resize(5);
    std::cout << "The vector v is of size " << v.size() << std::endl;
    std::cout << "As a matrix, v is of size "
              << v.rows() << "x" << v.cols() << std::endl;

    MatrixXf a(2, 2);
    std::cout << "a is of size " << a.rows() << "x" << a.cols() << std::endl;
    MatrixXf b(3, 3);
    a = b;
    std::cout << "a is now of size " << a.rows() << "x" << a.cols() << std::endl;
    std::cout << "b is now of size " << b.rows() << "x" << b.cols() << std::endl;
}
/// 矩阵和向量的运算
/// 加减
void d()
{
    Matrix2d a;
    a << 1, 2,
        3, 4;
    MatrixXd b(2, 2);
    b << 2, 3,
        1, 4;
    std::cout << "a + b =\n"
              << a + b << std::endl;
    std::cout << "a - b =\n"
              << a - b << std::endl;
    std::cout << "Doing a += b;" << std::endl;
    a += b;
    std::cout << "Now a =\n"
              << a << std::endl;
    Vector3d v(1, 2, 3);
    Vector3d w(1, 0, 0);
    std::cout << "-v + w - v =\n"
              << -v + w - v << std::endl;
}
/// 乘除
void d1()
{
    Matrix2d a;
    a << 1, 2,
        3, 4;
    Vector3d v(1, 2, 3);
    std::cout << "a * 2.5 =\n"
              << a * 2.5 << std::endl;
    std::cout << "0.1 * v =\n"
              << 0.1 * v << std::endl;
    std::cout << "Doing v *= 2;" << std::endl;
    v *= 2;
    std::cout << "Now v =\n"
              << v << std::endl;
}
/// 转置和共轭
void e()
{
    /*img 表示transpose转置
    img 表示conjugate共轭
    img 表示adjoint(共轭转置) 伴随矩阵
    */
    Matrix2d a;
    a << 1, 2,
        3, 4;
    // MatrixXcf a = MatrixXcf::Random(2, 2);
    cout << "Here is the matrix a\n"
         << a << endl;
    cout << "Here is the matrix a^T\n"
         << a.transpose() << endl;
    cout << "Here is the conjugate of a\n"
         << a.conjugate() << endl;
    cout << "Here is the matrix a^*\n"
         << a.adjoint() << endl;
    /// 对 a=a.transpose() 这种操作，可以执行in-palce转置。类似还有adjointInPlace。
    MatrixXf b(2, 3);
    b << 1, 2, 3, 4, 5, 6;
    cout << "Here is the initial matrix a:\n"
         << b << endl;
    b.transposeInPlace();
    cout << "and after being transposed:\n"
         << b << endl;
}
/// 矩阵-矩阵的乘法和矩阵-向量的乘法
void e1()
{
    Matrix2d mat;
    mat << 1, 2,
        3, 4;
    Vector2d u(-1, 1), v(2, 0);
    std::cout << "Here is mat*mat:\n"
              << mat * mat << std::endl;
    std::cout << "Here is mat*u:\n"
              << mat * u << std::endl;
    std::cout << "Here is u^T*mat:\n"
              << u.transpose() * mat << std::endl;
    std::cout << "Here is u^T*v:\n"
              << u.transpose() * v << std::endl;
    std::cout << "Here is u*v^T:\n"
              << u * v.transpose() << std::endl;
    std::cout << "Let's multiply mat by itself" << std::endl;
    mat = mat * mat;
    std::cout << "Now mat is mat:\n"
              << mat << std::endl;
}
/// 点运算和叉运算
void e2()
{
    Vector3d v(1, 2, 3);
    Vector3d w(0, 1, 2);
    cout << "Dot product: " << v.dot(w) << endl;
    double dp = v.adjoint() * w; // automatic conversion of the inner product to a scalar
    cout << "Dot product via a matrix product: " << dp << endl;
    cout << "Cross product:\n"
         << v.cross(w) << endl;
}
/// 基础的归约操作
///Eigen提供了而一些归约函数：sum()、prod()、maxCoeff()和minCoeff()，他们对所有元素进行操作。
void f()
{
    Eigen::Matrix2d mat;
    mat << 1, 2,
        3, 4;
    /// 每个元素的和
    cout << "Here is mat.sum():       " << mat.sum() << endl;
    /// 每个元素相乘的积
    cout << "Here is mat.prod():      " << mat.prod() << endl;
    /// 每个元素之和的平均值
    cout << "Here is mat.mean():      " << mat.mean() << endl;
    /// 返回最小的元素
    cout << "Here is mat.minCoeff():  " << mat.minCoeff() << endl;
    /// 返回最大的元素
    cout << "Here is mat.maxCoeff():  " << mat.maxCoeff() << endl;
    /// trace表示矩阵的迹，对角元素的和等价于 a.diagonal().sum()
    /// 在线性代数中，一个n×n矩阵A的主对角线（从左上方至右下方的对角线）上各个元素的总和被称为矩阵A的迹（或迹数），一般记作tr(A)。
    cout << "Here is mat.trace():     " << mat.trace() << endl;
    // Matrix3f m;
    // Vector3f v;
    // v = m * v; // Compile-time error: YOU_MIXED_MATRICES_OF_DIFFERENT_SIZES
    MatrixXf m(3, 3);
    VectorXf v(4);
    v = m * v; // Run-time assertion failure here: "invalid matrix product"
}
int main()
{
    // Cognition();
    // a();
    // b();
    // c();
    // d();
    // d1();
    // e();
    // e1();
    // e2();
    f();
}
