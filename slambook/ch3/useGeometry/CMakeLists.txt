# 声明要求的cmake最低版本
cmake_minimum_required(VERSION 2.8)

# 声明项目名称
project(useGeometry)

# 添加头文件
include_directories("/usr/include/eigen3")

# 添加一个可执行程序
add_executable(useGeometry useGeometry.cpp)
