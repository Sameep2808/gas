cmake_minimum_required(VERSION 3.0.2)
project(gas)

## Find catkin and any catkin packages
find_package(catkin REQUIRED COMPONENTS roscpp rospy std_msgs message_generation tf rostest move_base_msgs cv_bridge sensor_msgs geometry_msgs nav_msgs gazebo_msgs)

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

include_directories(include ${catkin_INCLUDE_DIRS} src include)

add_executable(main src/main.cpp src/Traverse.cpp src/detection.cpp src/collect.cpp)
target_link_libraries(main ${catkin_LIBRARIES})

add_executable(collection src/collection.cpp)
target_link_libraries(collection ${catkin_LIBRARIES})

if (CATKIN_ENABLE_TESTING)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O0 --coverage")
  find_package(rostest REQUIRED)
  
  add_rostest_gtest(
   test_gas 
   test/test.launch
   #test/detecttest.cpp 
   test/Traverse_test.cpp 
   test/collect_test.cpp 
   test/main_test.cpp 
   src/collect.cpp
   src/detection.cpp
   src/Traverse.cpp)

  target_link_libraries(
   test_gas 
   ${catkin_LIBRARIES})
  
  add_dependencies(
    test_gas
    main
    ${catkin_EXPORTED_TARGETS}
  )
endif()
