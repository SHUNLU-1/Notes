#include <iostream>
#include <Eigen/Dense>
using namespace Eigen;
using namespace std;
/*
  为什么使用Array
  相对于Matrix提供的线性代数运算，Array类提供了更为一般的数组功能。
  Array类为元素级的操作提供了有效途径，比如点加（每个元素加值）或两个数据相应元素的点乘。

  Array是个类模板（类似于Matrx）,前三个参数是必须指定的，后三个是可选的，这点和Matrix是相同的。
  Array<typename Scalar, int RowsAtCompileTime, int ColsAtCompileTime>
    -------------------------------------------
    | Type	                        | Tyoedef |
    | Array<float,Dynamic,1>	    | ArrayXf |
    | Array<float,3,1>	            | Array3f |
    | Array<double,Dynamic,Dynamic> | ArrayXXd|
    | Array<double,3,3>	            | Array33d|
    -------------------------------------------
*/
/// 获取元素
void a()
{
    ArrayXXf m(2, 2);

    // assign some values coefficient by coefficient
    m(0, 0) = 1.0;
    m(0, 1) = 2.0;
    m(1, 0) = 3.0;
    m(1, 1) = m(0, 1) + m(1, 0);

    // print values to standard output
    cout << m << endl
         << endl;

    // using the comma-initializer is also allowed
    m << 1.0, 2.0,
        3.0, 4.0;

    // print values to standard output
    cout << m << endl;
}
/// 加法与乘法
/// 和matrix类似，要求array的尺寸一致。同时支持array+/-scalar的操作！
void b()
{
    ArrayXXf a(3, 3);
    ArrayXXf b(3, 3);
    a << 1, 2, 3,
        4, 5, 6,
        7, 8, 9;
    b << 1, 2, 3,
        1, 2, 3,
        1, 2, 3;

    // Adding two arrays
    cout << "a + b = " << endl
         << a + b << endl
         << endl;
    // Subtracting a scalar from an array
    cout << "a - 2 = " << endl
         << a - 2 << endl;
}
/// 乘法
/// 支持array*scalar（类似于matrix），
/// 但是当执行array*array时，执行的是相应元素的乘积，因此两个array必须具有相同的尺寸。
void b1()
{
    ArrayXXf a(2, 2);
    ArrayXXf b(2, 2);
    a << 1, 2,
        3, 4;
    b << 5, 6,
        7, 8;
    cout << "a * b = " << endl
         << a * b << endl;
}
/// 其他元素级操作
/*----------------------------------------
   | Function |	function               |
   | abs	  | 绝对值                  |
   | sqrt	  | 平方根                  |
   | min(.)	  | 两个array相应元素的最小值 |
-----------------------------------------*/
void c()
{
    ArrayXf a = ArrayXf::Random(5);
    a *= 2;
    cout << "a =" << endl
         << a << endl;
    cout << "a.abs() =" << endl
         << a.abs() << endl;
    cout << "a.abs().sqrt() =" << endl
         << a.abs().sqrt() << endl;
    cout << "a.min(a.abs().sqrt()) =" << endl
         << a.min(a.abs().sqrt()) << endl;
}
/// ******array和matrix之间的转换*******
/// 当需要线性代数类操作时，请使用Matrix；但需要元素级操作时，需要使用Array。
/// 这样就需要提供两者的转化方法。
/// Matrix提供了.array()函数将它们转化为Array对象。
/// Array提供了.matrix()函数将它们转化为Matrix对象。
/// 在Eigen，在表达式中混合Matrix和Array操作是被禁止的，但是可以将array表达式结果赋值为matrix。
/// 另外，Matrix提供了cwiseProduct函数也实现了点乘。
void d()
{
    MatrixXf m(2, 2);
    MatrixXf n(2, 2);
    MatrixXf result(2, 2);
    m << 1, 2,
        3, 4;
    n << 5, 6,
        7, 8;
    result = m * n;
    cout << "-- Matrix m*n: --" << endl
         << result << endl
         << endl;
    result = m.array() * n.array();
    cout << "-- Array m*n: --" << endl
         << result << endl
         << endl;
    result = m.cwiseProduct(n);
    cout << "-- With cwiseProduct: --" << endl
         << result << endl
         << endl;
    result = m.array() + 4;
    cout << "-- Array m + 4: --" << endl
         << result << endl
         << endl;
}
int main()
{
    // a();
    // b();
    // b1();
    // c();
    d();
}