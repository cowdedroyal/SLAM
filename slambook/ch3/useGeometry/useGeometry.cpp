#include <iostream>
#include <cmath>
using namespace std;

#include <Eigen/Core>
// Eigen 几何模块
#include <Eigen/Geometry>

int main(int argc, char** argv)
{
    // Eigen/Geometry 模块提供了各种旋转和平移的表示
    // 3D 旋转矩阵直接使用Matrix3d 或 Matrix3f
    Eigen::Matrix3d rotation_matrix = Eigen::Matrix3d::Identity();
    // 旋转向量使用 AngleAxis, 它底层不直接是 Matrix, 但运算可以当作矩阵（因为重载了运算符）
    Eigen::AngleAxisd rotation_vector(M_PI / 4, Eigen::Vector3d(0, 0, 1)); // 沿 Z 轴旋转 45 度
    cout .precision(3);
    cout << "rotation matrix =\n" << rotation_vector.matrix() << endl; // 用matrix()转成矩阵
    // 也可以直接赋值
    rotation_matrix = rotation_vector.toRotationMatrix();
    // 用 AngleAxisd 可以进行坐标变换
    Eigen::Vector3d v(1, 0, 0); // 沿 X 轴的向量
    Eigen::Vector3d v_rotated = rotation_vector * v;
    cout << "(1,0,0) after rotation = " << v_rotated.transpose() << endl;
    // 或者用旋转矩阵
    v_rotated = rotation_matrix * v;
    cout << "(1,0,0) after rotation = " << v_rotated.transpose() << endl;

    // 欧拉角：可以将旋转矩阵直接转换成欧拉角
    Eigen::Vector3d euler_angles = rotation_matrix.eulerAngles(2, 1, 0); // ZYX 顺序
    cout << "yaw pitch roll = " << euler_angles.transpose() << endl;

    // 欧氏变换矩阵使用 Eigen::Isometry
    Eigen::Isometry3d T = Eigen::Isometry3d::Identity(); // 初始化为单位矩阵,实质上是4x4矩阵
    T.rotate(rotation_vector); // 旋转
    T.pretranslate(Eigen::Vector3d(1, 3, 4)); // 平移
    cout << "Transform matrix =\n" << T.matrix() << endl;

    // 对于仿射和射影变换，使用 Eigen::Affine3d 和 Eigen::Projective3d

    // 四元数
    // 可以直接把 AngleAxis 赋值给四元数，反之亦然
    Eigen::Quaterniond q = Eigen::Quaterniond(rotation_vector);
    cout << "quaternion = \n"
         << q.coeffs() << endl;
    // 注意coeffs() 返回的是四元数的系数，顺序是 (x, y, z, w)，w为实部，前三者是虚部

    // 也可以把旋转矩阵赋给他
    q = Eigen::Quaterniond (rotation_matrix);
    cout << "quaternion from rotation matrix = \n"
         << q.coeffs() << endl;

    // 使用四元数旋转一个向量，使用重载的乘法即可
    v_rotated = q * v; // 注意数学上是 q * v * q^{-1}
    cout << "(1,0,0) after rotation = " << v_rotated.transpose() << endl;

    return 0;
}