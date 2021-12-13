///============================================================================
/// @file        : detection.hpp
/// @author      : Advait PatoleGaurav Raut (Driver)
/// @author      : Sameep Pote (Navigator)
/// @author      : Gaurav Raut (Design Keeper)
/// @version     : 1.0.1
/// @copyright   : MIT License
/// @brief       : detection.cpp include file
///============================================================================

#ifndef INCLUDE_DETECTION_HPP_
#define INCLUDE_DETECTION_HPP_

#include <cv_bridge/cv_bridge.h>
#include <move_base_msgs/MoveBaseActionGoal.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>
#include <sensor_msgs/image_encodings.h>
#include <bits/stdc++.h>
#include <sensor_msgs/LaserScan.h>
#include <nav_msgs/Odometry.h>
#include <geometry_msgs/Twist.h>
#include <iostream>
#include <vector>
#include "ros/ros.h"
#include "Traverse.h"
#include "collect.hpp"
#include "opencv2/opencv.hpp"
#include "tf/transform_datatypes.h"

class Detect {
 public:
  // store the distance of object
  double laser_dist;

  // check if the robot is align
  bool aligned;

  // check if distance got from laser
  bool get_dist;

  // position x of object after align
  double pos_x;

  // position x of object after align
  double pos_y;

  // current orientation of robot
  double orientation;

  // check the number of rotations
  int rotate;

  // check to exit the ros spin
  int out;

  // check if the red object spotted
  bool spotted;

  // current ocation of red object
  std::vector<int> pos;

  // ros subscriber for camera
  ros::Subscriber camsub;

  // ros subscriber for laser
  ros::Subscriber scansub;

  // ros subscriber for odometry
  ros::Subscriber odomsub;

  // ros publisher for motor
  ros::Publisher motorpub;

  /**
   * @brief Constructor of class Detect
   *
   * @param ros::NodeHandle nh
   */
  explicit Detect(ros::NodeHandle);

  /**
   * @brief Callback function when camera topic subscribed
   *
   * @param img
   */
  void process_image_callback(const sensor_msgs::Image img);

  /**
   * @brief Callback function when laser topic subscribed
   *
   * @param msg
   */
  void LaserCallback(const sensor_msgs::LaserScan::ConstPtr &msg);

  /**
   * @brief Callback function when odometry topic subscribed
   *
   * @param msg
   */
  void odomCallback(const nav_msgs::Odometry::ConstPtr &msg);

  /**
   * @brief function to drive the robot
   *
   * @param lin_x
   * @param ang_z
   */
  void drive_robot(float lin_x, float ang_z);

  /**
   * @brief Function that starts detection
   *
   */
  void startdetect();

  /**
   * @brief Function to find if red color is spotted
   *
   * @param im
   */
  void spot_image(cv::Mat im);

  /**
   * @brief Function to control robot motion
   *
   * @param im
   */
  void robot_motion(cv::Mat im);

 private:
  // handle for ros node
  ros::NodeHandle n;
};

#endif  // INCLUDE_DETECTION_HPP_
