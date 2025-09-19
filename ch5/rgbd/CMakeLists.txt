project(rgbd)

find_package(Sophus REQUIRED)
find_package(Pangolin REQUIRED)
include_directories("/usr/include/eigen3")

add_executable(joinMap joinMap.cpp)
target_link_libraries(joinMap 
    ${OpenCV_LIBS} 
    ${Pangolin_LIBRARIES}
)