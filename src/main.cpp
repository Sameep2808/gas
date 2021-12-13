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

/// @brief Main function to run the program
///
/// @param argc
/// @param argv
/// @return
int main(int argc, char **argv) {

    ros::init(argc, argv, "main");
    ros::NodeHandle nh;
    char* name = "box1";
    double x_d ;
    double y_d ;
    double z_d ;
    int c = 1;
    
    x_d = atoll(argv[1]);
    y_d = atoll(argv[2]);

    Collect col;
    col.spawn(name, x_d, y_d, 0, c);
    Traverse tr(nh) ;
    tr.move_next();
    ROS_INFO_STREAM("Completed navigation!");


  while (ros::ok()) {
    ros::spinOnce();
  }
  return 0;
}
