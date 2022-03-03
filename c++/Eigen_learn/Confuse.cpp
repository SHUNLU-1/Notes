#include <iostream>
#include <Eigen/Dense>

using namespace Eigen;
using namespace std;
/*
    在Eigen中，当变量同时出现在左值和右值，赋值操作可能会带来混淆问题。
    这一篇将解释什么是混淆，什么时候是有害的，怎么使用做。\
*/
void a()
{
    MatrixXi mat(3, 3);
    mat << 1, 2, 3, 4, 5, 6, 7, 8, 9;
    cout << "Here is the matrix mat:\n"
         << mat << endl;
    // This assignment shows the aliasing problem
    /// 在 mat.bottomRightCorner(2,2) = mat.topLeftCorner(2,2); 赋值中展示了混淆。
    mat.bottomRightCorner(2, 2) = mat.topLeftCorner(2, 2);
    cout << "After the assignment, mat = \n"
         << mat << endl;
    Matrix2i a;
    a << 1, 2, 3, 4;
    cout << "Here is the matrix a:\n"
         << a << endl;
    a = a.transpose(); // !!! do NOT do this !!!
    cout << "and the result of the aliasing effect:\n"
         << a << endl;
}
/// Eigen需要把右值赋值为一个临时matrix/array，然后再将临时值赋值给左值，
/// 便可以解决混淆。eval()函数实现了这个功能。

/// 同样： a = a.transpose().eval(); ，当然我们最好使用 transposeInPlace()。
/// 如果存在xxxInPlace函数，推荐使用这类函数，它们更加清晰地标明了你在做什么。提供的这类函数：
/*
    ---------------------------------------------------------------
    |Origin	                    |   In-place                      |
    |MatrixBase::adjoint()	    |  MatrixBase::adjointInPlace()   |
    |DenseBase::reverse()	    |  DenseBase::reverseInPlace()    |
    |LDLT::solve()	            |  LDLT::solveInPlace()           |
    |LLT::solve()	            |  LLT::solveInPlace()            |
    |TriangularView::solve()    |  TriangularView::solveInPlace() |
    |DenseBase::transpose()	    |  DenseBase::transposeInPlace()  |
     --------------------------------------------------------------
     而针对vec = vec.head(n)这种情况，推荐使用conservativeResize()。
*/
void b()
{
    MatrixXi mat(3, 3);
    mat << 1, 2, 3, 4, 5, 6, 7, 8, 9;
    cout << "Here is the matrix mat:\n"
         << mat << endl;
    // The eval() solves the aliasing problem
    mat.bottomRightCorner(2, 2) = mat.topLeftCorner(2, 2).eval();
    cout << "After the assignment, mat = \n"
         << mat << endl;
}
/*
混淆和component级的操作。
组件级是指整体的操作，比如matrix加法、scalar乘、array乘等，这类操作是安全的，不会出现混淆。
*/
void c()
{
    MatrixXf mat(2, 2);
    mat << 1, 2, 4, 7;
    cout << "Here is the matrix mat:\n"
         << mat << endl
         << endl;
    mat = 2 * mat;
    cout << "After 'mat = 2 * mat', mat = \n"
         << mat << endl
         << endl;
    mat = mat - MatrixXf::Identity(2, 2);
    cout << "After the subtraction, it becomes\n"
         << mat << endl
         << endl;
    ArrayXXf arr = mat;
    arr = arr.square();
    cout << "After squaring, it becomes\n"
         << arr << endl
         << endl;
}
/*混淆和矩阵的乘法*/
/*
    在Eigen中，矩阵的乘法一般都会出现混淆。除非是方阵（实质是元素级的乘）。

    其他的操作，Eigen默认都是存在混淆的。所以Eigen对矩阵乘法自动引入了临时变量，
    对的matA=matA*matA这是必须的，但是对matB=matA*matA这样便是不必要的了。
    我们可以使用noalias()函数来声明这里没有混淆，matA*matA的结果可以直接赋值为matB。
    matB.noalias() = matA * matA;

    从Eigen3.3开始，如果目标矩阵resize且结果不直接赋值给目标矩阵，默认不存在混淆。
    当然，对于任何混淆问题，都可以通过matA=(matB*matA).eval() 来解决。

    总结
    当相同的矩阵或array在等式左右都出现时，很容易出现混淆。

    compnent级别的操作不用考虑混淆。
    矩阵相乘，Eigen默认会解决混淆问题，如果你确定不会出现混淆，可以使用noalias（）来提效。
    混淆出现时，可以用eval()和xxxInPlace()函数解决。

*/
int main()
{
    // a();
    // b();
    c();
}