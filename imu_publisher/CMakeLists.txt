cmake_minimum_required(VERSION 2.8.3)
project(imu_publisher)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  std_msgs
  sensor_msgs
)

catkin_package()

include_directories(
  ${catkin_INCLUDE_DIRS}
)

add_executable(imu_publisher src/imu_publisher.cpp)
target_link_libraries(imu_publisher ${catkin_LIBRARIES})
add_dependencies(imu_publisher imu_publisher_generate_messages_cpp)


