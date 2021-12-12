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

include_directories(include ${catkin_INCLUDE_DIRS} src include)

add_executable(main src/main.cpp src/Traverse.cpp src/detection.cpp src/collect.cpp)
target_link_libraries(main ${catkin_LIBRARIES})

add_executable(collection src/collection.cpp)
target_link_libraries(collection ${catkin_LIBRARIES})

if (CATKIN_ENABLE_TESTING)
  
  find_package(rostest REQUIRED)
  
  add_rostest_gtest(
   ct 
   test/test.launch  
   test/collect_test.cpp 
   src/collect.cpp)

  target_link_libraries(
   ct 
   ${catkin_LIBRARIES}
   ${OpenCV_LIBS})
  
  add_dependencies(
    ct
    main
    ${catkin_EXPORTED_TARGETS}
  )
endif()
