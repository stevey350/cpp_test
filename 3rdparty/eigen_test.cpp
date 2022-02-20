/**
 * @file eigen_test.cpp
 * @brief  Eigen中基本和常用函数(总结很全): https://blog.csdn.net/u010307048/article/details/108747539
 * @author sj.su (sj.su@tungthih.com.cn)
 * @version 1.0
 * @date 2022-01-12
 * 
 * @copyright Copyright (c) 2022 Xiamen Tung Thih Electron CO.,LTD
 * 
 * @par History:
 * <table>
 * <tr>
 *     <th>Date
 *     <th>Version
 *     <th>Author
 *     <th>Description
 * </tr>
 * <tr>
 *     <th>2022-01-12
 *     <th>v0.0.1
 *     <th>sj.su
 *     <th>原型开发
 * </tr>
 * </table>
 */
#include <eigen3/Eigen/Eigen>
#include <iostream>

using namespace std;
using namespace Eigen;

void eigen_map_test(void)
{
    int array[9];
    for(int i = 0; i < 9; ++i)
        array[i] = i;
    Eigen::Map<Eigen::Matrix3i> matrix(array);
    std::cout << matrix << std::endl;
    std::cout << "[0][0] " << matrix(0, 0) << " " << matrix(0, 1) << " " << matrix(0, 2) << std::endl;

    Eigen::Matrix3i matrix2(array);
    std::cout << matrix2 << std::endl;

    Eigen::Matrix<int, 3, 3, Eigen::RowMajor> matrix3(array);
    std::cout << "Row Major matrix\n" << matrix3 << std::endl;
}

/**
 * @brief 矩阵/向量的定义、赋值与访问
 */
void eigen_definition(void)
{
    Matrix<double, 3, 3> A;                 // 固定了行数和列数的矩阵和Matrix3d一致.
    Matrix<double, 3, Dynamic> B;           // 固定行数.
    Matrix<double, Dynamic, Dynamic> C;     // 和MatrixXd一致.
    Matrix<double, 3, 3, RowMajor> E;       // 按行存储; 默认按列存储.
    Matrix3f P, Q, R;                       // 3x3 float 矩阵.
    Vector3f x, y, z;                       // 3x1 float 列向量.
    RowVector3f a, b, c;                    // 1x3 float 行向量.
    VectorXd v;                             // 动态长度double型列向量

    A << 1, 2, 3,
         4, 5, 6,
         7, 8, 9;
    // A.resize(4, 4);                         // 如果越界触发运行时错误.
    B.resize(3, 9);                         // OK; 没有越界
    C.resize(3, 3);
    C.fill(10);                             // 赋成全10
    int i=0, j=0;

    cout << "x.size: " << x.size() << endl;   // 向量长度
    cout << "C.rows: " << C.rows() << endl;   // 矩阵行数
    cout << "C.cols: " << C.cols() << endl;   // 矩阵列数
    cout << "x.(i): " << x(i) << endl;        // 下标0开始
    cout << "C(i, j): " << C(i, j) << endl;   // 下标0开始
}

/**
 * @brief 常用矩阵
 */
