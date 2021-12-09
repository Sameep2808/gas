cmake_minimum_required(VERSION 2.8.3)
project(gas)

## Find catkin and any catkin packages
find_package(catkin REQUIRED COMPONENTS roscpp rospy std_msgs genmsg message_generation tf rostest move_base_msgs)

## Generate messages in the 'msg' folder
# add_message_files(
#   FILES
#   Message1.msg
#   Message2.msg
# )

## Generate services in the 'srv' folder
## add_service_files(FILES change_string.srv)

## Generate added messages and services
generate_messages(DEPENDENCIES std_msgs)

## Declare a catkin package
catkin_package()

## Build talker and listener
include_directories(include ${catkin_INCLUDE_DIRS} include)

add_executable(reach_goal src/reach_goal.cpp)
target_link_libraries(reach_goal ${catkin_LIBRARIES})

add_executable(transform src/transform.cpp)
target_link_libraries(transform ${catkin_LIBRARIES})

add_executable(main src/main.cpp src/collect.cpp)
target_link_libraries(main ${catkin_LIBRARIES})
