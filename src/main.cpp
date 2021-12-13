///============================================================================
/// @file        : main.cpp
/// @author      : Sameep Pote (Driver)
/// @author      : Gaurav Raut (Navigator)
/// @author      : Advait Patole (Design Keeper)
/// @version     : 1.0.1
/// @copyright   : MIT License
/// @brief       : main.cpp is used to execute the complete program
///============================================================================

#include <vector>
#include <Traverse.h>
#include "ros/ros.h"
#include "collect.hpp"
#include "detection.hpp"

int main(int argc, char **argv) {
  ros::init(argc, argv, "gas");
  ros::NodeHandle nh;
  Traverse tr(nh);
  tr.move_next();
  ROS_INFO_STREAM("Completed navigation!");

  while (ros::ok()) {
    ros::spinOnce();
  }
  return 0;
}
