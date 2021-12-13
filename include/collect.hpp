///============================================================================
/// @file        : collect.cpp
/// @author      : Sameep Pote (Driver)
/// @author      : Gaurav Raut (Navigator)
/// @author      : Advait Patole (Design Keeper)
/// @version     : 1.0.1
/// @copyright   : MIT License
/// @brief       : collect.cpp is used to spawn and collect the object
///============================================================================

#ifndef INCLUDE_COLLECT_HPP_
#define INCLUDE_COLLECT_HPP_

#include <tf/transform_broadcaster.h>
#include <geometry_msgs/Pose.h>
#include <gazebo_msgs/SpawnModel.h>
#include <gazebo_msgs/SpawnModelRequest.h>
#include <gazebo_msgs/SpawnModelResponse.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "std_srvs/Empty.h"
#include "gazebo_msgs/DeleteModel.h"
#include "ros/ros.h"
#include "std_msgs/String.h"


class Collect {
 private:
  // the node handle of the collect node
  ros::NodeHandle nh;

  // the Service Client that activates spawn_model_client
  ros::ServiceClient spawn_model_client;

  // the Service Client that activates delete_model_client
  ros::ServiceClient delete_model_client;
  // geometry msgs to store position
  geometry_msgs::Pose pose;

 public:
  bool checkr = false;
  bool checks = false;

  // Function to Spawn Objects

  void spawn(char *name, double xd, double yd, double zd, int c);

  // Function to Remove Objects

  void remove_ob(char *name);
};

#endif  // INCLUDE_COLLECT_HPP_
