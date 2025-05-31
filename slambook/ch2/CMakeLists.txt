# 声明要求的cmake最低版本
cmake_minimum_required(VERSION 2.8)

# 设置为Debug模式
SET(CMAKE_BUILD_TYPE Debug)

# 声明项目名称
project(HelloSLAM)

# 添加一个可执行程序
add_executable(helloSLAM helloSLAM.cpp)
add_executable(useHello useHello.cpp)
# 链接到库
target_link_libraries(useHello hello_shared)

# 添加库
# 添加一个静态库
# add_library(hello libHelloSLAM.cpp) 
# 添加一个动态库
add_library(hello_shared SHARED libHelloSLAM.cpp)
