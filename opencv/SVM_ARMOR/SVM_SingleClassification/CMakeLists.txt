cmake_minimum_required(VERSION 3.19)
project(SVM_single)

set(CMAKE_CXX_STANDARD 14)
#opencv
find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )

add_executable(SVM_single main.cpp)
target_link_libraries( SVM_single ${OpenCV_LIBS})
