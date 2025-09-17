cmake_minimum_required(VERSION 2.8.12)
project(chapter4)

find_package(Sophus REQUIRED)

include_directories("/usr/include/eigen3")
add_executable(useSophus useSophus.cpp)
target_link_libraries(useSophus Sophus::Sophus)

add_subdirectory(example)