cmake_minimum_required(VERSION 2.8.3)
project(gas)

## Find catkin and any catkin packages
find_package(catkin REQUIRED COMPONENTS roscpp rospy std_msgs genmsg message_generation tf rostest move_base_msgs cv_bridge sensor_msgs geometry_msgs nav_msgs)

## Generate messages in the 'msg' folder
# add_message_files(
#   FILES
#   Message1.msg
#   Message2.msg
# )

## Generate services in the 'srv' folder

## Generate added messages and services
generate_messages(DEPENDENCIES std_msgs)

## Declare a catkin package
catkin_package()

## Build talker and listener
include_directories(include ${catkin_INCLUDE_DIRS})

add_executable(collect src/collect.cpp)
target_link_libraries(collect ${catkin_LIBRARIES} )
add_dependencies(collect gas_generate_messages_cpp)

add_executable(detection src/detection.cpp src/main.cpp)
target_link_libraries(detection ${catkin_LIBRARIES} )
add_dependencies(detection gas_generate_messages_cpp)


