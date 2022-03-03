cmake_minimum_required(VERSION 3.10.2)
project(EIGEN_LEARN)

SET(CMAKE_CXX_COMPILER "g++")         #设置编译器（可选的有gcc，g++）
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DPATH=\"\\\"${PROJECT_SOURCE_DIR}\\\"\"")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D${CMAKE_SYSTEM_NAME}")
set(CMAKE_BUILD_TYPE Release )
SET(BIN_NAME "eigen")
#set(CMAKE_CXX_STANDARD 14)

# 是一个编译器缓存
FIND_PROGRAM(CCACHE_FOUND ccache)
IF(CCACHE_FOUND)
    SET_PROPERTY(GLOBAL PROPERTY RULE_LAUNCH_COMPILE ccache)
    SET_PROPERTY(GLOBAL PROPERTY RULE_LAUNCH_LINK ccache)
    MESSAGE("< Use ccache for compiler >")
ENDIF()
# Eigen
include_directories("/usr/local/include/eigen3")
INCLUDE_DIRECTORIES(${EIGEN3_INCLUDE_DIR})

# ADD_EXECUTABLE(${BIN_NAME} Matrix.cpp)   # 矩阵操作
# ADD_EXECUTABLE(${BIN_NAME} Array.cpp)    # 数组操作
# ADD_EXECUTABLE(${BIN_NAME} Block.cpp)    # 块操作
# ADD_EXECUTABLE(${BIN_NAME} Init.cpp)     # 更高级的初始化操作
# ADD_EXECUTABLE(${BIN_NAME} Function.cpp) # 功能函数
# ADD_EXECUTABLE(${BIN_NAME} Map.cpp)      # Eigen::Map用法
# ADD_EXECUTABLE(${BIN_NAME} Confuse.cpp)  # 混淆问题
ADD_EXECUTABLE(${BIN_NAME} StorageOrder.cpp) # 存储顺序问题
