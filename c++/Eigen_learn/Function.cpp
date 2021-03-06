#include <iostream>
#include "Eigen/Dense"

using namespace Eigen;
using namespace std;
/*****************归约、迭代器和广播*************************/
/// 归约
/// 在Eigen中，有些函数可以统计matrix/array的某类特征，返回一个标量。
void a()
{
    Eigen::Matrix2d mat;
    mat << 1, 2,
        3, 4;
    cout << "Here is mat.sum():       " << mat.sum() << endl;
    cout << "Here is mat.prod():      " << mat.prod() << endl;
    cout << "Here is mat.mean():      " << mat.mean() << endl;
    cout << "Here is mat.minCoeff():  " << mat.minCoeff() << endl;
    cout << "Here is mat.maxCoeff():  " << mat.maxCoeff() << endl;
    cout << "Here is mat.trace():     " << mat.trace() << endl;
}
// 范数计算
// L2范数 squareNorm()，等价于计算vector的自身点积，norm()返回squareNorm的开方根。
// 这些操作应用于matrix，norm() 会返回Frobenius或Hilbert-Schmidt范数。
// 如果你想使用其他Lp范数，可以使用lpNorm< p >()方法。p可以取Infinity，表示L∞范数。
void b()
{
    VectorXf v(2);
    MatrixXf m(2, 2), n(2, 2);

    v << -1,
        2;

    m << 1, -2,
        -3, 4;
    ///  L2范数 squareNorm()，等价于计算vector的自身点积
    cout << "v.squaredNorm() = " << v.squaredNorm() << endl;
    ///  norm()返回squareNorm的开方根。
    ///  这些操作应用于matrix，norm() 会返回Frobenius或Hilbert-Schmidt范数。
    cout << "v.norm() = " << v.norm() << endl;
    ///  如果你想使用其他Lp范数，可以使用lpNorm< p >()方法。p可以取Infinity，表示L∞范数
    cout << "v.lpNorm<1>() = " << v.lpNorm<1>() << endl;
    cout << "v.lpNorm<Infinity>() = " << v.lpNorm<Infinity>() << endl;
    cout << endl;
    cout << "m.squaredNorm() = " << m.squaredNorm() << endl;
    cout << "m.norm() = " << m.norm() << endl;
    cout << "m.lpNorm<1>() = " << m.lpNorm<1>() << endl;
    cout << "m.lpNorm<Infinity>() = " << m.lpNorm<Infinity>() << endl;

    ///  Operator norm: 1-norm和∞-norm可以通过其他方式得到。
    cout << "1-norm(m)     = " << m.cwiseAbs().colwise().sum().maxCoeff()
         << " == " << m.colwise().lpNorm<1>().maxCoeff() << endl;
    cout << "infty-norm(m) = " << m.cwiseAbs().rowwise().sum().maxCoeff()
         << " == " << m.rowwise().lpNorm<1>().maxCoeff() << endl;
}
/// 布尔归约
/// all()=true matrix/array中的所有算术(元素)是true
/// any()=true matrix/array中至少有一个元素是true
/// count() 返回为true元素的数目
void c()
{
    ArrayXXf a(2, 2);

    a << 1, 2,
        3, 4;
    cout << "(a > 0).all()   = " << (a > 0).all() << endl;
    cout << "(a > 0).any()   = " << (a > 0).any() << endl;
    cout << "(a > 0).count() = " << (a > 0).count() << endl;
    cout << endl;
    cout << "(a > 2).all()   = " << (a > 2).all() << endl;
    cout << "(a > 2).any()   = " << (a > 2).any() << endl;
    cout << "(a > 2).count() = " << (a > 2).count() << endl;
}
/// 迭代器(遍历)
/// 当我们想获取某元素在Matrix或Array中的位置的时候，迭代器是必须的。常用的有：minCoeff和maxCoeff。
void d()
{
    Eigen::MatrixXf m(2, 2);
    m << 1, 2,
        3, 4;
    //get location of maximum
    MatrixXf::Index maxRow, maxCol;
    float max = m.maxCoeff(&maxRow, &maxCol);
    //get location of minimum
    MatrixXf::Index minRow, minCol;
    float min = m.minCoeff(&minRow, &minCol);
    cout << "Max: " << max << ", at: " << maxRow << "," << maxCol << endl;
    cout << "Min: " << min << ", at: " << minRow << "," << minCol << endl;
}
/// 部分公约
/// Eigen中支持对Matrx或Array的行/行进行归约操作。部分归约可以使用colwise()/rowwise()函数。
void e()
{
    Eigen::MatrixXf mat(2, 4);
    mat << 1, 2, 6, 9,
        3, 1, 7, 2;
    /// 针对列向量  返回行向量
    std::cout << "Column's maximum: " << std::endl
              << mat.colwise().maxCoeff() << std::endl;
    /// 针对行向量  返回列向量
    std::cout << "Row's maximum: " << std::endl
              << mat.rowwise().maxCoeff() << std::endl;
}
///  结合部分归约和其他操作
void f()
{
    // 寻找和最大的列向量。
    MatrixXf mat(2, 4);
    mat << 1, 2, 6, 9,
        3, 1, 7, 2;

    MatrixXf::Index maxIndex;
    float maxNorm = mat.colwise().sum().maxCoeff(&maxIndex);

    std::cout << "Maximum sum at position " << maxIndex << std::endl;
    std::cout << "The corresponding vector is: " << std::endl;
    std::cout << mat.col(maxIndex) << std::endl;
    std::cout << "And its sum is is: " << maxNorm << std::endl;
}
/// 广播
/// 广播是针对vector的，将vector沿行/列重复构建一个matrix，便于后期运算。
/// 对Array类型，*=，/=和/这些操作可以进行行/列级的操作，但不使用与Matrix，因为会与矩阵乘混淆
void g()
{
    Eigen::MatrixXf mat(2, 4);
    Eigen::VectorXf v(2);
    mat << 1, 2, 6, 9,
        3, 1, 7, 2;
    v << 0,
        1;

    //add v to each column of m
    mat.colwise() += v;

    std::cout << "Broadcasting result: " << std::endl;
    std::cout << mat << std::endl;
}
/// 结合广播和其他操作
void h()
{
    /// 计算矩阵中哪列与目标向量距离最近。
    Eigen::MatrixXf m(2, 4);
    Eigen::VectorXf v(2);

    m << 1, 23, 6, 9,
        3, 11, 7, 2;

    v << 2,
        3;
    MatrixXf::Index index;
    // find nearest neighbour
    (m.colwise() - v).colwise().squaredNorm().minCoeff(&index);
    cout << "Nearest neighbour is column " << index << ":" << endl;
    cout << m.col(index) << endl;
}

int main()
{
    // a();
    // b();
    // c();
    // d();
    // e();
    // f();
    // g();
    h();
}