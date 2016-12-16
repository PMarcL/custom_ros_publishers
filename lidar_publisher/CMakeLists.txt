cmake_minimum_required(VERSION 2.8.3)
project(lidar_publisher)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  std_msgs
  sensor_msgs
)

catkin_package()

include_directories(
  ${catkin_INCLUDE_DIRS}
)

file(COPY ./data DESTINATION ${CATKIN_DEVEL_PREFIX}/${CATKIN_PACKAGE_BIN_DESTINATION})

add_executable(lidar_publisher src/lidar_publisher.cpp)
target_link_libraries(lidar_publisher ${catkin_LIBRARIES})
add_dependencies(lidar_publisher lidar_publisher_generate_messages_cpp)
