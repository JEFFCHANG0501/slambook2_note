cmake_minimum_required(VERSION 2.8.12)
project(chapter5)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_subdirectory(imageBasics)
add_subdirectory(rgbd)
add_subdirectory(stereo)