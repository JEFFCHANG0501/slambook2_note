project(stereo)

find_package(Pangolin REQUIRED)
include_directories("/usr/include/eigen3")

add_executable(stereoVision stereoVision.cpp)
target_link_libraries(stereoVision
    ${OpenCV_LIBS}
    ${Pangolin_LIBRARIES}
)
