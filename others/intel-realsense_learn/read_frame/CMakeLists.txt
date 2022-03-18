cmake_minimum_required(VERSION 3.20)
project(read_frame)
aux_source_directory(. SRC_LIST)
#add_executable(${PROJECT_NAME} ${SRC_LIST})

 #添加后可进行调试
set( CMAKE_BUILD_TYPE Debug )

set(CMAKE_CXX_FLAGS "-std=c++11")
#寻找opencv库
find_package(OpenCV REQUIRED)
#message(STATUS ${OpenCV_INCLUDE_DIRS})
#添加头文件
include_directories(${OpenCV_INCLUDE_DIRS})
#链接Opencv库

set(DEPENDENCIES realsense2 )

add_executable(read_frame read_frame.cpp )

target_link_libraries(read_frame ${OpenCV_LIBS} )
target_link_libraries(read_frame ${DEPENDENCIES})