void eigen_basic_matrix(void)
{
    Matrix<double, Dynamic, Dynamic> C;
    VectorXd v;
    Eigen::Index rows=3, cols=3;

    // 单位矩阵 (Matlab)
    // eye(rows,cols) 单位矩阵
    // C = eye(rows,cols) 单位矩阵
    cout << "MatrixXd::Identity: \n" << MatrixXd::Identity(rows, cols) << endl;
    cout << "C.setIdentity: \n" << C.setIdentity(rows, cols) << endl;            
    
    // 零矩阵 (Matlab)
    // zeros(rows,cols)
    // C = zeros(rows,cols)
    cout << "MatrixXd::Zero: \n" << MatrixXd::Zero(rows,cols) << endl;
    cout << "C.setZero: \n" << C.setZero(rows,cols) << endl;

    // 全一矩阵(Matlab)
    // ones(rows,cols)
    // C = ones(rows,cols)
    cout << "MatrixXd::Ones: \n" << MatrixXd::Ones(rows,cols) << endl;
    cout << "C.setOnes: \n" << C.setOnes(rows,cols) << endl;

    // 随机矩阵(Matlab) 元素随机在-1->1
    // rand(rows,cols)*2-1
    // C = rand(rows,cols)*2-1
    cout << "MatrixXd::Random: \n" << MatrixXd::Random(rows,cols) << endl;
    cout << "C.setRandom: \n" << C.setRandom(rows,cols) << endl;

    // 线性分布的数组
    // linspace(low,high,size)'
    // v = linspace(low,high,size)'
    Eigen::Index size=10, low=0, high=100;
    cout << "VectorXd::LinSpaced: \n" << VectorXd::LinSpaced(size,low,high) << endl;
    cout << "v.setLinSpaced: \n" << v.setLinSpaced(size,low,high) << endl;

}

/**
 * @brief eigen的基本运算
 */
void eigen_basic_operation(void)
{
    // 1-矩阵和向量的加减运算
    Matrix2d a;     // Matrix<double, 2, 2>
    a << 1, 2,
         3, 4;
    MatrixXd b(2, 2);
    b << 2, 3,
         1, 4;
    Vector3d v(1, 2, 3);        // 列向量
    Vector3d w(1, 2, 0);

    std::cout<<"a+b=\n"<<a+b<<std::endl;
    std::cout<<"a-b=\n"<<a-b<<std::endl;
    // std::cout<<"Doing a+=b;"<<std::endl;
    // a+=b;
    // std::cout<<"Now a=\n"<<a<<std::endl;
    std::cout<<"-v+w-v=\n"<<-v+w-v<<std::endl;

    // 2-和标量的乘法和除法
    std::cout<<"a*2.5=\n"<<a*2.5<<std::endl;
    std::cout<<"0.1*v=\n"<<0.1*v<<std::endl;
    std::cout<<"Doing v*=2;"<<std::endl;
    // v*=2;
    // std::cout<<"Now v=\n"<<v<<std::endl;

    // 3-转置(Transposition)和共轭(conjugation)
    std::cout << "The transposition of a=\n" << a.transpose() << std::endl;
    std::cout << "The conjugate of a=\n" << a.conjugate() << std::endl;
    std::cout << "The adjoint of a=\n" << a.adjoint() << std::endl;

    // 4-矩阵-矩阵以及矩阵-向量相乘
    Vector2d u(1, -1);
    std::cout << "a*a=\n" << a*a << std::endl;
    std::cout << "a*u=\n" << a*u << std::endl;
    std::cout << "u^T*u=\t\t" << u.transpose()*u << std::endl;
    std::cout << "v^T*w=\t\t" << v.transpose()*w << std::endl;

    // 5-点乘和叉乘
    std::cout << "v dot w=\t\t" << v.dot(w) << std::endl;
    std::cout << "v corss w=\n" << v.cross(w) << std::endl;

    // 6-其它元素操作
    cout<<"Here is a.sum():\t\t"<<a.sum()<<endl;
    cout<<"Here is a.prd():\t\t"<<a.prod()<<endl;
    cout<<"Here is a.mean():\t\t"<<a.mean()<<endl;
    cout<<"Here is a.minCoeff():\t\t"<<a.minCoeff()<<endl;
    cout<<"Here is a.maxCoeff():\t\t"<<a.maxCoeff()<<endl;
    cout<<"Here is a.trace():\t\t"<<a.trace()<<endl;
}

int main(int argc, char ** argv)
{
    std::cout << "Hello Eigen" << std::endl;

    // eigen_definition();
    eigen_basic_matrix();
    // eigen_basic_operation();

    // eigen_map_test();

    return 0;
}
