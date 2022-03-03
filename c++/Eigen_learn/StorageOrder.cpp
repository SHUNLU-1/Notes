#include <iostream>
#include <Eigen/Dense>

using namespace Eigen;
using namespace std;
/******************存储顺序*********************/
///  对于矩阵和二维数组有两种存储方式，列优先和行优先。
///  PlainObjectBase::data()函数可以返回矩阵中第一个元素的内存位置。
/*
    存储顺序及选择
    Matrix类模板中可以设定存储的方向，RowMajor表示行优先，ColMajor表示列优先。默认是列优先。

    如何选择存储方式呢？

    如果要和其他库合作开发，为了转化方便，可以选择同样的存储方式。
    应用中涉及大量行遍历操作，应该选择行优先，寻址更快。反之亦然。
    默认是列优先，而且大多库都是按照这个顺序的，默认的不失为较好的。
*/
void a()
{
    Matrix<int, 3, 4, ColMajor> Acolmajor;
    Acolmajor << 8, 2, 2, 9,
        9, 1, 4, 4,
        3, 5, 4, 5;
    cout << "The matrix A:" << endl;
    cout << Acolmajor << endl
         << endl;
    /// 列优先
    cout << "In memory (column-major):" << endl;
    for (int i = 0; i < Acolmajor.size(); i++)
        cout << *(Acolmajor.data() + i) << "  ";
    cout << endl
         << endl;
    Matrix<int, 3, 4, RowMajor> Arowmajor = Acolmajor;
    /// 行优先
    cout << "In memory (row-major):" << endl;
    for (int i = 0; i < Arowmajor.size(); i++)
        cout << *(Arowmajor.data() + i) << "  ";
    cout << endl;
}

int main()
{
    a();
}