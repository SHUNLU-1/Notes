cmake_minimum_required(VERSION 3.19)
project(SVM_Multi)

set(CMAKE_CXX_STANDARD 14)
#opencv
find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )

add_executable(SVM_Multi main.cpp)
target_link_libraries( SVM_Multi ${OpenCV_LIBS})
