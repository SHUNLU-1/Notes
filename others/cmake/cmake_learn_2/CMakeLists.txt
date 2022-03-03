# cmake版本控制
cmake_minimum_required( VERSION 2.8 )
# cmake工程名字
project( geometry )

# 添加Eigen头文件
include_directories( "/usr/local/include/eigen3" )
# 添加可执行文件
add_executable(eigenGeometry eigenGeometry.cpp )
