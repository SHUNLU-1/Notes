#include <iostream>
#include <Eigen/Dense>

using namespace Eigen;
using namespace std;
/***********************原生缓存的接口：Map类*******************************/
/// Eigen中定义了一系列的vector和matrix，
/// 相比copy数据，更一般的方式是复用数据的内存，将它们转变为Eigen类型。Map类很好地实现了这个功能。
///     Map类型
///     Map的定义
/// Map<Matrix<typename Scalar, int RowsAtCompileTime, int ColsAtCompileTime> >
/// 默认情况下，Map只需要一个模板参数。
/// 为了构建Map变量，我们需要其余的两个信息：
/// 一个指向元素数组的指针，Matrix/vector的尺寸。
/// 定义一个float类型的矩阵： Map<MatrixXf> mf(pf,rows,columns); pf是一个数组指针float *。
/// 固定尺寸的整形vector声明： Map<const Vector4i> mi(pi);
/// 注意:Map没有默认的构造函数，你需要传递一个指针来初始化对象。

/// Map是灵活地足够去容纳多种不同的数据表示，其他的两个模板参数：
/// Map<typename MatrixType,
///     int MapOptions,
///     typename StrideType>
/// MapOptions标识指针是否是对齐的（Aligned），默认是Unaligned。

// StrideType表示内存数组的组织方式：行列的步长。
void a()
{
    int array[8];
    for (int i = 0; i < 8; ++i)
        array[i] = i;
    cout << "Column-major:\n"
         << Map<Matrix<int, 2, 4>>(array) << endl;
    cout << "Row-major:\n"
         << Map<Matrix<int, 2, 4, RowMajor>>(array) << endl;
    cout << "Row-major using stride:\n"
         << Map<Matrix<int, 2, 4>, Unaligned, Stride<1, 4>>(array) << endl;
}
/// 可以像Eigen的其他类型一样来使用Map类型。
void b()
{
    typedef Matrix<float, 1, Dynamic> MatrixType;
    typedef Map<MatrixType> MapType;
    typedef Map<const MatrixType> MapTypeConst; // a read-only map
    const int n_dims = 5;

    MatrixType m1(n_dims), m2(n_dims);
    /// 设置随机数
    m1.setRandom();
    m2.setRandom();

    float *p = &m2(0);                     // get the address storing the data for m2
    MapType m2map(p, m2.size());           // m2map shares data with m2
    MapTypeConst m2mapconst(p, m2.size()); // a read-only accessor for m2
    cout << "p: " << *p << endl;
    cout << "m1: " << m1 << endl;
    cout << "m2: " << m2 << endl;
    cout << "m2map: " << m2map << endl;
    cout << "m2mapconst: " << m2mapconst << endl;
    cout << "Squared euclidean distance: " << (m1 - m2).squaredNorm() << endl;
    cout << "Squared euclidean distance, using map: " << (m1 - m2map).squaredNorm() << endl;
    m2map(3) = 7; // this will change m2, since they share the same array
    cout << "Updated m2: " << m2 << endl;
    cout << "m2 coefficient 2, constant accessor: " << m2mapconst(2) << endl;
    /* m2mapconst(2) = 5; */ // this yields a compile-time error
}
/// 改变mapped数组
/// Map对象声明后，可以通过C++的placement new语法来改变Map的数组。
void c()
{
    int data[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    Map<RowVectorXi> v(data, 4);
    cout << "The mapped vector v is: " << v << "\n";
    new (&v) Map<RowVectorXi>(data + 3, 5);
    cout << "Now v is: " << v << "\n";
}
/// reshape
/// reshape操作是改变matrix的尺寸大小但保持元素不变。采用的方法是创建一个不同“视图” Map。
void d()
{
    MatrixXf M1(3, 3); // Column-major storage
    M1 << 1, 2, 3,
        4, 5, 6,
        7, 8, 9;
    Map<RowVectorXf> v1(M1.data(), M1.size());
    cout << "v1:" << endl
         << v1 << endl;
    Matrix<float, Dynamic, Dynamic, RowMajor> M2(M1);
    Map<RowVectorXf> v2(M2.data(), M2.size());
    cout << "v2:" << endl
         << v2 << endl;

    MatrixXf M3(2, 6); // Column-major storage
    M3 << 1, 2, 3, 4, 5, 6,
        7, 8, 9, 10, 11, 12;
    Map<MatrixXf> M4(M3.data(), 6, 2);
    cout << "M4:" << endl
         << M4 << endl;
}
// Slicing
// 也是通过Map实现的，比如：每p个元素获取一个。
void e()
{
    RowVectorXf v = RowVectorXf::LinSpaced(20, 0, 19);
    cout << "Input:" << endl
         << v << endl;
    Map<RowVectorXf, 0, InnerStride<2>> v2(v.data(), v.size() / 2);
    cout << "Even:" << v2 << endl;
}
int main()
{
    // a();
    // b();
    // c();
    // d();
    e();
}