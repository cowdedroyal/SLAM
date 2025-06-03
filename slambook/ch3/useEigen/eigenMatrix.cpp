#include <iostream>
#include <ctime>
using namespace std;

// Eigen 部分
#include <Eigen/Core>
// 稠密矩阵的代数运算（逆，特征值等）
#include <Eigen/Dense>

#define MATRIX_SIZE 50

int main(int argc, char **argv)
{
    // Eigen 以矩阵为基本数据单元。它是一个模板类。它的前三个参数为：数据类型，行，列
    // 声明一个2*3的float矩阵
    Eigen::Matrix<float, 2, 3> matrix_23;
    // 同时，Eigen 通过 typedef 提供了许多内置类型，不过底层仍是 Eigen::Matrix
    // 例如 Vector3d 实质上是 Eigen::Matrix<double, 3, 1>
    Eigen::Vector3d v_3d;
    // Matrix3d 实质上是 Eigen::Matrix<double, 3, 3>
    Eigen::Matrix3d matrix_33 = Eigen::Matrix3d::Zero(); // 初始化为零矩阵
    // 如果不确定矩阵大小，可以使用动态大小的矩阵
    Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> matrix_dynamic;
    // 更简单的
    Eigen::MatrixXd matrix_x; // 动态大小的矩阵，默认类型为 double

    // 对矩阵的操作
    // 输入数据
    matrix_23 << 1, 2, 3, 4, 5, 6; // 注意逗号分隔
    // 输出
    cout << matrix_23 << endl;
    // 用()访问矩阵中的元素
    for (int i = 0; i < 1; i++)
        for (int j = 0; j < 2; j++)
            cout << matrix_23(i, j) << endl;

    v_3d << 3, 2, 1;
    // 矩阵和向量相乘（实际上仍是矩阵和矩阵）
    // 但是在这里你不能混合两种不同类型的矩阵，像这样是错误的
    // Eigen::Matrix<double, 2, 1> result_wrong_type = matrix_23 * v_3d;

    // 应该显式转换
    Eigen::Matrix<double, 2, 1> result = matrix_23.cast<double>() * v_3d;
    cout << result << endl;

    // 也不能搞错维度
    // 不然会报error: static assertion failed: YOU_MIXED_MATRICES_OF_DIFFERENT_SIZES
    // Eigen::Matrix<double, 2, 3> result_wrong_dimension = matrix_23.cast<double>() * v_3d;

    // 运算符
    matrix_33 = Eigen::Matrix3d::Random(); // 随机初始化
    cout << matrix_33 << endl
         << endl;

    cout << matrix_33.transpose() << endl; // 转置
    cout << matrix_33.sum() << endl;        // 各元素和
    cout << matrix_33.trace() << endl;      // 对角线元素和，迹
    cout << 10*matrix_33 << endl; // 数乘
    cout << matrix_33.inverse() << endl; // 逆矩阵
    cout << matrix_33.determinant() << endl; // 行列式

    // 特征值
    // 实对称矩阵可以保证对角化成功
    Eigen::SelfAdjointEigenSolver<Eigen::Matrix3d> eigen_solver(matrix_33.transpose() * matrix_33);
    cout << "Eigen values = " << eigen_solver.eigenvalues() << endl; // 特征值
    cout << "Eigen vectors = " << eigen_solver.eigenvectors() << endl; // 特征向量

    // 解方程
    // 我们求解 matrix_NN * x = v_Nd 这个方程
    // N 的大小在前边的宏里定义，矩阵由随机数生成
    // 直接求逆自然是最直接的，但是求逆的计算量很大

    Eigen::Matrix<double, MATRIX_SIZE, MATRIX_SIZE> matrix_NN = Eigen::MatrixXd::Random(MATRIX_SIZE, MATRIX_SIZE);
    Eigen::Matrix<double, MATRIX_SIZE, 1> v_Nd = Eigen::MatrixXd::Random(MATRIX_SIZE, 1);

    clock_t time_stt = clock(); // 记录开始时间
    // 直接求逆
    Eigen::Matrix<double, MATRIX_SIZE, 1> x = matrix_NN.inverse() * v_Nd;
    cout << "time use in normal invers is " << 1000 * (clock() - time_stt) / (double)CLOCKS_PER_SEC << "ms" << endl;

    // 通常用矩阵分解来求，例如QR分解，速度会快很多
    time_stt = clock(); // 记录开始时间
    x = matrix_NN.colPivHouseholderQr().solve(v_Nd);
    cout << "time use in QR composition is " << 1000 * (clock() - time_stt) / (double)CLOCKS_PER_SEC << "ms" << endl;

    return 0;
}