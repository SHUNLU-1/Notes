#include <iostream>
#include <Eigen/Dense>

using namespace Eigen;
using namespace std;
/*************高级初始化方法*****************/
/*
    逗号初始化
    Eigen提供了逗号操作符允许我们方便地为矩阵/向量/数组中的元素赋值。顺序是从左上到右下：
    自左到右，从上至下。对象的尺寸需要事先指定，初始化的参数也应该和要操作的元素数目一致。

    Matrix3f m;
    m << 1, 2, 3,
        4, 5, 6,
        7, 8, 9;
    std::cout << m;
*/
void a()
{
    /// 初始化列表不仅可以是数值也可以是vectors或matrix。
    RowVectorXd vec1(3);
    vec1 << 1, 2, 3;
    std::cout << "vec1 = " << vec1 << std::endl;
    RowVectorXd vec2(4);
    vec2 << 1, 4, 9, 16;
    std::cout << "vec2 = " << vec2 << std::endl;
    RowVectorXd joined(7);
    joined << vec1, vec2;
    std::cout << "joined = " << joined << std::endl;

    /// 也可以使用块结构。
    MatrixXf matA(2, 2);
    matA << 1, 2, 3, 4;
    MatrixXf matB(4, 4);
    matB << matA, matA / 10, matA / 10, matA;
    std::cout << matB << std::endl;

    /// 同时逗号初始化方式也可以用来为块表达式赋值。
    Matrix3f m;
    m.row(0) << 1, 2, 3;
    m.block(1, 0, 2, 2) << 4, 5, 7, 8;
    m.col(2).tail(2) << 6, 9;
    std::cout << m;
}
/// 特殊的矩阵和向量
void b()
{
    /// 零阵：类的静态成员函数Zero()，有三种定义形式。
    std::cout << "A fixed-size array:\n";
    Array33f a1 = Array33f::Zero();
    std::cout << a1 << "\n\n";
    std::cout << "A one-dimensional dynamic-size array:\n";
    ArrayXf a2 = ArrayXf::Zero(3);
    std::cout << a2 << "\n\n";
    std::cout << "A two-dimensional dynamic-size array:\n";
    ArrayXXf a3 = ArrayXXf::Zero(3, 4);
    std::cout << a3 << "\n";
    /// 类似地，还有常量矩阵：Constant([rows],[cols],value)，Random()随机矩阵。
    /// 单位阵Identity()方法只能使用与Matrix不使用Array，因为单位阵是个线性代数概念。
    /// LinSpaced(size, low, high)可以从low到high等间距的size长度的序列，适用于vector和一维数组。
    ArrayXXf table(10, 4);
    table.col(0) = ArrayXf::LinSpaced(10, 0, 90);
    table.col(1) = M_PI / 180 * table.col(0);
    table.col(2) = table.col(1).sin();
    table.col(3) = table.col(1).cos();
    std::cout << "      Degrees   Radians      Sine    Cosine\n";
    std::cout << table << std::endl;
    /// 功能函数
    /// Eigen也提供可同样功能的函数：setZero(),
    /// MatrixBase::setIdentity()和 DenseBase::setLinSpaced()。
    const int size = 6;
    MatrixXd mat1(size, size);
    mat1.topLeftCorner(size / 2, size / 2) = MatrixXd::Zero(size / 2, size / 2);
    mat1.topRightCorner(size / 2, size / 2) = MatrixXd::Identity(size / 2, size / 2);
    mat1.bottomLeftCorner(size / 2, size / 2) = MatrixXd::Identity(size / 2, size / 2);
    mat1.bottomRightCorner(size / 2, size / 2) = MatrixXd::Zero(size / 2, size / 2);
    std::cout << mat1 << std::endl
              << std::endl;
    MatrixXd mat2(size, size);
    mat2.topLeftCorner(size / 2, size / 2).setZero();
    mat2.topRightCorner(size / 2, size / 2).setIdentity();
    mat2.bottomLeftCorner(size / 2, size / 2).setIdentity();
    mat2.bottomRightCorner(size / 2, size / 2).setZero();
    std::cout << mat2 << std::endl
              << std::endl;
    MatrixXd mat3(size, size);
    mat3 << MatrixXd::Zero(size / 2, size / 2), MatrixXd::Identity(size / 2, size / 2),
        MatrixXd::Identity(size / 2, size / 2), MatrixXd::Zero(size / 2, size / 2);
    std::cout << mat3 << std::endl;
}
/************表达式变量************/
/*
    上面的静态方法如 Zero()、Constant()并不是直接返回一个矩阵或数组，
    实际上它们返回的是是‘expression object’，只是临时被使用/被用于优化。

    m = (m + MatrixXd::Constant(3,3,1.2)) * 50;
    MatrixXf::Constant(3,3,1.2)构建的是一个3*3的矩阵表达式（临时变量）。

    逗号初始化的方式也可以构建这种临时变量，这是为了获取真正的矩阵需要调用finished()函数：


*/
void c()
{
    MatrixXf mat = MatrixXf::Random(2, 3);
    std::cout << mat << std::endl
              << std::endl;
    mat = (MatrixXf(2, 2) << 0, 1, 1, 0).finished() * mat;
    std::cout << mat << std::endl;
}
int main()
{
    // a();
    // b();
    c();
}