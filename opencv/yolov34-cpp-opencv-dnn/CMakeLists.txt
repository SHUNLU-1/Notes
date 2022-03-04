cmake_minimum_required(VERSION 3.10.2)
project(OPENCV-YOLO)

SET(CMAKE_CXX_COMPILER "g++")         #设置编译器（可选的有gcc，g++）

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DPATH=\"\\\"${PROJECT_SOURCE_DIR}\\\"\"")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D${CMAKE_SYSTEM_NAME}")
set(CMAKE_BUILD_TYPE Debug)
SET(BIN_NAME "yolo")
set(CMAKE_CXX_STANDARD 14)

# 是一个编译器缓存
FIND_PROGRAM(CCACHE_FOUND ccache)
IF(CCACHE_FOUND)
    SET_PROPERTY(GLOBAL PROPERTY RULE_LAUNCH_COMPILE ccache)
    SET_PROPERTY(GLOBAL PROPERTY RULE_LAUNCH_LINK ccache)
    MESSAGE("< Use ccache for compiler >")
ENDIF()

# OpenCV
find_package( OpenCV 4 REQUIRED PATHS /home/ubuntu/opencv-4.5.0/build)
include_directories( ${OpenCV_INCLUDE_DIRS} )
include_directories( ${OpenCV_INCLUDE_DIRS}/opencv2/ )


# My Directory
INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/)

ADD_EXECUTABLE(${BIN_NAME} "main_yolo.cpp" )
TARGET_LINK_LIBRARIES(${BIN_NAME} ${OpenCV_LIBS})


