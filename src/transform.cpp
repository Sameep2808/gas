///============================================================================
/// @file        : pub.cpp
/// @version     : 1.0
/// @author      : Sameep Pote
/// @copyright   : MIT License
/// @brief       : pub.cpp This file is used to publish the custom string
///============================================================================

#include <tf/transform_broadcaster.h>
#include <sstream>
#include "ros/ros.h"
#include "std_msgs/String.h"


int main(int argc, char **argv) {
  ros::init(argc, argv, "transform");

  if (ros::isInitialized()) {
    int frequency = 100;

    ros::NodeHandle n;
    tf::TransformBroadcaster br;
    tf::Transform transform;

    ros::Rate loop_rate(frequency);

    ROS_DEBUG_STREAM("Frequency Check: %d"; frequency);
    while (ros::ok()) {
      transform.setOrigin(tf::Vector3(0.0, 0.0, 0.0));
      transform.setRotation(tf::Quaternion(0, 0, 3.1416, 1));
      br.sendTransform(
          tf::StampedTransform(transform, ros::Time::now(), "map", "base_link"));

      ros::spinOnce();

      loop_rate.sleep();
    }
  } else {
    ROS_FATAL_STREAM("ROS is not initialized.");
  }
  return 0;
}
